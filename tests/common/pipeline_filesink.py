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


class PipelineFileSink(GenericPipeline):

    def __init__(self, properties, is_aarch64):
        pipeline_base = [
            ["filesrc", "file-source"],  # source
            ["h264parse", "h264-parser"],  # h264parser
            ["nvv4l2decoder", "nvv4l2-decoder"],  # decoder
            ["nvstreammux", "Stream-muxer"],  # streammux
            ["nvinfer", "primary-inference"],  # pgie
            ["nvvideoconvert", "convertor"],  # nvvidconv
            ["nvdsosd", "onscreendisplay"],  # nvosd
            ["queue", "queue"],  # queue
            ["nvvideoconvert", "convertor2"],  # nvvidconv2
            ["capsfilter", "capsfilter"],  # capsfilter
            ["avenc_mpeg4", "encoder"],  # encoder
            ["mpeg4videoparse", "mpeg4-parser"],  # codeparser
            ["qtmux", "qtmux"],  # container
            ["filesink", "filesink"],  # sink
        ]
        pipeline_arm64 = [
            ["nvegltransform", "nvegl-transform"]  # transform
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
        nvvidconv = gebn("convertor")
        nvosd = gebn("onscreendisplay")
        queue = gebn("queue")
        nvvidconv2 = gebn("convertor2")
        capsfilter = gebn("capsfilter")
        encoder = gebn("encoder")
        codeparser = gebn("mpeg4-parser")
        container = gebn("qtmux")
        sink = gebn("filesink")

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

        caps = Gst.Caps.from_string("video/x-raw, format=I420")
        capsfilter.set_property("caps", caps)

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
        if self._is_aarch64:
            transform = gebn("nvegl-transform")
            nvosd.link(transform)
            transform.link(sink)
        else:
            nvosd.link(sink)
        return True
