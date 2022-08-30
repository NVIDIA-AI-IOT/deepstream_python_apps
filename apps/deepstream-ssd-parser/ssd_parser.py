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

"""
    Simple python SSD output parser.
    The function `nvds_infer_parse_custom_tf_ssd` should be used.
"""

import sys
import pyds
from nms import cluster_and_fill_detection_output_nms


class BoxSizeParam:
    """ Class contaning base element for too small object box deletion. """
    def __init__(self, screen_height, screen_width,
                 min_box_height, min_box_width):
        self.screen_height = screen_height
        self.screen_width = screen_width
        self.min_box_height = min_box_height
        self.min_box_width = min_box_width

    def is_percentage_sufficiant(self, percentage_height, percentage_width):
        """ Return True if detection box dimension is large enough,
            False otherwise.
        """
        res = self.screen_width * percentage_width > self.min_box_width
        res &= self.screen_height * percentage_height > self.min_box_height
        return res


class NmsParam:
    """ Contains parametter for non maximal suppression algorithm. """
    def __init__(self, top_k=20, iou_threshold=0.4):
        self.top_k = top_k
        self.iou_threshold = iou_threshold


class DetectionParam:
    """ Contains the number of classes and their detection threshold. """

    def __init__(self, class_nb, threshold):
        self.class_nb = class_nb
        self.classes_threshold = [threshold] * class_nb

    def get_class_threshold(self, index):
        """ Get detection value of a class """
        return self.classes_threshold[index]


def clip(elm, mini, maxi):
    """ Clips a value between mini and maxi."""
    return max(min(elm, maxi), mini)


def layer_finder(output_layer_info, name):
    """ Return the layer contained in output_layer_info which corresponds
        to the given name.
    """
    for layer in output_layer_info:
        # dataType == 0 <=> dataType == FLOAT
        if layer.dataType == 0 and layer.layerName == name:
            return layer
    return None


def make_nodi(index, layers, detection_param, box_size_param):
    """ Creates a NvDsInferObjectDetectionInfo object from one layer of SSD.
        Return None if the class Id is invalid, if the detection confidence
        is under the threshold or if the width/height of the bounding box is
        null/negative.
        Return the created NvDsInferObjectDetectionInfo object otherwise.
    """
    score_layer, class_layer, box_layer = layers
    res = pyds.NvDsInferObjectDetectionInfo()
    res.detectionConfidence = pyds.get_detections(score_layer.buffer, index)
    res.classId = int(pyds.get_detections(class_layer.buffer, index))
    if (
            res.classId >= detection_param.class_nb
            or res.detectionConfidence < detection_param.get_class_threshold(res.classId)
    ):
        return None

    def clip_1d_elm(index2):
        """ Clips an element from buff_view between bounds. """
        buff_elm = pyds.get_detections(box_layer.buffer, index * 4 + index2)
        return clip(buff_elm, 0.0, 1.0)

    rect_x1_f = clip_1d_elm(0)
    rect_y1_f = clip_1d_elm(1)
    rect_x2_f = clip_1d_elm(2)
    rect_y2_f = clip_1d_elm(3)
    res.left = rect_y1_f
    res.top = rect_x1_f
    res.width = rect_y2_f - rect_y1_f
    res.height = rect_x2_f - rect_x1_f

    if not box_size_param.is_percentage_sufficiant(res.height, res.width):
        return None

    return res


def nvds_infer_parse_custom_tf_ssd(output_layer_info, detection_param, box_size_param,
                                   nms_param=NmsParam()):
    """ Get data from output_layer_info and fill object_list
        with several NvDsInferObjectDetectionInfo.

        Keyword arguments:
        - output_layer_info : represents the neural network's output.
            (NvDsInferLayerInfo list)
        - detection_param : contains per class threshold.
            (DetectionParam)
        - box_size_param : element containing information to discard boxes
            that are too small. (BoxSizeParam)
        - nms_param : contains information for performing non maximal
            suppression. (NmsParam)

        Return:
        - Bounding boxes. (NvDsInferObjectDetectionInfo list)
    """
    num_detection_layer = layer_finder(output_layer_info, "num_detections")
    score_layer = layer_finder(output_layer_info, "detection_scores")
    class_layer = layer_finder(output_layer_info, "detection_classes")
    box_layer = layer_finder(output_layer_info, "detection_boxes")

    if not num_detection_layer or not score_layer or not class_layer or not box_layer:
        sys.stderr.write("ERROR: some layers missing in output tensors\n")
        return []

    num_detection = 0

    if num_detection_layer.buffer:
        num_detection = int(pyds.get_detections(num_detection_layer.buffer, 0))
        num_detection = clip(num_detection, 0, class_layer.inferDims.d[0])

    x3_layers = score_layer, class_layer, box_layer
    object_list = []
    for i in range(num_detection):
        obj = make_nodi(i, x3_layers, detection_param, box_size_param)
        if obj:
            object_list.append(obj)

    if object_list:
        object_list = cluster_and_fill_detection_output_nms(object_list, nms_param.top_k,
                                                            nms_param.iou_threshold)
    return object_list
