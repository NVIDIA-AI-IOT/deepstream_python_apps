#!/usr/bin/env python3

# SPDX-FileCopyrightText: Copyright (c) 2021-2023 NVIDIA CORPORATION & AFFILIATES. All rights reserved.
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

import pytest
import pyds

from tests.testcommon.frame_iterator import FrameIterator
from tests.testcommon.pipeline_fakesink import PipelineFakesink
from tests.testcommon.pipeline_fakesink_tracker import PipelineFakesinkTracker
from tests.testcommon.tracker_utils import get_tracker_properties_from_config
from tests.testcommon.utils import is_integrated_gpu

VIDEO_PATH1 = "/opt/nvidia/deepstream/deepstream/samples/streams/sample_720p.h264"
STANDARD_PROPERTIES1 = {
    "file-source": {
        "location": VIDEO_PATH1
    },
    "Stream-muxer": {
        "width": 1280,
        "height": 720,
        "batch-size": 1,
        "batched-push-timeout": 4000000
    },
    "primary-inference": {
        "config-file-path": "./ds_base_config.txt"
    }
}
STANDARD_PROPERTIES_TRACKER1 = {
    "file-source": {
        "location": VIDEO_PATH1
    },
    "Stream-muxer": {
        "width": 1280,
        "height": 720,
        "batch-size": 1,
        "batched-push-timeout": 4000000
    },
    "primary-inference": {
        "config-file-path": "ds_pgie_config.txt"
    },
    "secondary1-nvinference-engine": {
        "config-file-path", "ds_sgie1_config.txt"
    },
    "secondary2-nvinference-engine": {
        "config-file-path", "ds_sgie2_config.txt"
    }
}
STANDARD_CLASS_ID1 = {
    0: "vehicle",
    1: "person",
    2: "bicycle",
    3: "roadsign",
}


def test_pipeline1():
    ### INIT DATA

    # defining the function to be called at each frame
    def frame_function(batch_meta, frame_meta, dict_data):
        pass

    # defining the function to be called at each object
    def box_function(batch_meta, frame_meta, obj_meta, dict_data):
        obj_counter = dict_data["obj_counter"]
        pgie_class_id = dict_data["pgie_class_id"]
        obj_counter[pgie_class_id[obj_meta.class_id]] += 1

    # defining a shared data dictionary
    data_probe = {
        "pgie_class_id": STANDARD_CLASS_ID1,
        "obj_counter": {
            STANDARD_CLASS_ID1[0]: 0,
            STANDARD_CLASS_ID1[1]: 0,
            STANDARD_CLASS_ID1[2]: 0,
            STANDARD_CLASS_ID1[3]: 0
        }
    }
    # Creating the probe function
    probe_function = FrameIterator(frame_function, box_function, data_probe)

    # Creating the pipeline
    sp = PipelineFakesink(STANDARD_PROPERTIES1, is_integrated_gpu())
    # registering the probe function
    sp.set_probe(probe_function)

    ### LAUNCH BEHAVIOR
    # Running the pipeline
    sp.run()

    ### CHECK OUTPUT
    assert data_probe["obj_counter"]["person"] > 0
    assert data_probe["obj_counter"]["vehicle"] > 0
    assert data_probe["obj_counter"]["bicycle"] > 0


def test_pipeline2():
    ### INIT DATA

    # defining the function to be called at each frame
    def frame_function(batch_meta, frame_meta, dict_data):
        pass

    tracker_qty_expected = {
        "stream_id" : 1, # only one video
        "surface_stream_id" : 1,
        "numobj" : 22,
        "unique_id" : 317,
        "class_id": 3,
        "obj_label" : 3,
        "frame_num": 896,
        "tbox_left": 1340,
        "tbox_width" : 650,
        "tbox_top" : 1075,
        "tbox_right" : 488,
        "confidence": 464,
        "age": 464}

    def user_function(batch_meta, user_meta, dict_data):
        if not user_meta:
            return
        if not user_meta.base_meta.meta_type == pyds.NvDsMetaType.NVDS_TRACKER_PAST_FRAME_META:
            return
        miscDataBatch = pyds.NvDsTargetMiscDataBatch.cast(user_meta.user_meta_data)
        tracker_data = dict_data["tracker_data"]
        for miscDataStream in pyds.NvDsTargetMiscDataBatch.list(miscDataBatch):
            tracker_data["stream_id"].add(miscDataStream.streamID)
            tracker_data["surface_stream_id"].add(miscDataStream.surfaceStreamID)
            for miscDataObj in pyds.NvDsTargetMiscDataStream.list(miscDataStream):
                tracker_data["numobj"].add(miscDataObj.numObj)
                tracker_data["unique_id"].add(miscDataObj.uniqueId)
                tracker_data["class_id"].add(miscDataObj.classId)
                tracker_data["obj_label"].add(miscDataObj.objLabel)
                for miscDataFrame in pyds.NvDsTargetMiscDataObject.list(miscDataObj):
                    tracker_data["frame_num"].add(miscDataFrame.frameNum)
                    tracker_data["tbox_left"].add(miscDataFrame.tBbox.left)
                    tracker_data["tbox_width"].add(miscDataFrame.tBbox.width)
                    tracker_data["tbox_top"].add(miscDataFrame.tBbox.top)
                    tracker_data["tbox_right"].add(miscDataFrame.tBbox.height)
                    tracker_data["confidence"].add(miscDataFrame.confidence)
                    tracker_data["age"].add(miscDataFrame.confidence)

    # defining the function to be called at each object
    def box_function(batch_meta, frame_meta, obj_meta, dict_data):
        obj_counter = dict_data["obj_counter"]
        pgie_class_id = dict_data["pgie_class_id"]
        obj_counter[pgie_class_id[obj_meta.class_id]] += 1

    tracker_cfg = get_tracker_properties_from_config("ds_tracker_config.txt")
    properties = {
        "file-source": {
            "location": VIDEO_PATH1
        },
        "Stream-muxer": {
            "width": 1280,
            "height": 720,
            "batch-size": 1,
            "batched-push-timeout": 4000000
        },
        "primary-inference": {
            "config-file-path": "ds_pgie_config.txt"
        },
        "secondary1-nvinference-engine": {
            "config-file-path": "ds_sgie1_config.txt"
        },
        "secondary2-nvinference-engine": {
            "config-file-path": "ds_sgie2_config.txt"
        },
        "tracker": tracker_cfg
    }
    print(properties)
    # defining a shared data dictionary
    tracker_data = {}
    for elm in tracker_qty_expected.keys():
        tracker_data[elm] = set()
    data_probe = {
        "pgie_class_id": STANDARD_CLASS_ID1,
        "obj_counter": {
            STANDARD_CLASS_ID1[0]: 0,
            STANDARD_CLASS_ID1[1]: 0,
            STANDARD_CLASS_ID1[2]: 0,
            STANDARD_CLASS_ID1[3]: 0
        },
        "tracker_data": tracker_data
    }
    # Creating the probe function
    probe_function = FrameIterator(frame_function, box_function, data_probe,
                                   user_function)

    # Creating the pipeline
    sp = PipelineFakesinkTracker(properties, is_integrated_gpu())
    # registering the probe function
    sp.set_probe(probe_function)

    ### LAUNCH BEHAVIOR
    # Running the pipeline
    sp.run()

    ### CHECK OUTPUT
    for key, expected_qty in tracker_qty_expected.items():
        qty = len(data_probe["tracker_data"][key])
        assert qty > 0
