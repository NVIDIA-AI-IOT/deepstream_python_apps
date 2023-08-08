#!/usr/bin/env python3

# SPDX-FileCopyrightText: Copyright (c) 2021 NVIDIA CORPORATION & AFFILIATES. All rights reserved.
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

import os
import sys
import gi

gi.require_version('Gst', '1.0')
from gi.repository import GObject, Gst

from tests.common.generic_pipeline import GenericPipeline


class PipelineFakesinkTracker(GenericPipeline):

    def __init__(self, properties, is_aarch64):
        pipeline_base = [
            ["filesrc", "file-source"],  # source
            ["h264parse", "h264-parser"],  # h264parser
            ["nvv4l2decoder", "nvv4l2-decoder"],  # decoder
            ["nvstreammux", "Stream-muxer"],  # streammux
            ["nvinfer", "primary-inference"],  # pgie
            ["nvtracker", "tracker"],  # tracker
            ["nvinfer", "secondary1-nvinference-engine"],  # sgie1
            ["nvinfer", "secondary2-nvinference-engine"],  # sgie2
            ["nvinfer", "secondary3-nvinference-engine"],  # sgie3
            ["nvvideoconvert", "convertor"],  # nvvidconv
            ["nvdsosd", "onscreendisplay"],  # nvosd
            ["fakesink", "fakesink"],  # sink
        ]
        pipeline_arm64 = [
        ]
        super().__init__(properties, is_aarch64, pipeline_base,
                         pipeline_arm64)

    def set_probe(self, probe_function):
        nvosd = self._get_elm_by_name("onscreendisplay")
        osdsinkpad = nvosd.get_static_pad("sink")
        if not osdsinkpad:
            sys.stderr.write("Unable to get sink pad of nvosd \n")

        osdsinkpad.add_probe(Gst.PadProbeType.BUFFER, probe_function, 0)

    def _link_elements(self):
        gebn = lambda n: self._get_elm_by_name(n)
        source = gebn("file-source")
        h264parser = gebn("h264-parser")
        decoder = gebn("nvv4l2-decoder")
        streammux = gebn("Stream-muxer")
        pgie = gebn("primary-inference")
        tracker = gebn("tracker")
        sgie1 = gebn("secondary1-nvinference-engine")
        sgie2 = gebn("secondary2-nvinference-engine")
        sgie3 = gebn("secondary3-nvinference-engine")
        nvvidconv = gebn("convertor")
        nvosd = gebn("onscreendisplay")
        sink = gebn("fakesink")

        source.link(h264parser)
        h264parser.link(decoder)

        srcpad = decoder.get_static_pad("src")
        if not srcpad:
            sys.stderr.write(" Unable to get source pad of decoder \n")
            return False

        sinkpad = streammux.get_request_pad("sink_0")
        if not sinkpad:
            sys.stderr.write(" Unable to get the sink pad of streammux \n")
            return False

        srcpad.link(sinkpad)
        streammux.link(pgie)
        pgie.link(tracker)
        tracker.link(sgie1)
        sgie1.link(sgie2)
        sgie2.link(sgie3)
        sgie3.link(nvvidconv)
        nvvidconv.link(nvosd)
        nvosd.link(sink)
        return True
