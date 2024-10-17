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
    def frame_function(batch_meta, frame_meta, dict_data, gst_buffer):
        pass

    # defining the function to be called at each object
    def box_function(batch_meta, frame_meta, obj_meta, dict_data, gst_buffer):
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
    def frame_function(batch_meta, frame_meta, dict_data, gst_buffer):
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

    def user_function(batch_meta, user_meta, dict_data, gst_buffer):
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
    def box_function(batch_meta, frame_meta, obj_meta, dict_data, gst_buffer):
        obj_counter = dict_data["obj_counter"]
        pgie_class_id = dict_data["pgie_class_id"]
        obj_counter[pgie_class_id[obj_meta.class_id]] += 1

        l_obj_user_meta = obj_meta.obj_user_meta_list
        while l_obj_user_meta is not None:
            try:
                user_meta=pyds.NvDsUserMeta.cast(l_obj_user_meta.data)
                if not user_meta.base_meta.meta_type == pyds.NvDsMetaType.NVDS_TRACKER_OBJ_REID_META:
                    continue
                reid=pyds.NvDsObjReid.cast(user_meta.user_meta_data)
                vec = reid.get_host_reid_vector()
                assert reid.featureSize == vec.size
                # print(f"reid featureSize {reid.featureSize} == {vec.__class__} == {vec.size}")
            except StopIteration:
                break
            try:
                l_obj_user_meta=l_obj_user_meta.next
            except StopIteration:
                break

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


def test_pipeline3():
    ### INIT DATA

    # Creating the pipeline
    sp = PipelineFakesink(STANDARD_PROPERTIES1, is_integrated_gpu())

    # Create Context for Object Encoding.
    # Takes GPU ID as a parameter.
    obj_ctx_handle = pyds.nvds_obj_enc_create_context (0)

    # defining the function to be called at each frame
    def frame_function(batch_meta, frame_meta, dict_data, gst_buffer):
        frame_number=frame_meta.frame_num
        if frame_number < 3:
            frameData = pyds.NvDsObjEncUsrArgs()
            frameData.isFrame = 1
            frameData.saveImg = False
            frameData.attachUsrMeta = True
            frameData.scaleImg = False
            frameData.scaledWidth = 0
            frameData.scaledHeight = 0
            frameData.quality = 80
            frameData.calcEncodeTime = 1
            pyds.nvds_obj_enc_process (obj_ctx_handle, frameData, hash(gst_buffer), None, frame_meta)

    # defining the function to be called at each object
    def box_function(batch_meta, frame_meta, obj_meta, dict_data, gst_buffer):
        count = 0
        frame_number=frame_meta.frame_num
        num_obj = frame_meta.num_obj_meta
        if frame_number < 3 and count == 0:
            count += 1
            objData = pyds.NvDsObjEncUsrArgs()
            objData.saveImg = False
            objData.attachUsrMeta = True
            objData.scaleImg = False
            objData.scaledWidth = 0
            objData.scaledHeight = 0
            objData.objNum = num_obj
            objData.quality = 80
            objData.calcEncodeTime = 1
            pyds.nvds_obj_enc_process (obj_ctx_handle, objData, hash(gst_buffer), obj_meta, frame_meta)

    def post_process(gst_buffer):
        pyds.nvds_obj_enc_finish(obj_ctx_handle)

    # Creating the probe function
    probe_function = FrameIterator(frame_function, box_function, None, None, post_process)
    # registering the probe function
    sp.set_fix_elem_probe("primary-inference", "src", probe_function)

    def frame_function2(batch_meta, frame_meta, dict_data, gst_buffer):
        fusrMetaList = frame_meta.frame_user_meta_list
        frame_number = frame_meta.frame_num
        while fusrMetaList is not None:
            try:
                fuser_meta = pyds.NvDsUserMeta.cast(fusrMetaList.data)
                if fuser_meta.base_meta.meta_type == pyds.NvDsMetaType.NVDS_CROP_IMAGE_META:
                    fenc_output = pyds.NvDsObjEncOutParams.cast(fuser_meta.user_meta_data)
                    foutput = fenc_output.outBuffer()
                    assert foutput is not None
                    foutput.tofile(f"frame-{frame_number}-out.jpg")
            except StopIteration:
                break
            try:
                fusrMetaList = fusrMetaList.next
            except StopIteration:
                break

    def box_function2(batch_meta, frame_meta, obj_meta, dict_data, gst_buffer):
        frame_number = frame_meta.frame_num
        usrMetaList = obj_meta.obj_user_meta_list
        count = 0
        while usrMetaList is not None:
            try:
                user_meta = pyds.NvDsUserMeta.cast(usrMetaList.data)
                if user_meta.base_meta.meta_type == pyds.NvDsMetaType.NVDS_CROP_IMAGE_META:
                    enc_output = pyds.NvDsObjEncOutParams.cast(user_meta.user_meta_data)
                    output = enc_output.outBuffer()
                    assert output is not None
                    output.tofile(f"frame-{frame_number}-obj-{count}-out.jpg")
                    count += 1
            except StopIteration:
                break
            try:
                usrMetaList = usrMetaList.next
            except StopIteration:
                break

    probe_function2 = FrameIterator(frame_function2, box_function2, None)
    sp.set_probe(probe_function2)

    ### LAUNCH BEHAVIOR
    # Running the pipeline
    sp.run()

    # Destroy context for Object Encoding
    pyds.nvds_obj_enc_destroy_context (obj_ctx_handle)
