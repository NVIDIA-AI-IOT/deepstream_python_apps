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

import pyds
import gi

gi.require_version('Gst', '1.0')
from gi.repository import GObject, Gst


class FrameIterator:

    def __init__(self, fun_frame, fun_obj, data_dict, fun_user=None):
        self._fun_frame = fun_frame
        self._fun_obj = fun_obj
        self._fun_user = fun_user
        self._data_dict = data_dict

    def _process_frame_function(self, batch_meta, frame_meta):

        self._fun_frame(batch_meta, frame_meta, self._data_dict)

    def _process_obj_function(self, batch_meta, frame_meta, obj_meta):
        self._fun_obj(batch_meta, frame_meta, obj_meta, self._data_dict)

    def _process_user_function(self, batch_meta, user_meta):
        if self._fun_user:
            self._fun_user(batch_meta, user_meta, self._data_dict)

    def __call__(self, pad, info, u_data):

        gst_buffer = info.get_buffer()
        if not gst_buffer:
            print("Unable to get GstBuffer ")
            return

        batch_meta = pyds.gst_buffer_get_nvds_batch_meta(hash(gst_buffer))
        l_frame = batch_meta.frame_meta_list
        while l_frame is not None:
            try:
                frame_meta = pyds.NvDsFrameMeta.cast(l_frame.data)
            except StopIteration:
                break

            l_obj = frame_meta.obj_meta_list
            while l_obj is not None:
                try:
                    obj_meta = pyds.NvDsObjectMeta.cast(l_obj.data)
                except StopIteration:
                    break
                self._process_obj_function(batch_meta, frame_meta, obj_meta)

                try:
                    l_obj = l_obj.next
                except StopIteration:
                    break

            self._process_frame_function(batch_meta, frame_meta)

            try:
                l_frame = l_frame.next
            except StopIteration:
                break

        l_user = batch_meta.batch_user_meta_list
        while l_user is not None:
            try:
                user_meta = pyds.NvDsUserMeta.cast(l_user.data)
            except StopIteration:
                break
            self._process_user_function(batch_meta, user_meta)
            try:
                l_user = l_user.next
            except StopIteration:
                break

        return Gst.PadProbeReturn.OK
