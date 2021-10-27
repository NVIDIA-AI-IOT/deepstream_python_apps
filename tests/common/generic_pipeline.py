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

import sys

sys.path.append('../')
import gi

gi.require_version('Gst', '1.0')
from gi.repository import Gst, GLib
from tests.common.utils import bus_call


class PipelineElement:
    """ Element containing information about gst element
    """

    def __init__(self, elm_type, name):
        self.type = elm_type
        self.name = name
        self.content = Gst.ElementFactory.make(elm_type, name)
        if not self.content:
            raise Exception(f"Unable to create {name} \n")


class GenericPipeline:
    """ Generic pipeline that must be derived to add
    its content. There are
    """

    def __init__(self, properties, is_aarch64, data_pipeline,
                 data_pipeline_arm64):
        self._pipeline = None
        self._loop = None
        self._pipeline_content = {}
        self._properties = properties
        self._is_aarch64 = is_aarch64
        self._data_pipeline = data_pipeline
        self._data_pipeline_arm64 = data_pipeline_arm64
        # Standard GStreamer initialization
        Gst.init(None)

        if not self._create_pipeline():
            raise Exception("Could not create pipeline")

        # create an event loop and feed gstreamer bus mesages to it
        self._loop = GLib.MainLoop()
        bus = self._pipeline.get_bus()
        bus.add_signal_watch()
        bus.connect("message", bus_call, self._loop)

    def _set_property(self, name, dict_properties):
        pe = self._get_elm_by_name(name)
        for key, val in dict_properties.items():
            pe.set_property(key, val)

    def _get_elm_by_name(self, name):
        if name not in self._pipeline_content:
            raise Exception(f"Element \"{name}\" does not exist in pipeline")
        return self._pipeline_content[name].content

    def _link_elements(self):
        raise Exception("Generic class call not allowed")

    def _set_properties(self, property_dict):
        for name, content in property_dict.items():
            self._set_property(name, content)

    def set_probe(self, probe_function):
        raise Exception("Generic class call not allowed")

    def _create_element(self, elm):
        if elm[1] in self._pipeline_content:
            raise Exception(f"An element named {elm[1]} already exist"
                            f" in pipeline")
        self._pipeline_content[elm[1]] = PipelineElement(elm[0], elm[1])

    def _add_all_elements_to_pipeline(self):
        for elm in self._pipeline_content.values():
            self._pipeline.add(elm.content)

    def _create_pipeline(self):
        self._pipeline = Gst.Pipeline()
        if not self._pipeline:
            sys.stderr.write(" Unable to create Pipeline \n")

        for elm in self._data_pipeline:
            self._create_element(elm)

        if self._is_aarch64:
            for elm in self._data_pipeline_arm64:
                self._create_element(elm)

        self._set_properties(self._properties)

        self._add_all_elements_to_pipeline()

        if not self._link_elements():
            sys.stderr.write("Could not link elements")
            return False

        return True

    def run(self):
        print("Starting pipeline \n")
        self._pipeline.set_state(Gst.State.PLAYING)
        self._loop.run()
        self._pipeline.set_state(Gst.State.NULL)
