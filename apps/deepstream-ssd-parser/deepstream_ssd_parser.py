#!/usr/bin/env python3

################################################################################
# SPDX-FileCopyrightText: Copyright (c) 2020-2021 NVIDIA CORPORATION & AFFILIATES. All rights reserved.
# SPDX-License-Identifier: Apache-2.0
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
# http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
################################################################################

""" Example of deepstream using SSD neural network and parsing SSD's outputs. """

import sys
import io
sys.path.append("../")
import gi
gi.require_version("Gst", "1.0")
from gi.repository import GLib, Gst
from common.is_aarch_64 import is_aarch64
from common.bus_call import bus_call
from ssd_parser import nvds_infer_parse_custom_tf_ssd, DetectionParam, NmsParam, BoxSizeParam
import pyds




CLASS_NB = 91
ACCURACY_ALL_CLASS = 0.5
UNTRACKED_OBJECT_ID = 0xffffffffffffffff
IMAGE_HEIGHT = 1080
IMAGE_WIDTH = 1920
MIN_BOX_WIDTH = 32
MIN_BOX_HEIGHT = 32
TOP_K = 20
IOU_THRESHOLD = 0.3
OUTPUT_VIDEO_NAME = "./out.mp4"


def get_label_names_from_file(filepath):
    """ Read a label file and convert it to string list """
    f = io.open(filepath, "r")
    labels = f.readlines()
    labels = [elm[:-1] for elm in labels]
    f.close()
    return labels


def make_elm_or_print_err(factoryname, name, printedname, detail=""):
    """ Creates an element with Gst Element Factory make.
        Return the element  if successfully created, otherwise print
        to stderr and return None.
    """
    print("Creating", printedname)
    elm = Gst.ElementFactory.make(factoryname, name)
    if not elm:
        sys.stderr.write("Unable to create " + printedname + " \n")
        if detail:
            sys.stderr.write(detail)
    return elm


def osd_sink_pad_buffer_probe(pad, info, u_data):
    frame_number = 0
    # Intiallizing object counter with 0.
    obj_counter = dict(enumerate([0] * CLASS_NB))
    num_rects = 0

    gst_buffer = info.get_buffer()
    if not gst_buffer:
        print("Unable to get GstBuffer ")
        return

    # Retrieve batch metadata from the gst_buffer
    # Note that pyds.gst_buffer_get_nvds_batch_meta() expects the
    # C address of gst_buffer as input, which is obtained with hash(gst_buffer)
    batch_meta = pyds.gst_buffer_get_nvds_batch_meta(hash(gst_buffer))
    l_frame = batch_meta.frame_meta_list
    while l_frame is not None:
        try:
            # Note that l_frame.data needs a cast to pyds.NvDsFrameMeta
            # The casting also keeps ownership of the underlying memory
            # in the C code, so the Python garbage collector will leave
            # it alone.
            frame_meta = pyds.NvDsFrameMeta.cast(l_frame.data)
        except StopIteration:
            break

        frame_number = frame_meta.frame_num
        num_rects = frame_meta.num_obj_meta
        l_obj = frame_meta.obj_meta_list
        while l_obj is not None:
            try:
                # Casting l_obj.data to pyds.NvDsObjectMeta
                obj_meta = pyds.NvDsObjectMeta.cast(l_obj.data)
            except StopIteration:
                break
            obj_counter[obj_meta.class_id] += 1
            try:
                l_obj = l_obj.next
            except StopIteration:
                break

        # Acquiring a display meta object. The memory ownership remains in
        # the C code so downstream plugins can still access it. Otherwise
        # the garbage collector will claim it when this probe function exits.
        display_meta = pyds.nvds_acquire_display_meta_from_pool(batch_meta)
        display_meta.num_labels = 1
        py_nvosd_text_params = display_meta.text_params[0]
        # Setting display text to be shown on screen
        # Note that the pyds module allocates a buffer for the string, and the
        # memory will not be claimed by the garbage collector.
        # Reading the display_text field here will return the C address of the
        # allocated string. Use pyds.get_string() to get the string content.
        id_dict = {
            val: index
            for index, val in enumerate(get_label_names_from_file("labels.txt"))
        }
        disp_string = "Frame Number={} Number of Objects={} Vehicle_count={} Person_count={}"
        py_nvosd_text_params.display_text = disp_string.format(
            frame_number,
            num_rects,
            obj_counter[id_dict["car"]],
            obj_counter[id_dict["person"]],
        )

        # Now set the offsets where the string should appear
        py_nvosd_text_params.x_offset = 10
        py_nvosd_text_params.y_offset = 12

        # Font , font-color and font-size
        py_nvosd_text_params.font_params.font_name = "Serif"
        py_nvosd_text_params.font_params.font_size = 10
        # set(red, green, blue, alpha); set to White
        py_nvosd_text_params.font_params.font_color.set(1.0, 1.0, 1.0, 1.0)

        # Text background color
        py_nvosd_text_params.set_bg_clr = 1
        # set(red, green, blue, alpha); set to Black
        py_nvosd_text_params.text_bg_clr.set(0.0, 0.0, 0.0, 1.0)
        # Using pyds.get_string() to get display_text as string
        print(pyds.get_string(py_nvosd_text_params.display_text))
        pyds.nvds_add_display_meta_to_frame(frame_meta, display_meta)
        try:
            l_frame = l_frame.next
        except StopIteration:
            break

    return Gst.PadProbeReturn.OK


def add_obj_meta_to_frame(frame_object, batch_meta, frame_meta, label_names):
    """ Inserts an object into the metadata """
    # this is a good place to insert objects into the metadata.
    # Here's an example of inserting a single object.
    obj_meta = pyds.nvds_acquire_obj_meta_from_pool(batch_meta)
    # Set bbox properties. These are in input resolution.
    rect_params = obj_meta.rect_params
    rect_params.left = int(IMAGE_WIDTH * frame_object.left)
    rect_params.top = int(IMAGE_HEIGHT * frame_object.top)
    rect_params.width = int(IMAGE_WIDTH * frame_object.width)
    rect_params.height = int(IMAGE_HEIGHT * frame_object.height)

    # Semi-transparent yellow backgroud
    rect_params.has_bg_color = 0
    rect_params.bg_color.set(1, 1, 0, 0.4)

    # Red border of width 3
    rect_params.border_width = 3
    rect_params.border_color.set(1, 0, 0, 1)

    # Set object info including class, detection confidence, etc.
    obj_meta.confidence = frame_object.detectionConfidence
    obj_meta.class_id = frame_object.classId

    # There is no tracking ID upon detection. The tracker will
    # assign an ID.
    obj_meta.object_id = UNTRACKED_OBJECT_ID

    lbl_id = frame_object.classId
    if lbl_id >= len(label_names):
        lbl_id = 0

    # Set the object classification label.
    obj_meta.obj_label = label_names[lbl_id]

    # Set display text for the object.
    txt_params = obj_meta.text_params
    if txt_params.display_text:
        pyds.free_buffer(txt_params.display_text)

    txt_params.x_offset = int(rect_params.left)
    txt_params.y_offset = max(0, int(rect_params.top) - 10)
    txt_params.display_text = (
        label_names[lbl_id] + " " + "{:04.3f}".format(frame_object.detectionConfidence)
    )
    # Font , font-color and font-size
    txt_params.font_params.font_name = "Serif"
    txt_params.font_params.font_size = 10
    # set(red, green, blue, alpha); set to White
    txt_params.font_params.font_color.set(1.0, 1.0, 1.0, 1.0)

    # Text background color
    txt_params.set_bg_clr = 1
    # set(red, green, blue, alpha); set to Black
    txt_params.text_bg_clr.set(0.0, 0.0, 0.0, 1.0)

    # Inser the object into current frame meta
    # This object has no parent
    pyds.nvds_add_obj_meta_to_frame(frame_meta, obj_meta, None)


def pgie_src_pad_buffer_probe(pad, info, u_data):

    gst_buffer = info.get_buffer()
    if not gst_buffer:
        print("Unable to get GstBuffer ")
        return

    # Retrieve batch metadata from the gst_buffer
    # Note that pyds.gst_buffer_get_nvds_batch_meta() expects the
    # C address of gst_buffer as input, which is obtained with hash(gst_buffer)
    batch_meta = pyds.gst_buffer_get_nvds_batch_meta(hash(gst_buffer))
    l_frame = batch_meta.frame_meta_list

    detection_params = DetectionParam(CLASS_NB, ACCURACY_ALL_CLASS)
    box_size_param = BoxSizeParam(IMAGE_HEIGHT, IMAGE_WIDTH,
                                  MIN_BOX_WIDTH, MIN_BOX_HEIGHT)
    nms_param = NmsParam(TOP_K, IOU_THRESHOLD)

    label_names = get_label_names_from_file("labels.txt")

    while l_frame is not None:
        try:
            # Note that l_frame.data needs a cast to pyds.NvDsFrameMeta
            # The casting also keeps ownership of the underlying memory
            # in the C code, so the Python garbage collector will leave
            # it alone.
            frame_meta = pyds.NvDsFrameMeta.cast(l_frame.data)
        except StopIteration:
            break

        l_user = frame_meta.frame_user_meta_list
        while l_user is not None:
            try:
                # Note that l_user.data needs a cast to pyds.NvDsUserMeta
                # The casting also keeps ownership of the underlying memory
                # in the C code, so the Python garbage collector will leave
                # it alone.
                user_meta = pyds.NvDsUserMeta.cast(l_user.data)
            except StopIteration:
                break

            if (
                    user_meta.base_meta.meta_type
                    != pyds.NvDsMetaType.NVDSINFER_TENSOR_OUTPUT_META
            ):
                continue

            tensor_meta = pyds.NvDsInferTensorMeta.cast(user_meta.user_meta_data)

            # Boxes in the tensor meta should be in network resolution which is
            # found in tensor_meta.network_info. Use this info to scale boxes to
            # the input frame resolution.
            layers_info = []

            for i in range(tensor_meta.num_output_layers):
                layer = pyds.get_nvds_LayerInfo(tensor_meta, i)
                layers_info.append(layer)

            frame_object_list = nvds_infer_parse_custom_tf_ssd(
                layers_info, detection_params, box_size_param, nms_param
            )
            try:
                l_user = l_user.next
            except StopIteration:
                break

            for frame_object in frame_object_list:
                add_obj_meta_to_frame(frame_object, batch_meta, frame_meta, label_names)

        try:
            # indicate inference is performed on the frame
            frame_meta.bInferDone = True
            l_frame = l_frame.next
        except StopIteration:
            break
    return Gst.PadProbeReturn.OK


def main(args):
    # Check input arguments
    if len(args) != 2:
        sys.stderr.write("usage: %s <media file or uri>\n" % args[0])
        sys.exit(1)

    # Standard GStreamer initialization
    Gst.init(None)

    # Create gstreamer elements
    # Create Pipeline element that will form a connection of other elements
    print("Creating Pipeline \n ")
    pipeline = Gst.Pipeline()

    if not pipeline:
        sys.stderr.write(" Unable to create Pipeline \n")

    # Source element for reading from the file
    source = make_elm_or_print_err("filesrc", "file-source", "Source")

    # Since the data format in the input file is elementary h264 stream,
    # we need a h264parser
    h264parser = make_elm_or_print_err("h264parse", "h264-parser", "H264Parser")

    # Use nvdec_h264 for hardware accelerated decode on GPU
    decoder = make_elm_or_print_err("nvv4l2decoder", "nvv4l2-decoder", "Decoder")

    # Create nvstreammux instance to form batches from one or more sources.
    streammux = make_elm_or_print_err("nvstreammux", "Stream-muxer", "NvStreamMux")

    # Use nvinferserver to run inferencing on decoder's output,
    # behaviour of inferencing is set through config file
    pgie = make_elm_or_print_err("nvinferserver", "primary-inference", "Nvinferserver")

    # Use convertor to convert from NV12 to RGBA as required by nvosd
    nvvidconv = make_elm_or_print_err("nvvideoconvert", "convertor", "Nvvidconv")

    # Create OSD to draw on the converted RGBA buffer
    nvosd = make_elm_or_print_err("nvdsosd", "onscreendisplay", "OSD (nvosd)")


    # Finally encode and save the osd output
    queue = make_elm_or_print_err("queue", "queue", "Queue")

    nvvidconv2 = make_elm_or_print_err("nvvideoconvert", "convertor2", "Converter 2 (nvvidconv2)")

    capsfilter = make_elm_or_print_err("capsfilter", "capsfilter", "capsfilter")

    caps = Gst.Caps.from_string("video/x-raw, format=I420")
    capsfilter.set_property("caps", caps)

    # On Jetson, there is a problem with the encoder failing to initialize
    # due to limitation on TLS usage. To work around this, preload libgomp.
    # Add a reminder here in case the user forgets.
    preload_reminder = "If the following error is encountered:\n" + \
                       "/usr/lib/aarch64-linux-gnu/libgomp.so.1: cannot allocate memory in static TLS block\n" + \
                       "Preload the offending library:\n" + \
                       "export LD_PRELOAD=/usr/lib/aarch64-linux-gnu/libgomp.so.1\n"
    encoder = make_elm_or_print_err("avenc_mpeg4", "encoder", "Encoder", preload_reminder)

    encoder.set_property("bitrate", 2000000)

    codeparser = make_elm_or_print_err("mpeg4videoparse", "mpeg4-parser", 'Code Parser')

    container = make_elm_or_print_err("qtmux", "qtmux", "Container")

    sink = make_elm_or_print_err("filesink", "filesink", "Sink")

    sink.set_property("location", OUTPUT_VIDEO_NAME)
    sink.set_property("sync", 0)
    sink.set_property("async", 0)

    print("Playing file %s " % args[1])
    source.set_property("location", args[1])
    streammux.set_property("width", IMAGE_WIDTH)
    streammux.set_property("height", IMAGE_HEIGHT)
    streammux.set_property("batch-size", 1)
    streammux.set_property("batched-push-timeout", 4000000)
    pgie.set_property("config-file-path", "dstest_ssd_nopostprocess.txt")

    print("Adding elements to Pipeline \n")
    pipeline.add(source)
    pipeline.add(h264parser)
    pipeline.add(decoder)
    pipeline.add(streammux)
    pipeline.add(pgie)
    pipeline.add(nvvidconv)
    pipeline.add(nvosd)
    pipeline.add(queue)
    pipeline.add(nvvidconv2)
    pipeline.add(capsfilter)
    pipeline.add(encoder)
    pipeline.add(codeparser)
    pipeline.add(container)
    pipeline.add(sink)

    # we link the elements together
    # file-source -> h264-parser -> nvh264-decoder ->
    # nvinfer -> nvvidconv -> nvosd -> video-renderer
    print("Linking elements in the Pipeline \n")
    source.link(h264parser)
    h264parser.link(decoder)

    sinkpad = streammux.get_request_pad("sink_0")
    if not sinkpad:
        sys.stderr.write(" Unable to get the sink pad of streammux \n")
    srcpad = decoder.get_static_pad("src")
    if not srcpad:
        sys.stderr.write(" Unable to get source pad of decoder \n")
    srcpad.link(sinkpad)
    streammux.link(pgie)
    pgie.link(nvvidconv)
    nvvidconv.link(nvosd)
    nvosd.link(queue)
    queue.link(nvvidconv2)
    nvvidconv2.link(capsfilter)
    capsfilter.link(encoder)
    encoder.link(codeparser)
    codeparser.link(container)
    container.link(sink)

    # create an event loop and feed gstreamer bus mesages to it
    loop = GLib.MainLoop()
    bus = pipeline.get_bus()
    bus.add_signal_watch()
    bus.connect("message", bus_call, loop)

    # Add a probe on the primary-infer source pad to get inference output tensors
    pgiesrcpad = pgie.get_static_pad("src")
    if not pgiesrcpad:
        sys.stderr.write(" Unable to get src pad of primary infer \n")

    pgiesrcpad.add_probe(Gst.PadProbeType.BUFFER, pgie_src_pad_buffer_probe, 0)

    # Lets add probe to get informed of the meta data generated, we add probe to
    # the sink pad of the osd element, since by that time, the buffer would have
    # had got all the metadata.
    osdsinkpad = nvosd.get_static_pad("sink")
    if not osdsinkpad:
        sys.stderr.write(" Unable to get sink pad of nvosd \n")

    osdsinkpad.add_probe(Gst.PadProbeType.BUFFER, osd_sink_pad_buffer_probe, 0)

    # start play back and listen to events
    print("Starting pipeline \n")
    pipeline.set_state(Gst.State.PLAYING)
    try:
        loop.run()
    except:
        pass
    # cleanup
    pipeline.set_state(Gst.State.NULL)


if __name__ == "__main__":
    sys.exit(main(sys.argv))
