#!/usr/bin/env python3

################################################################################
# SPDX-FileCopyrightText: Copyright (c) 2019-2021 NVIDIA CORPORATION & AFFILIATES. All rights reserved.
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

import sys

sys.path.append('../')
import gi
import math

gi.require_version('Gst', '1.0')
from gi.repository import GLib, Gst
from common.is_aarch_64 import is_aarch64
from common.bus_call import bus_call
import cv2
import pyds
import numpy as np
import os.path
from os import path

MAX_DISPLAY_LEN = 64
MUXER_OUTPUT_WIDTH = 1920
MUXER_OUTPUT_HEIGHT = 1080
MUXER_BATCH_TIMEOUT_USEC = 4000000
TILED_OUTPUT_WIDTH = 1280
TILED_OUTPUT_HEIGHT = 720
COLORS = [[128, 128, 64], [0, 0, 128], [0, 128, 128], [128, 0, 0],
          [128, 0, 128], [128, 128, 0], [0, 128, 0], [0, 0, 64],
          [0, 0, 192], [0, 128, 64], [0, 128, 192], [128, 0, 64],
          [128, 0, 192], [128, 128, 128]]


def map_mask_as_display_bgr(mask):
    """ Assigning multiple colors as image output using the information
        contained in mask. (BGR is opencv standard.)
    """
    # getting a list of available classes
    m_list = list(set(mask.flatten()))

    shp = mask.shape
    bgr = np.zeros((shp[0], shp[1], 3))
    for idx in m_list:
        bgr[mask == idx] = COLORS[idx]
    return bgr


def seg_src_pad_buffer_probe(pad, info, u_data):
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
            # The casting is done by pyds.NvDsFrameMeta.cast()
            # The casting also keeps ownership of the underlying memory
            # in the C code, so the Python garbage collector will leave
            # it alone.
            frame_meta = pyds.NvDsFrameMeta.cast(l_frame.data)
        except StopIteration:
            break
        frame_number = frame_meta.frame_num
        l_user = frame_meta.frame_user_meta_list
        while l_user is not None:
            try:
                # Note that l_user.data needs a cast to pyds.NvDsUserMeta
                # The casting is done by pyds.NvDsUserMeta.cast()
                # The casting also keeps ownership of the underlying memory
                # in the C code, so the Python garbage collector will leave
                # it alone.
                seg_user_meta = pyds.NvDsUserMeta.cast(l_user.data)
            except StopIteration:
                break
            if seg_user_meta and seg_user_meta.base_meta.meta_type == \
                    pyds.NVDSINFER_SEGMENTATION_META:
                try:
                    # Note that seg_user_meta.user_meta_data needs a cast to
                    # pyds.NvDsInferSegmentationMeta
                    # The casting is done by pyds.NvDsInferSegmentationMeta.cast()
                    # The casting also keeps ownership of the underlying memory
                    # in the C code, so the Python garbage collector will leave
                    # it alone.
                    segmeta = pyds.NvDsInferSegmentationMeta.cast(seg_user_meta.user_meta_data)
                except StopIteration:
                    break
                # Retrieve mask data in the numpy format from segmeta
                # Note that pyds.get_segmentation_masks() expects object of
                # type NvDsInferSegmentationMeta
                masks = pyds.get_segmentation_masks(segmeta)
                masks = np.array(masks, copy=True, order='C')
                # map the obtained masks to colors of 2 classes.
                frame_image = map_mask_as_display_bgr(masks)
                cv2.imwrite(folder_name + "/" + str(frame_number) + ".jpg", frame_image)
            try:
                l_user = l_user.next
            except StopIteration:
                break
        try:
            l_frame = l_frame.next
        except StopIteration:
            break
    return Gst.PadProbeReturn.OK


def main(args):
    # Check input arguments
    if len(args) != 4:
        sys.stderr.write("usage: %s config_file <jpeg/mjpeg file> "
                         "<path to save seg images>\n" % args[0])
        sys.exit(1)

    global folder_name
    folder_name = args[-1]
    if path.exists(folder_name):
        sys.stderr.write("The output folder %s already exists. "
                         "Please remove it first.\n" % folder_name)
        sys.exit(1)
    os.mkdir(folder_name)

    config_file = args[1]
    num_sources = len(args) - 3
    # Standard GStreamer initialization
    Gst.init(None)

    # Create gstreamer elements
    # Create Pipeline element that will form a connection of other elements
    print("Creating Pipeline \n ")
    pipeline = Gst.Pipeline()

    if not pipeline:
        sys.stderr.write(" Unable to create Pipeline \n")

    # Source element for reading from the file
    print("Creating Source \n ")
    source = Gst.ElementFactory.make("filesrc", "file-source")
    if not source:
        sys.stderr.write(" Unable to create Source \n")

    # Since the data format in the input file is jpeg,
    # we need a jpegparser
    print("Creating jpegParser \n")
    jpegparser = Gst.ElementFactory.make("jpegparse", "jpeg-parser")
    if not jpegparser:
        sys.stderr.write("Unable to create jpegparser \n")

    # Use nvdec for hardware accelerated decode on GPU
    print("Creating Decoder \n")
    decoder = Gst.ElementFactory.make("nvv4l2decoder", "nvv4l2-decoder")
    if not decoder:
        sys.stderr.write(" Unable to create Nvv4l2 Decoder \n")

    # Create nvstreammux instance to form batches from one or more sources.
    streammux = Gst.ElementFactory.make("nvstreammux", "Stream-muxer")
    if not streammux:
        sys.stderr.write(" Unable to create NvStreamMux \n")

    # Create segmentation for primary inference
    seg = Gst.ElementFactory.make("nvinfer", "primary-nvinference-engine")
    if not seg:
        sys.stderr.write("Unable to create primary inferene\n")

    # Create nvsegvisual for visualizing segmentation
    nvsegvisual = Gst.ElementFactory.make("nvsegvisual", "nvsegvisual")
    if not nvsegvisual:
        sys.stderr.write("Unable to create nvsegvisual\n")

    if is_aarch64():
        transform = Gst.ElementFactory.make("nvegltransform", "nvegl-transform")

    print("Creating EGLSink \n")
    sink = Gst.ElementFactory.make("nveglglessink", "nvvideo-renderer")
    if not sink:
        sys.stderr.write(" Unable to create egl sink \n")

    print("Playing file %s " % args[2])
    source.set_property('location', args[2])
    if is_aarch64() and (args[2].endswith("mjpeg") or args[2].endswith("mjpg")):
        decoder.set_property('mjpeg', 1)
    streammux.set_property('width', 1920)
    streammux.set_property('height', 1080)
    streammux.set_property('batch-size', 1)
    streammux.set_property('batched-push-timeout', 4000000)
    seg.set_property('config-file-path', config_file)
    pgie_batch_size = seg.get_property("batch-size")
    if pgie_batch_size != num_sources:
        print("WARNING: Overriding infer-config batch-size", pgie_batch_size,
              " with number of sources ", num_sources,
              " \n")
        seg.set_property("batch-size", num_sources)
    nvsegvisual.set_property('batch-size', num_sources)
    nvsegvisual.set_property('width', 512)
    nvsegvisual.set_property('height', 512)
    sink.set_property("qos", 0)
    print("Adding elements to Pipeline \n")
    pipeline.add(source)
    pipeline.add(jpegparser)
    pipeline.add(decoder)
    pipeline.add(streammux)
    pipeline.add(seg)
    pipeline.add(nvsegvisual)
    pipeline.add(sink)
    if is_aarch64():
        pipeline.add(transform)

    # we link the elements together
    # file-source -> jpeg-parser -> nvv4l2-decoder ->
    # nvinfer -> nvsegvisual -> sink
    print("Linking elements in the Pipeline \n")
    source.link(jpegparser)
    jpegparser.link(decoder)

    sinkpad = streammux.get_request_pad("sink_0")
    if not sinkpad:
        sys.stderr.write(" Unable to get the sink pad of streammux \n")
    srcpad = decoder.get_static_pad("src")
    if not srcpad:
        sys.stderr.write(" Unable to get source pad of decoder \n")
    srcpad.link(sinkpad)
    streammux.link(seg)
    seg.link(nvsegvisual)
    if is_aarch64():
        nvsegvisual.link(transform)
        transform.link(sink)
    else:
        nvsegvisual.link(sink)
    # create an event loop and feed gstreamer bus mesages to it
    loop = GLib.MainLoop()
    bus = pipeline.get_bus()
    bus.add_signal_watch()
    bus.connect("message", bus_call, loop)

    # Lets add probe to get informed of the meta data generated, we add probe to
    # the src pad of the inference element
    seg_src_pad = seg.get_static_pad("src")
    if not seg_src_pad:
        sys.stderr.write(" Unable to get src pad \n")
    else:
        seg_src_pad.add_probe(Gst.PadProbeType.BUFFER, seg_src_pad_buffer_probe, 0)

    # List the sources
    print("Now playing...")
    for i, source in enumerate(args[1:-1]):
        if i != 0:
            print(i, ": ", source)

    print("Starting pipeline \n")
    # start play back and listed to events
    pipeline.set_state(Gst.State.PLAYING)
    try:
        loop.run()
    except:
        pass
    # cleanup
    pipeline.set_state(Gst.State.NULL)


if __name__ == '__main__':
    sys.exit(main(sys.argv))
