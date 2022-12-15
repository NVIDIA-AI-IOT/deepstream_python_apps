/*
 * SPDX-FileCopyrightText: Copyright (c) 2021-2022 NVIDIA CORPORATION & AFFILIATES. All rights reserved.
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

// NvDsMeta

#include "bind_string_property_definitions.h"
#include "bindnvdsmeta.hpp"

namespace py = pybind11;

namespace pydeepstream {

    void bindnvdsmeta(py::module &m) {
        /*Start of Bindings for nvdsmeta.h*/
        py::enum_<NvDsMetaType>(m, "NvDsMetaType",
                                pydsdoc::nvmeta::MetaTypeDoc::descr)
                .value("NVDS_INVALID_META", NVDS_INVALID_META,
                       pydsdoc::nvmeta::MetaTypeDoc::NVDS_INVALID_META)
                .value("NVDS_BATCH_META", NVDS_BATCH_META,
                       pydsdoc::nvmeta::MetaTypeDoc::NVDS_BATCH_META)
                .value("NVDS_FRAME_META", NVDS_FRAME_META,
                       pydsdoc::nvmeta::MetaTypeDoc::NVDS_FRAME_META)
                .value("NVDS_OBJ_META", NVDS_OBJ_META,
                       pydsdoc::nvmeta::MetaTypeDoc::NVDS_OBJ_META)
                .value("NVDS_DISPLAY_META", NVDS_DISPLAY_META,
                       pydsdoc::nvmeta::MetaTypeDoc::NVDS_DISPLAY_META)
                .value("NVDS_CLASSIFIER_META", NVDS_CLASSIFIER_META,
                       pydsdoc::nvmeta::MetaTypeDoc::NVDS_CLASSIFIER_META)
                .value("NVDS_LABEL_INFO_META", NVDS_LABEL_INFO_META,
                       pydsdoc::nvmeta::MetaTypeDoc::NVDS_LABEL_INFO_META)
                .value("NVDS_USER_META", NVDS_USER_META,
                       pydsdoc::nvmeta::MetaTypeDoc::NVDS_USER_META)
                .value("NVDS_PAYLOAD_META", NVDS_PAYLOAD_META,
                       pydsdoc::nvmeta::MetaTypeDoc::NVDS_PAYLOAD_META)
                .value("NVDS_EVENT_MSG_META", NVDS_EVENT_MSG_META,
                       pydsdoc::nvmeta::MetaTypeDoc::NVDS_EVENT_MSG_META)
                .value("NVDS_OPTICAL_FLOW_META", NVDS_OPTICAL_FLOW_META,
                       pydsdoc::nvmeta::MetaTypeDoc::NVDS_OPTICAL_FLOW_META)
                .value("NVDS_LATENCY_MEASUREMENT_META",
                       NVDS_LATENCY_MEASUREMENT_META,
                       pydsdoc::nvmeta::MetaTypeDoc::NVDS_LATENCY_MEASUREMENT_META)
                .value("NVDSINFER_TENSOR_OUTPUT_META",
                       NVDSINFER_TENSOR_OUTPUT_META,
                       pydsdoc::nvmeta::MetaTypeDoc::NVDSINFER_TENSOR_OUTPUT_META)
                .value("NVDSINFER_SEGMENTATION_META",
                       NVDSINFER_SEGMENTATION_META,
                       pydsdoc::nvmeta::MetaTypeDoc::NVDSINFER_SEGMENTATION_META)
                        /*adding new field*/
                .value("NVDS_CROP_IMAGE_META", NVDS_CROP_IMAGE_META,
                       pydsdoc::nvmeta::MetaTypeDoc::NVDS_CROP_IMAGE_META)
                .value("NVDS_TRACKER_PAST_FRAME_META",
                       NVDS_TRACKER_PAST_FRAME_META,
                       pydsdoc::nvmeta::MetaTypeDoc::NVDS_TRACKER_PAST_FRAME_META)
                .value("NVDS_AUDIO_BATCH_META", NVDS_AUDIO_BATCH_META,
                       pydsdoc::nvmeta::MetaTypeDoc::NVDS_AUDIO_BATCH_META)
                .value("NVDS_AUDIO_FRAME_META", NVDS_AUDIO_FRAME_META,
                       pydsdoc::nvmeta::MetaTypeDoc::NVDS_AUDIO_FRAME_META)
                .value("NVDS_RESERVED_META", NVDS_RESERVED_META,
                       pydsdoc::nvmeta::MetaTypeDoc::NVDS_RESERVED_META)
                .value("NVDS_GST_CUSTOM_META", NVDS_GST_CUSTOM_META,
                       pydsdoc::nvmeta::MetaTypeDoc::NVDS_GST_CUSTOM_META)
                .value("NVDS_START_USER_META", NVDS_START_USER_META,
                       pydsdoc::nvmeta::MetaTypeDoc::NVDS_START_USER_META)
                .value("NVDS_FORCE32_META", NVDS_FORCE32_META,
                       pydsdoc::nvmeta::MetaTypeDoc::NVDS_FORCE32_META)
                .export_values();


        py::class_<NvDsComp_BboxInfo>(m, "NvDsComp_BboxInfo",
                                      pydsdoc::nvmeta::NvDsComp_BboxInfoDoc::descr)
                .def(py::init<>())
                .def_readwrite("org_bbox_coords",
                               &NvDsComp_BboxInfo::org_bbox_coords)

                .def("cast",
                     [](void *data) {
                         return (NvDsComp_BboxInfo *) data;
                     },
                     py::return_value_policy::reference,
                     pydsdoc::nvmeta::NvDsComp_BboxInfoDoc::cast)

                .def("cast",
                     [](size_t data) {
                         return (NvDsComp_BboxInfo *) data;
                     },
                     py::return_value_policy::reference,
                     pydsdoc::nvmeta::NvDsComp_BboxInfoDoc::cast);


        py::class_<NvDsMetaPool>(m, "NvDsMetaPool",
                                 pydsdoc::nvmeta::MetaPoolDoc::descr)
                .def(py::init<>())
                .def_readwrite("meta_type", &NvDsMetaPool::meta_type)
                .def_readwrite("max_elements_in_pool",
                               &NvDsMetaPool::max_elements_in_pool)
                .def_readwrite("element_size", &NvDsMetaPool::element_size)
                .def_readwrite("num_empty_elements",
                               &NvDsMetaPool::num_empty_elements)
                .def_readwrite("num_full_elements",
                               &NvDsMetaPool::num_full_elements)
                .def_readwrite("empty_list", &NvDsMetaPool::empty_list)
                .def_readwrite("full_list", &NvDsMetaPool::full_list)

                .def("cast",
                     [](void *data) {
                         return (NvDsMetaPool *) data;
                     },
                     py::return_value_policy::reference,
                     pydsdoc::nvmeta::MetaPoolDoc::cast)

                .def("cast",
                     [](size_t data) {
                         return (NvDsMetaPool *) data;
                     },
                     py::return_value_policy::reference,
                     pydsdoc::nvmeta::MetaPoolDoc::cast);


        py::class_<NvDsBaseMeta>(m, "NvDsBaseMeta",
                                 pydsdoc::nvmeta::BaseMetaDoc::descr)
                .def(py::init<>())
                .def_readwrite("batch_meta", &NvDsBaseMeta::batch_meta)
                .def_readwrite("meta_type", &NvDsBaseMeta::meta_type)
                .def_readwrite("uContext", &NvDsBaseMeta::uContext)

                .def("cast",
                     [](void *data) {
                         return (NvDsBaseMeta *) data;
                     },
                     py::return_value_policy::reference,
                     pydsdoc::nvmeta::BaseMetaDoc::cast)

                .def("cast",
                     [](size_t data) {
                         return (NvDsBaseMeta *) data;
                     },
                     py::return_value_policy::reference,
                     pydsdoc::nvmeta::BaseMetaDoc::cast);


        py::class_<NvDsBatchMeta>(m, "NvDsBatchMeta",
                                  pydsdoc::nvmeta::BatchMetaDoc::descr)
                .def(py::init<>())
                .def_readwrite("base_meta", &NvDsBatchMeta::base_meta)
                .def_readwrite("max_frames_in_batch",
                               &NvDsBatchMeta::max_frames_in_batch)
                .def_readwrite("num_frames_in_batch",
                               &NvDsBatchMeta::num_frames_in_batch)
                .def_readwrite("frame_meta_pool",
                               &NvDsBatchMeta::frame_meta_pool)
                .def_readwrite("obj_meta_pool", &NvDsBatchMeta::obj_meta_pool)
                .def_readwrite("classifier_meta_pool",
                               &NvDsBatchMeta::classifier_meta_pool)
                .def_readwrite("display_meta_pool",
                               &NvDsBatchMeta::display_meta_pool)
                .def_readwrite("user_meta_pool", &NvDsBatchMeta::user_meta_pool)
                .def_readwrite("label_info_meta_pool",
                               &NvDsBatchMeta::label_info_meta_pool)
                .def_readwrite("frame_meta_list",
                               &NvDsBatchMeta::frame_meta_list)
                .def_readwrite("batch_user_meta_list",
                               &NvDsBatchMeta::batch_user_meta_list)
                .def_readwrite("meta_mutex", &NvDsBatchMeta::meta_mutex)

                .def("cast",
                     [](void *data) {
                         return (NvDsBatchMeta *) data;
                     },
                     py::return_value_policy::reference,
                     pydsdoc::nvmeta::BatchMetaDoc::cast)

                .def("cast",
                     [](size_t data) {
                         return (NvDsBatchMeta *) data;
                     },
                     py::return_value_policy::reference,
                     pydsdoc::nvmeta::BatchMetaDoc::cast)

                .def_property("misc_batch_info",
                              [](NvDsBatchMeta &self) -> py::array {
                                  auto dtype = py::dtype(
                                          py::format_descriptor<int>::format());
                                  auto base = py::array(dtype,
                                                        {MAX_USER_FIELDS},
                                                        {sizeof(int)});
                                  return py::array(dtype, {MAX_USER_FIELDS},
                                                   {sizeof(int)},
                                                   self.misc_batch_info, base);
                              },
                              [](NvDsBatchMeta &self) {})

                .def_property("reserved",
                              [](NvDsBatchMeta &self) -> py::array {
                                  auto dtype = py::dtype(
                                          py::format_descriptor<int>::format());
                                  auto base = py::array(dtype,
                                                        {MAX_RESERVED_FIELDS},
                                                        {sizeof(int)});
                                  return py::array(dtype, {MAX_RESERVED_FIELDS},
                                                   {sizeof(int)}, self.reserved,
                                                   base);
                              },
                              [](NvDsBatchMeta &self) {});


        py::class_<NvDsFrameMeta>(m, "NvDsFrameMeta",
                                  pydsdoc::nvmeta::FrameMetaDoc::descr)
                .def(py::init<>())
                .def_readwrite("base_meta", &NvDsFrameMeta::base_meta)
                .def_readwrite("pad_index", &NvDsFrameMeta::pad_index)
                .def_readwrite("batch_id", &NvDsFrameMeta::batch_id)
                .def_readwrite("frame_num", &NvDsFrameMeta::frame_num)
                .def_readwrite("buf_pts", &NvDsFrameMeta::buf_pts)
                .def_readwrite("ntp_timestamp", &NvDsFrameMeta::ntp_timestamp)
                .def_readwrite("source_id", &NvDsFrameMeta::source_id)
                .def_readwrite("num_surfaces_per_frame",
                               &NvDsFrameMeta::num_surfaces_per_frame)
                .def_readwrite("source_frame_width",
                               &NvDsFrameMeta::source_frame_width)
                .def_readwrite("source_frame_height",
                               &NvDsFrameMeta::source_frame_height)
                .def_readwrite("surface_type", &NvDsFrameMeta::surface_type)
                .def_readwrite("surface_index", &NvDsFrameMeta::surface_index)
                .def_readwrite("num_obj_meta", &NvDsFrameMeta::num_obj_meta)
                .def_readwrite("bInferDone", &NvDsFrameMeta::bInferDone)
                .def_readwrite("obj_meta_list", &NvDsFrameMeta::obj_meta_list)
                .def_readwrite("display_meta_list",
                               &NvDsFrameMeta::display_meta_list)
                .def_readwrite("frame_user_meta_list",
                               &NvDsFrameMeta::frame_user_meta_list)

                .def("cast",
                     [](void *data) {
                         return (NvDsFrameMeta *) data;
                     },
                     py::return_value_policy::reference,
                     pydsdoc::nvmeta::FrameMetaDoc::cast)

                .def("cast",
                     [](size_t data) {
                         return (NvDsFrameMeta *) data;
                     },
                     py::return_value_policy::reference,
                     pydsdoc::nvmeta::FrameMetaDoc::cast)

                .def_property("misc_frame_info",
                              [](NvDsFrameMeta &self) -> py::array {
                                  auto dtype = py::dtype(
                                          py::format_descriptor<int>::format());
                                  auto base = py::array(dtype,
                                                        {MAX_USER_FIELDS},
                                                        {sizeof(int)});
                                  return py::array(dtype, {MAX_USER_FIELDS},
                                                   {sizeof(int)},
                                                   self.misc_frame_info, base);
                              },
                              [](NvDsFrameMeta &self) {})

                .def_property("reserved",
                              [](NvDsFrameMeta &self) -> py::array {
                                  auto dtype = py::dtype(
                                          py::format_descriptor<int>::format());
                                  auto base = py::array(dtype,
                                                        {MAX_RESERVED_FIELDS},
                                                        {sizeof(int)});
                                  return py::array(dtype, {MAX_RESERVED_FIELDS},
                                                   {sizeof(int)}, self.reserved,
                                                   base);
                              },
                              [](NvDsBatchMeta &self) {});


        py::class_<NvDsObjectMeta>(m, "NvDsObjectMeta",
                                   pydsdoc::nvmeta::ObjectMetaDoc::descr)
                .def(py::init<>())
                .def_readwrite("base_meta", &NvDsObjectMeta::base_meta)
                .def_readwrite("parent", &NvDsObjectMeta::parent)
                .def_readwrite("unique_component_id",
                               &NvDsObjectMeta::unique_component_id)
                .def_readwrite("class_id", &NvDsObjectMeta::class_id)
                .def_readwrite("object_id", &NvDsObjectMeta::object_id)
                .def_readwrite("detector_bbox_info",
                               &NvDsObjectMeta::detector_bbox_info)
                .def_readwrite("tracker_bbox_info",
                               &NvDsObjectMeta::tracker_bbox_info)
                .def_readwrite("confidence", &NvDsObjectMeta::confidence)
                .def_readwrite("tracker_confidence",
                               &NvDsObjectMeta::tracker_confidence)
                .def_readwrite("rect_params", &NvDsObjectMeta::rect_params)
                .def_readwrite("mask_params", &NvDsObjectMeta::mask_params)
                .def_readwrite("text_params", &NvDsObjectMeta::text_params)

                .def("cast",
                     [](void *data) {
                         return (NvDsObjectMeta *) data;
                     },
                     py::return_value_policy::reference,
                     pydsdoc::nvmeta::ObjectMetaDoc::cast)

                .def("cast",
                     [](size_t data) {
                         return (NvDsObjectMeta *) data;
                     },
                     py::return_value_policy::reference,
                     pydsdoc::nvmeta::ObjectMetaDoc::cast)

                .def_property("obj_label",
                              STRING_CHAR_ARRAY(NvDsObjectMeta, obj_label))
                .def_readwrite("classifier_meta_list",
                               &NvDsObjectMeta::classifier_meta_list)
                .def_readwrite("obj_user_meta_list",
                               &NvDsObjectMeta::obj_user_meta_list)

                .def_property("misc_obj_info",
                              [](NvDsObjectMeta &self) -> py::array {
                                  auto dtype = py::dtype(
                                          py::format_descriptor<int>::format());
                                  auto base = py::array(dtype,
                                                        {MAX_USER_FIELDS},
                                                        {sizeof(int)});
                                  return py::array(dtype, {MAX_USER_FIELDS},
                                                   {sizeof(int)},
                                                   self.misc_obj_info, base);
                              },
                              [](NvDsObjectMeta &self) {})

                .def_property("reserved",
                              [](NvDsObjectMeta &self) -> py::array {
                                  auto dtype = py::dtype(
                                          py::format_descriptor<int>::format());
                                  auto base = py::array(dtype,
                                                        {MAX_RESERVED_FIELDS},
                                                        {sizeof(int)});
                                  return py::array(dtype, {MAX_RESERVED_FIELDS},
                                                   {sizeof(int)}, self.reserved,
                                                   base);
                              },
                              [](NvDsObjectMeta &self) {});


        py::class_<NvDsClassifierMeta>(m, "NvDsClassifierMeta",
                                       pydsdoc::nvmeta::ClassifierMetaDoc::descr)
                .def(py::init<>())
                .def_readwrite("base_meta", &NvDsClassifierMeta::base_meta)
                .def_readwrite("num_labels", &NvDsClassifierMeta::num_labels)
                .def_readwrite("unique_component_id",
                               &NvDsClassifierMeta::unique_component_id)

                .def("cast",
                     [](void *data) {
                         return (NvDsClassifierMeta *) data;
                     },
                     py::return_value_policy::reference,
                     pydsdoc::nvmeta::ClassifierMetaDoc::cast)

                .def("cast",
                     [](size_t data) {
                         return (NvDsClassifierMeta *) data;
                     },
                     py::return_value_policy::reference,
                     pydsdoc::nvmeta::ClassifierMetaDoc::cast)

                .def_readwrite("label_info_list",
                               &NvDsClassifierMeta::label_info_list);


        py::class_<NvDsLabelInfo>(m, "NvDsLabelInfo",
                                  pydsdoc::nvmeta::LabelInfoDoc::descr)
                .def(py::init<>())
                .def_readwrite("base_meta", &NvDsLabelInfo::base_meta)
                .def_readwrite("num_classes", &NvDsLabelInfo::num_classes)
                .def_property("result_label",
                              STRING_CHAR_ARRAY(NvDsLabelInfo, result_label))

                .def("cast",
                     [](void *data) {
                         return (NvDsLabelInfo *) data;
                     },
                     py::return_value_policy::reference,
                     pydsdoc::nvmeta::LabelInfoDoc::cast)

                .def("cast",
                     [](size_t data) {
                         return (NvDsLabelInfo *) data;
                     },
                     py::return_value_policy::reference,
                     pydsdoc::nvmeta::LabelInfoDoc::cast)

                .def_readwrite("pResult_label", &NvDsLabelInfo::pResult_label)
                .def_readwrite("result_class_id",
                               &NvDsLabelInfo::result_class_id)
                .def_readwrite("label_id", &NvDsLabelInfo::label_id)
                .def_readwrite("result_prob", &NvDsLabelInfo::result_prob);


        py::class_<NvDsDisplayMeta>(m, "NvDsDisplayMeta",
                                    pydsdoc::nvmeta::DisplayMetaDoc::descr)
                .def(py::init<>())
                .def_readwrite("base_meta", &NvDsDisplayMeta::base_meta)
                .def_readwrite("num_rects", &NvDsDisplayMeta::num_rects)
                .def_readwrite("num_labels", &NvDsDisplayMeta::num_labels)
                .def_readwrite("num_lines", &NvDsDisplayMeta::num_lines)
                .def_readwrite("num_arrows", &NvDsDisplayMeta::num_arrows)
                .def_readwrite("num_circles", &NvDsDisplayMeta::num_circles)

                .def_property_readonly("rect_params",
                                       [](const NvDsDisplayMeta &self) {
                                           std::vector<const NvOSD_RectParams *> vRectParams;
                                           for (const auto &rect_param : self.rect_params) {
                                               vRectParams.push_back(
                                                       &rect_param);
                                           }
                                           return vRectParams;
                                       },
                                       py::return_value_policy::reference)

                .def_property_readonly("text_params",
                                       [](const NvDsDisplayMeta &self) {
                                           std::vector<const NvOSD_TextParams *> vTextParams;
                                           for (const auto &text_param : self.text_params) {
                                               vTextParams.push_back(
                                                       &text_param);
                                           }
                                           return vTextParams;
                                       },
                                       py::return_value_policy::reference)

                .def_property_readonly("line_params",
                                       [](const NvDsDisplayMeta &self) {
                                           std::vector<const NvOSD_LineParams *> vlineParams;
                                           for (const auto &line_param : self.line_params) {
                                               vlineParams.push_back(
                                                       &line_param);
                                           }
                                           return vlineParams;
                                       },
                                       py::return_value_policy::reference)

                .def_property_readonly("arrow_params",
                                       [](const NvDsDisplayMeta &self) {
                                           std::vector<const NvOSD_ArrowParams *> varrowParams;
                                           for (const auto &arrow_param : self.arrow_params) {
                                               varrowParams.push_back(
                                                       &arrow_param);
                                           }
                                           return varrowParams;
                                       },
                                       py::return_value_policy::reference)

                .def_property_readonly("circle_params",
                                       [](const NvDsDisplayMeta &self) {
                                           std::vector<const NvOSD_CircleParams *> vcircleParams;
                                           for (const auto &circle_param : self.circle_params) {
                                               vcircleParams.push_back(
                                                       &circle_param);
                                           }
                                           return vcircleParams;
                                       },
                                       py::return_value_policy::reference)

                .def("cast",
                     [](void *data) {
                         return (NvDsDisplayMeta *) data;
                     },
                     py::return_value_policy::reference,
                     pydsdoc::nvmeta::DisplayMetaDoc::cast)

                .def("cast",
                     [](size_t data) {
                         return (NvDsDisplayMeta *) data;
                     },
                     py::return_value_policy::reference,
                     pydsdoc::nvmeta::DisplayMetaDoc::cast)

                .def_property("misc_osd_data",
                              [](NvDsDisplayMeta &self) -> py::array {
                                  auto dtype = py::dtype(
                                          py::format_descriptor<int>::format());
                                  auto base = py::array(dtype,
                                                        {MAX_USER_FIELDS},
                                                        {sizeof(int)});
                                  return py::array(dtype, {MAX_USER_FIELDS},
                                                   {sizeof(int)},
                                                   self.misc_osd_data, base);
                              },
                              [](NvDsDisplayMeta &self) {})

                .def_property("reserved",
                              [](NvDsDisplayMeta &self) -> py::array {
                                  auto dtype = py::dtype(
                                          py::format_descriptor<int>::format());
                                  auto base = py::array(dtype,
                                                        {MAX_RESERVED_FIELDS},
                                                        {sizeof(int)});
                                  return py::array(dtype, {MAX_RESERVED_FIELDS},
                                                   {sizeof(int)}, self.reserved,
                                                   base);
                              },
                              [](NvDsDisplayMeta &self) {});


        py::class_<NvDsUserMeta>(m, "NvDsUserMeta",
                                 pydsdoc::nvmeta::UserMetaDoc::descr)
                .def(py::init<>())
                .def_readwrite("base_meta", &NvDsUserMeta::base_meta)
                .def_readwrite("user_meta_data", &NvDsUserMeta::user_meta_data)

                .def("cast",
                     [](void *data) {
                         return (NvDsUserMeta *) data;
                     },
                     py::return_value_policy::reference,
                     pydsdoc::nvmeta::UserMetaDoc::cast)

                .def("cast",
                     [](size_t data) {
                         return (NvDsUserMeta *) data;
                     },
                     py::return_value_policy::reference,
                     pydsdoc::nvmeta::UserMetaDoc::cast);
    }
}