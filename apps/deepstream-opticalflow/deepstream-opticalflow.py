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
""" Deepstream optical flow application
"""

import math
import os
from os import path
import sys

sys.path.append('../')
import cv2
import numpy as np

import gi

gi.require_version('Gst', '1.0')
from gi.repository import GLib, Gst

from common.is_aarch_64 import is_aarch64
from common.bus_call import bus_call
import pyds

MAX_DISPLAY_LEN = 64
MUXER_OUTPUT_WIDTH = 1280
MUXER_OUTPUT_HEIGHT = 720
MUXER_BATCH_TIMEOUT_USEC = 3400000
TILED_OUTPUT_WIDTH = 1280
TILED_OUTPUT_HEIGHT = 720
GST_CAPS_FEATURES_NVMM = "memory:NVMM"


def visualize_optical_flowvectors(flow):
    """
    Converts the flow u, v vectors into visualization by mapping them into
    grey color space
    :param flow: flow vectors
    :return: bgr image
    """
    shape_visual = (flow.shape[0], flow.shape[1], 3)
    mag, ang = cv2.cartToPolar(flow[..., 0], flow[..., 1])
    hsv = np.full(shape_visual, 255, dtype=np.uint8)
    hsv[..., 1] = 255
    hsv[..., 0] = ang * 180 / np.pi / 2
    hsv[..., 2] = cv2.normalize(mag, None, 0, 255, cv2.NORM_MINMAX)
    bgr = cv2.cvtColor(hsv, cv2.COLOR_HSV2BGR)
    bgr = 255 - bgr
    return bgr


# tiler_sink_pad_buffer_probe  will extract metadata received on OSD sink pad
def ofvisual_queue_src_pad_buffer_probe(pad, info, u_data):
    got_visual = False
    frame_number = 0
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
            # The casting is done by pyds.glist_get_nvds_frame_meta()
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
                # Casting l_user.data to pyds.NvDsUserMeta
                of_user_meta = pyds.NvDsUserMeta.cast(l_user.data)
            except StopIteration:
                break
            try:
                # Casting of_user_meta.user_meta_data to pyds.NvDsOpticalFlowMeta
                of_meta = pyds.NvDsOpticalFlowMeta.cast(of_user_meta.user_meta_data)
                # Get Flow vectors
                flow_vectors = pyds.get_optical_flow_vectors(of_meta)
                # Reshape the obtained flow vectors into proper shape
                flow_vectors = flow_vectors.reshape(of_meta.rows, of_meta.cols, 2)
                # map the flow vectors in HSV color space for visualization
                flow_visual = visualize_optical_flowvectors(flow_vectors)
                got_visual = True
            except StopIteration:
                break
            try:
                l_user = l_user.next
            except StopIteration:
                break

        print("Frame Number=", frame_number)
        if got_visual:
            cv2.imwrite(folder_name + "/stream_" + str(frame_meta.pad_index)
                        + "/frame_" + str(frame_number) + ".jpg", flow_visual)
        try:
            l_frame = l_frame.next
        except StopIteration:
            break

    return Gst.PadProbeReturn.OK


def cb_newpad(decodebin, decoder_src_pad, data):
    print("In cb_newpad\n")
    caps = decoder_src_pad.get_current_caps()
    gststruct = caps.get_structure(0)
    gstname = gststruct.get_name()
    source_bin = data
    features = caps.get_features(0)

    # Need to check if the pad created by the decodebin is for video and not
    # audio.
    print("gstname=", gstname)
    if gstname.find("video") != -1:
        # Link the decodebin pad only if decodebin has picked nvidia
        # decoder plugin nvdec_*. We do this by checking if the pad caps contain
        # NVMM memory features.
        print("features=", features)
        if features.contains("memory:NVMM"):
            # Get the source bin ghost pad
            bin_ghost_pad = source_bin.get_static_pad("src")
            if not bin_ghost_pad.set_target(decoder_src_pad):
                sys.stderr.write("Failed to link decoder src pad to source bin ghost pad\n")
        else:
            sys.stderr.write(" Error: Decodebin did not pick nvidia decoder plugin.\n")


def decodebin_child_added(child_proxy, Object, name, user_data):
    print("Decodebin child added:", name, "\n")
    if name.find("decodebin") != -1:
        Object.connect("child-added", decodebin_child_added, user_data)


def create_source_bin(index, uri):
    print("Creating source bin")

    # Create a source GstBin to abstract this bin's content from the rest of the
    # pipeline
    bin_name = "source-bin-%02d" % index
    print(bin_name)
    nbin = Gst.Bin.new(bin_name)
    if not nbin:
        sys.stderr.write(" Unable to create source bin \n")

    # Source element for reading from the uri.
    # We will use decodebin and let it figure out the container format of the
    # stream and the codec and plug the appropriate demux and decode plugins.
    uri_decode_bin = Gst.ElementFactory.make("uridecodebin", "uri-decode-bin")
    if not uri_decode_bin:
        sys.stderr.write(" Unable to create uri decode bin \n")
    # We set the input uri to the source element
    uri_decode_bin.set_property("uri", uri)
    # Connect to the "pad-added" signal of the decodebin which generates a
    # callback once a new pad for raw data has beed created by the decodebin
    uri_decode_bin.connect("pad-added", cb_newpad, nbin)
    uri_decode_bin.connect("child-added", decodebin_child_added, nbin)

    # We need to create a ghost pad for the source bin which will act as a proxy
    # for the video decoder src pad. The ghost pad will not have a target right
    # now. Once the decode bin creates the video decoder and generates the
    # cb_newpad callback, we will set the ghost pad target to the video decoder
    # src pad.
    Gst.Bin.add(nbin, uri_decode_bin)
    bin_pad = nbin.add_pad(Gst.GhostPad.new_no_target("src", Gst.PadDirection.SRC))
    if not bin_pad:
        sys.stderr.write(" Failed to add ghost pad in source bin \n")
        return None
    return nbin


def main(args):
    # Check input arguments
    if len(args) < 2:
        sys.stderr.write("usage: %s <uri1> [uri2] ... [uriN] <output_folder>\n" % args[0])
        sys.exit(1)

    number_sources = len(args) - 2
    global folder_name
    folder_name = args[-1]
    if path.exists(folder_name):
        sys.stderr.write("The output folder %s already exists. Please remove"
                         " it first.\n" % folder_name)
        sys.exit(1)

    os.mkdir(folder_name)
    # Standard GStreamer initialization
    Gst.init(None)

    # Create gstreamer elements */
    # Create Pipeline element that will form a connection of other elements
    print("Creating Pipeline \n ")
    pipeline = Gst.Pipeline()

    if not pipeline:
        sys.stderr.write(" Unable to create Pipeline \n")
    print("Creating streamux \n ")

    # Create nvstreammux instance to form batches from one or more sources.
    streammux = Gst.ElementFactory.make("nvstreammux", "Stream-muxer")
    if not streammux:
        sys.stderr.write(" Unable to create NvStreamMux \n")

    pipeline.add(streammux)
    for i in range(number_sources):
        print("Creating source_bin ", i, " \n ")
        uri_name = args[i + 1]
        os.mkdir(folder_name + "/stream_" + str(i))
        source_bin = create_source_bin(i, uri_name)
        if not source_bin:
            sys.stderr.write("Unable to create source bin \n")
        pipeline.add(source_bin)
        padname = "sink_%u" % i
        sinkpad = streammux.get_request_pad(padname)
        if not sinkpad:
            sys.stderr.write("Unable to create sink pad bin \n")
        srcpad = source_bin.get_static_pad("src")
        if not srcpad:
            sys.stderr.write("Unable to create src pad bin \n")
        srcpad.link(sinkpad)

    print("Creating tiler \n ")
    tiler = Gst.ElementFactory.make("nvmultistreamtiler", "nvtiler")
    if not tiler:
        sys.stderr.write(" Unable to create tiler \n")
    print("Creating nv optical flow element \n")
    nvof = Gst.ElementFactory.make("nvof", "nvopticalflow")
    if not nvof:
        sys.stderr.write("Unable to create optical flow \n")
    print("Creating nv optical flow visualisation element \n")
    nvofvisual = Gst.ElementFactory.make("nvofvisual", "nvopticalflowvisual")
    if not nvofvisual:
        sys.stderr.write("Unable to create flow visualisation element")
    print("Creating queue \n ")
    of_queue = Gst.ElementFactory.make("queue", "q_after_of")
    if not of_queue:
        sys.stderr.write("Unable to create queue \n")
    print("Creating queue \n")
    ofvisual_queue = Gst.ElementFactory.make("queue", "q_after_ofvisual")
    if not ofvisual_queue:
        sys.stderr.write("Unable to create queue \n")

    print("Creating Queue \n")
    queue = Gst.ElementFactory.make("queue", "queue")
    if not queue:
        sys.stderr.write(" Unable to create queue \n")
    print("Creating nvosd \n ")
    nvosd = Gst.ElementFactory.make("nvdsosd", "onscreendisplay")
    if not nvosd:
        sys.stderr.write(" Unable to create nvosd \n")
    print("Creating converter 2\n")
    nvvidconv2 = Gst.ElementFactory.make("nvvideoconvert", "convertor2")
    if not nvvidconv2:
        sys.stderr.write(" Unable to create nvvidconv2 \n")
    print("Creating capsfilter \n")
    capsfilter = Gst.ElementFactory.make("capsfilter", "capsfilter")
    if not capsfilter:
        sys.stderr.write(" Unable to create capsfilter \n")
    caps = Gst.Caps.from_string("video/x-raw, format=I420")
    capsfilter.set_property("caps", caps)
    print("Creating Encoder \n")
    encoder = Gst.ElementFactory.make("avenc_mpeg4", "encoder")
    if not encoder:
        sys.stderr.write(" Unable to create encoder \n")
    encoder.set_property("bitrate", 2000000)
    print("Creating Code Parser \n")
    codeparser = Gst.ElementFactory.make("mpeg4videoparse", "mpeg4-parser")
    if not codeparser:
        sys.stderr.write(" Unable to create code parser \n")
    print("Creating Container \n")
    container = Gst.ElementFactory.make("qtmux", "qtmux")
    if not container:
        sys.stderr.write(" Unable to create code parser \n")
    print("Creating File Sink \n")
    sink = Gst.ElementFactory.make("filesink", "filesink")
    if not sink:
        sys.stderr.write(" Unable to create file sink \n")
    sink.set_property("location", "./out.mp4")
    sink.set_property("sync", 0)
    streammux.set_property('width', 1280)
    streammux.set_property('height', 720)
    streammux.set_property('batch-size', number_sources)
    streammux.set_property('batched-push-timeout', 33333)
    streammux.set_property('sync-inputs', 1)
    tiler_rows = int(math.sqrt(number_sources))
    tiler_columns = int(math.ceil((1.0 * number_sources) / tiler_rows))
    tiler.set_property("rows", tiler_rows)
    tiler.set_property("columns", tiler_columns)
    tiler.set_property("width", TILED_OUTPUT_WIDTH)
    tiler.set_property("height", TILED_OUTPUT_HEIGHT)

    print("Adding elements to Pipeline \n")
    pipeline.add(nvof)
    pipeline.add(of_queue)
    pipeline.add(nvofvisual)
    pipeline.add(ofvisual_queue)
    pipeline.add(tiler)
    pipeline.add(nvosd)
    pipeline.add(queue)
    pipeline.add(nvvidconv2)
    pipeline.add(capsfilter)
    pipeline.add(encoder)
    pipeline.add(codeparser)
    pipeline.add(container)
    pipeline.add(sink)

    print("Linking elements in the Pipeline \n")
    streammux.link(nvof)
    nvof.link(of_queue)
    of_queue.link(nvofvisual)
    nvofvisual.link(ofvisual_queue)
    ofvisual_queue.link(tiler)
    tiler.link(nvosd)
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
    ofvisual_queue_src_pad = ofvisual_queue.get_static_pad("src")
    if not ofvisual_queue_src_pad:
        sys.stderr.write(" Unable to get src pad \n")
    else:
        ofvisual_queue_src_pad.add_probe(Gst.PadProbeType.BUFFER,
                                         ofvisual_queue_src_pad_buffer_probe,
                                         0)

    # List the sources
    print("Now playing...")
    for i, source in enumerate(args[:-1]):
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
    print("Exiting app\n")
    pipeline.set_state(Gst.State.NULL)


if __name__ == '__main__':
    sys.exit(main(sys.argv))
