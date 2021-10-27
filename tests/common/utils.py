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

import ctypes
import platform
import sys
import time
import gi

gi.require_version('Gst', '1.0')
from gi.repository import GObject, Gst


def bus_call(bus, message, loop):
    t = message.type
    if t == Gst.MessageType.EOS:
        sys.stdout.write("End-of-stream\n")
        loop.quit()
    elif t == Gst.MessageType.WARNING:
        err, debug = message.parse_warning()
        sys.stderr.write("Warning: %s: %s\n" % (err, debug))
    elif t == Gst.MessageType.ERROR:
        err, debug = message.parse_error()
        sys.stderr.write("Error: %s: %s\n" % (err, debug))
        loop.quit()
    return True

class FPSCounter:
    def __init__(self, stream_id):
        self.start_time = time.time()
        self.is_first = True
        self.frame_count = 0
        self.stream_id = stream_id

    def get_fps(self):
        end_time = time.time()
        if self.is_first:
            self.start_time = end_time
            self.is_first = False
        if end_time - self.start_time > 5:
            print("**********************FPS*****************************************")
            print("Fps of stream", self.stream_id, "is ", float(self.frame_count) / 5.0)
            self.frame_count = 0
            self.start_time = end_time
        else:
            self.frame_count = self.frame_count + 1

    def print_data(self):
        print('frame_count=', self.frame_count)
        print('start_time=', self.start_time)


def load_deepstream_libs():
    sys.path.append('/opt/nvidia/deepstream/deepstream/lib')


def is_aarch64():
    return platform.uname()[4] == 'aarch64'


def long_to_int(l):
    value = ctypes.c_int(l & 0xffffffff).value
    return value
