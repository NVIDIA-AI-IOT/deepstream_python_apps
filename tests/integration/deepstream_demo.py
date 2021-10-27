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

sys.path.append('../..')

from tests.common.utils import is_aarch64, load_deepstream_libs
from tests.common.pipeline_filesink import PipelineFileSink
from tests.common.frame_iterator import FrameIterator

import pyds


def make_text_display(display_meta, frame_number, num_rects, obj_counter):
    display_meta.num_labels = 1
    py_nvosd_text_params = display_meta.text_params[0]
    disp_txt = f"Frame Number={frame_number} " \
               f"Number of Objects={num_rects} " \
               f"Vehicle_count={obj_counter['vehicle']} " \
               f"Person_count={obj_counter['person']}"
    py_nvosd_text_params.display_text = disp_txt

    # Now set the offsets where the string should appear
    py_nvosd_text_params.x_offset = 10
    py_nvosd_text_params.y_offset = 12

    # Font , font-color and font-size
    py_nvosd_text_params.font_params.font_name = "Consolas"
    py_nvosd_text_params.font_params.font_size = 10
    # set(red, green, blue, alpha); set to White
    py_nvosd_text_params.font_params.font_color.set(1.0, 1.0, 1.0, 1.0)

    # Text background color
    py_nvosd_text_params.set_bg_clr = 1
    # set(red, green, blue, alpha); set to Black
    py_nvosd_text_params.text_bg_clr.set(0.0, 0.0, 0.0, 1.0)


def frame_function(batch_meta, frame_meta, dict_data):
    obj_counter = dict_data["obj_counter"]
    pgie_class_id = dict_data["pgie_class_id"]
    frame_number = frame_meta.frame_num
    num_rects = frame_meta.num_obj_meta
    display_meta = pyds.nvds_acquire_display_meta_from_pool(
        batch_meta)
    make_text_display(display_meta, frame_number, num_rects, obj_counter)
    # Using pyds.get_string() to get display_text as string
    py_nvosd_text_params = display_meta.text_params[0]
    print(pyds.get_string(py_nvosd_text_params.display_text))
    pyds.nvds_add_display_meta_to_frame(frame_meta, display_meta)


def box_function(batch_meta, frame_meta, obj_meta, dict_data):
    obj_counter = dict_data["obj_counter"]
    pgie_class_id = dict_data["pgie_class_id"]
    obj_counter[pgie_class_id[obj_meta.class_id]] += 1
    obj_meta.rect_params.border_color.set(0.0, 0.0, 1.0, 0.0)


def parse_input(args):
    # Check input arguments
    if len(args) != 3:
        sys.stderr.write(f"usage: {args[0]} <video.h264> <config_file.txt> \n")
        sys.exit(1)

    video_path = args[1]
    if not os.path.isfile(video_path):
        raise Exception(f"{video_path} is not a file")
    config_file = args[2]
    if not os.path.isfile(config_file):
        raise Exception(f"{config_file} is not a file")

    return config_file, video_path


def make_and_run_pipeline(config_file, video_path):
    properties = {
        "file-source": {
            "location": video_path
        },
        "Stream-muxer": {
            "width": 1280,
            "height": 720,
            "batch-size": 1,
            "batched-push-timeout": 4000000
        },
        "primary-inference": {
            "config-file-path": config_file
        },
        "filesink": {
            "location": "./out.mp4",
            "sync": 0,
            "async": 0,
        },
        "encoder": {
            "bitrate": 2000000
        }

    }

    pgie_class_id = {
        0: "vehicle",
        1: "person",
        2: "bicycle",
        3: "roadsign",
    }
    data_probe = {
        "pgie_class_id": pgie_class_id,
        "obj_counter": {
            pgie_class_id[0]: 0,
            pgie_class_id[1]: 0,
            pgie_class_id[2]: 0,
            pgie_class_id[3]: 0
        }
    }
    probe_function = FrameIterator(frame_function, box_function, data_probe)

    sp = PipelineFileSink(properties, is_aarch64())
    sp.set_probe(probe_function)
    sp.run()


def main(args):
    config_file, video_path = parse_input(args)
    load_deepstream_libs()
    make_and_run_pipeline(config_file, video_path)


if __name__ == '__main__':
    sys.exit(main(sys.argv))
