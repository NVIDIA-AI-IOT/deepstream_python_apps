################################################################################
# Copyright (c) 2020, NVIDIA CORPORATION. All rights reserved.
#
# Permission is hereby granted, free of charge, to any person obtaining a
# copy of this software and associated documentation files (the "Software"),
# to deal in the Software without restriction, including without limitation
# the rights to use, copy, modify, merge, publish, distribute, sublicense,
# and/or sell copies of the Software, and to permit persons to whom the
# Software is furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
# THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
# FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
# DEALINGS IN THE SOFTWARE.
################################################################################

"""
    Non Maximum Supression algorithm translated from
    src_utils_nvdsinferserver_infer_postprocess.cpp
    The function that should be imported is cluster_and_fill_detection_output_nms
"""

def overlap_1d(x1min, x1max, x2min, x2max):
    """ Return the overlap distance between 2 segments. """
    if x1min > x2min:
        x1min, x2min = x2min, x1min
        x1max, x2max = x2max, x1max
    return 0 if x1max < x2min else min(x1max, x2max) - x2min


def compute_iou(bbox1, bbox2):
    """ Compute the result of the intersection over union of 2 boxes. """
    overlap_x = overlap_1d(
        bbox1.left, bbox1.left + bbox1.width, bbox2.left, bbox2.left + bbox2.width
    )
    overlap_y = overlap_1d(
        bbox1.top, bbox1.top + bbox1.height, bbox2.top, bbox2.top + bbox2.height
    )
    area_1 = bbox1.width * bbox1.height
    area_2 = bbox2.width * bbox2.height
    intersection = overlap_x * overlap_y
    union = area_1 + area_2 - intersection
    return 0 if union == 0 else intersection / union


def non_maximum_suppression(score_index, bbox, nms_threshold):
    """ Test boxes overlapping. Returns indices of boxes that do not overlap more
    than nms_threshold.
    """
    indices = []
    for pair in score_index:
        idx = pair[1]
        keep = True
        for indice in indices:
            if keep:
                overlap = compute_iou(bbox[idx], bbox[indice])
                keep = overlap <= nms_threshold
            else:
                break
        if keep:
            indices.append(idx)
    return indices


def cluster_and_fill_detection_output_nms(object_list, topk=20, iou_threshold=0.4):
    """ Post-process object list in order to remove redundant boxes and limit
        the number of boxes.

        Keyword arguments:
        - object_list : list of NvDsInferObjectDetectionInfo objects
        - topk : maximum number of boxes kept (default 20)
        - iou_threshold : maximum overlap allowance between 2 boxes (default 0.4)

        Return:
        - Cleaned NvDsInferObjectDetectionInfo object list.
    """
    clustered_b_boxes = []
    per_class_object_list = {}
    for obj in object_list:
        cl_id = obj.classId
        if cl_id not in per_class_object_list:
            per_class_object_list[cl_id] = []
        per_class_object_list[cl_id].append(obj)

    for key in per_class_object_list:
        class_objs = per_class_object_list[key]
        score_index = [(elm.detectionConfidence, i) for i, elm in enumerate(class_objs)]
        score_index.sort(key=lambda x: x[0], reverse=True)

        indices = non_maximum_suppression(score_index, class_objs, iou_threshold)
        for idx in indices:
            clustered_b_boxes.append(class_objs[idx])

    if topk != 0 and len(clustered_b_boxes) > topk:
        clustered_b_boxes.sort(lambda x: x.detectionConfidence, reverse=True)
        clustered_b_boxes = clustered_b_boxes[:topk]

    return clustered_b_boxes
