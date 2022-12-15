#!/usr/bin/env python3

################################################################################
# SPDX-FileCopyrightText: Copyright (c) 2022 NVIDIA CORPORATION & AFFILIATES. All rights reserved.
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
import os
import gi

gi.require_version('Gst', '1.0')
from gi.repository import Gst, GLib

import pyds

def bus_call(bus, message, loop):
    t = message.type
    if t == Gst.MessageType.EOS:
        Gst.info("End-of-stream")
        loop.quit()
    elif t == Gst.MessageType.WARNING:
        err, debug = message.parse_warning()
        Gst.warning("Warning: %s: %s" % (err, debug))
    elif t == Gst.MessageType.ERROR:
        err, debug = message.parse_error()
        Gst.error("Error: %s: %s" % (err, debug))
        loop.quit()
    return True

def streammux_src_pad_buffer_probe(pad, info, u_data):
    gst_buffer = info.get_buffer()
    if not gst_buffer:
        Gst.warning("Unable to get GstBuffer ")
        return

    batch_meta = pyds.gst_buffer_get_nvds_batch_meta(hash(gst_buffer))
    if not batch_meta:
        return Gst.PadProbeReturn.OK

    pyds.nvds_acquire_meta_lock(batch_meta)

    l_frame = batch_meta.frame_meta_list
    while l_frame is not None:
        try:
            frame_meta = pyds.NvDsFrameMeta.cast(l_frame.data)
            frame_number = frame_meta.frame_num
        except StopIteration:
            continue

        user_meta = pyds.nvds_acquire_user_meta_from_pool(batch_meta)

        if user_meta:
            print('adding user meta')
            test_string = 'test message ' + str(frame_number)
            data = pyds.alloc_custom_struct(user_meta)
            data.message = test_string
            data.message = pyds.get_string(data.message)
            data.structId = frame_number
            data.sampleInt = frame_number + 1

            user_meta.user_meta_data = data
            user_meta.base_meta.meta_type = pyds.NvDsMetaType.NVDS_USER_META

            pyds.nvds_add_user_meta_to_frame(frame_meta, user_meta)
        else:
            print('failed to acquire user meta')

        try:
            l_frame = l_frame.next
        except StopIteration:
            break

    pyds.nvds_release_meta_lock(batch_meta)
    return Gst.PadProbeReturn.OK


def fakesink_sink_pad_buffer_probe(pad, info, u_data):
    gst_buffer = info.get_buffer()
    if not gst_buffer:
        print("Unable to get GstBuffer ")
        return
    batch_meta = pyds.gst_buffer_get_nvds_batch_meta(hash(gst_buffer))

    if not batch_meta:
        return Gst.PadProbeReturn.OK

    pyds.nvds_acquire_meta_lock(batch_meta)

    l_frame = batch_meta.frame_meta_list
    while l_frame is not None:
        try:
            frame_meta = pyds.NvDsFrameMeta.cast(l_frame.data)
        except StopIteration:
            continue

        l_usr = frame_meta.frame_user_meta_list
        while l_usr is not None:
            try:
                user_meta = pyds.NvDsUserMeta.cast(l_usr.data)
            except StopIteration:
                continue

            if user_meta.base_meta.meta_type == pyds.NvDsMetaType.NVDS_USER_META:
                custom_msg_meta = pyds.CustomDataStruct.cast(user_meta.user_meta_data)
                Gst.info(f'event msg meta, otherAttrs = {pyds.get_string(custom_msg_meta.message)}')
                print('custom meta structId:: ', custom_msg_meta.structId)
                print('custom meta msg:: ', pyds.get_string(custom_msg_meta.message))
                print('custom meta sampleInt:: ', custom_msg_meta.sampleInt)
            try:
                l_usr = l_usr.next
            except StopIteration:
                break

        try:
            l_frame = l_frame.next
        except StopIteration:
            break

    pyds.nvds_release_meta_lock(batch_meta)
    return Gst.PadProbeReturn.OK


def main(args):
    # Check input arguments
    if len(args) != 2:
        sys.stderr.write("usage: %s <h264 stream file or uri>\n" % args[0])
        sys.exit(1)

    Gst.init(None)

    pipeline = Gst.Pipeline()
    if not pipeline:
        Gst.error(" Unable to create Pipeline")

    source = Gst.ElementFactory.make("filesrc", "file-source")
    if not source:
        Gst.error(" Unable to create Source")

    h264parser = Gst.ElementFactory.make("h264parse", "h264-parser")
    if not h264parser:
        Gst.error(" Unable to create h264 parser")

    decoder = Gst.ElementFactory.make("nvv4l2decoder", "nvv4l2-decoder")
    if not decoder:
        Gst.error(" Unable to create Nvv4l2 Decoder")

    streammux = Gst.ElementFactory.make("nvstreammux", "Stream-muxer")
    if not streammux:
        Gst.error(" Unable to create NvStreamMux")

    queue = Gst.ElementFactory.make("queue", "queue")
    if not queue:
        Gst.error(" Unable to create queue")
    queue1 = Gst.ElementFactory.make("queue", "queue1")
    if not queue1:
        Gst.error(" Unable to create queue")
    sink = Gst.ElementFactory.make("fakesink", "fakesink")
    if not sink:
        sys.stderr.write(" Unable to create fake sink \n")
    print("reading input")
    print("Playing file %s " %args[1])
    source.set_property('location', args[1])

    streammux.set_property('width', 1280)
    streammux.set_property('height', 720)
    streammux.set_property('batch-size', 1)

    Gst.info("Adding elements to Pipeline")
    pipeline.add(source)
    pipeline.add(h264parser)
    pipeline.add(decoder)
    pipeline.add(streammux)
    pipeline.add(queue)
    pipeline.add(queue1)
    pipeline.add(sink)

    Gst.info("Linking elements in the Pipeline")
    source.link(h264parser)
    h264parser.link(decoder)

    sinkpad = streammux.get_request_pad("sink_0")
    if not sinkpad:
        Gst.error(" Unable to get the sink pad of streammux")

    srcpad = decoder.get_static_pad("src")
    if not srcpad:
        Gst.error(" Unable to get source pad of decoder(source)")
    srcpad.link(sinkpad)

    streammux.link(queue)
    queue.link(queue1)
    queue1.link(sink)

    loop = GLib.MainLoop()
    bus = pipeline.get_bus()
    bus.add_signal_watch()
    bus.connect("message", bus_call, loop)

    streammux_src_pad = streammux.get_static_pad('src')
    if not streammux_src_pad:
        Gst.error(" Unable to get src pad of streammux")
    streammux_src_pad.add_probe(Gst.PadProbeType.BUFFER, streammux_src_pad_buffer_probe, 0)

    fakesink_sink_pad = sink.get_static_pad('sink')
    if not fakesink_sink_pad:
        Gst.error(" Unable to get sink pad of fakesink")
    fakesink_sink_pad.add_probe(Gst.PadProbeType.BUFFER, fakesink_sink_pad_buffer_probe, 0)
    Gst.debug_bin_to_dot_file(pipeline, Gst.DebugGraphDetails.ALL, 'graph')
    Gst.info("Starting pipeline")

    pipeline.set_state(Gst.State.PLAYING)
    print("pipeline playing")
    try:
        loop.run()
    except:
        pass
    # cleanup
    pipeline.set_state(Gst.State.NULL)


if __name__ == '__main__':
    sys.exit(main(sys.argv))