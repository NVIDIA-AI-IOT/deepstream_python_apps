/*
 * SPDX-FileCopyrightText: Copyright (c) 2021 NVIDIA CORPORATION & AFFILIATES. All rights reserved.
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

// NvDsInfer

#include "bindnvdsinfer.hpp"

namespace py = pybind11;

namespace pydeepstream {

    void bindnvdsinfer(py::module &m) {
        /*Start of Bindings for /deepstream/sdk/src/utils/nvdsinfer/include/nvdsinfer.h*/
        py::class_<NvDsInferDims>(m, "NvDsInferDims",
                                  pydsdoc::NvInferDoc::NvdsInferDimsDoc::descr)
                .def(py::init<>())
                .def_readonly("numDims", &NvDsInferDims::numDims)
                .def_readonly("numElements", &NvDsInferDims::numElements)

                .def_property("d",
                              [](NvDsInferDims &self) -> py::array {
                                  auto dtype = py::dtype(
                                          py::format_descriptor<unsigned int>::format());
                                  auto base = py::array(dtype,
                                                        {NVDSINFER_MAX_DIMS},
                                                        {sizeof(unsigned int)});
                                  return py::array(dtype, {NVDSINFER_MAX_DIMS},
                                                   {sizeof(unsigned int)},
                                                   self.d, base);
                              },
                              [](NvDsInferDims &self) {})

                .def("cast",
                     [](void *data) {
                         return (NvDsInferDims *) data;
                     },
                     py::return_value_policy::reference,
                     pydsdoc::NvInferDoc::NvdsInferDimsDoc::cast)

                .def("cast",
                     [](size_t data) {
                         return (NvDsInferDims *) data;
                     },
                     py::return_value_policy::reference,
                     pydsdoc::NvInferDoc::NvdsInferDimsDoc::cast);


        py::class_<NvDsInferDimsCHW>(m, "NvDsInferDimsCHW",
                                     pydsdoc::NvInferDoc::NvDsInferDimsCHWDoc::descr)
                .def(py::init<>())
                .def_readonly("c", &NvDsInferDimsCHW::c)
                .def_readonly("h", &NvDsInferDimsCHW::h)
                .def_readonly("w", &NvDsInferDimsCHW::w)

                .def("cast",
                     [](void *data) {
                         return (NvDsInferDimsCHW *) data;
                     },
                     py::return_value_policy::reference,
                     pydsdoc::NvInferDoc::NvDsInferDimsCHWDoc::cast)

                .def("cast",
                     [](size_t data) {
                         return (NvDsInferDimsCHW *) data;
                     },
                     py::return_value_policy::reference,
                     pydsdoc::NvInferDoc::NvDsInferDimsCHWDoc::cast);


        py::enum_<NvDsInferDataType>(m, "NvDsInferDataType",
                                     pydsdoc::NvInferDoc::NvDsInferDataTypeDoc::descr)
                .value("FLOAT", FLOAT,
                       pydsdoc::NvInferDoc::NvDsInferDataTypeDoc::FLOAT)
                .value("HALF", HALF,
                       pydsdoc::NvInferDoc::NvDsInferDataTypeDoc::HALF)
                .value("INT8", INT8,
                       pydsdoc::NvInferDoc::NvDsInferDataTypeDoc::INT8)
                .value("INT32", INT32,
                       pydsdoc::NvInferDoc::NvDsInferDataTypeDoc::INT32)
                .export_values();


        py::class_<NvDsInferLayerInfo>(m, "NvDsInferLayerInfo",
                                       pydsdoc::NvInferDoc::NvDsInferLayerInfoDoc::descr)
                .def(py::init<>())
                .def_readonly("dataType", &NvDsInferLayerInfo::dataType)
                .def_readonly("dims", &NvDsInferLayerInfo::inferDims)
                .def_readonly("inferDims", &NvDsInferLayerInfo::inferDims)
                .def_readonly("bindingIndex", &NvDsInferLayerInfo::bindingIndex)
                .def_readonly("layerName", &NvDsInferLayerInfo::layerName)
                .def_readonly("buffer", &NvDsInferLayerInfo::buffer)
                .def_readonly("isInput", &NvDsInferLayerInfo::isInput)

                .def("cast",
                     [](void *data) {
                         return (NvDsInferLayerInfo *) data;
                     },
                     py::return_value_policy::reference,
                     pydsdoc::NvInferDoc::NvDsInferLayerInfoDoc::cast)

                .def("cast",
                     [](size_t data) {
                         return (NvDsInferLayerInfo *) data;
                     },
                     py::return_value_policy::reference,
                     pydsdoc::NvInferDoc::NvDsInferLayerInfoDoc::cast);


        py::class_<NvDsInferNetworkInfo>(m, "NvDsInferNetworkInfo",
                                         pydsdoc::NvInferDoc::NvDsInferNetworkInfoDoc::descr)
                .def(py::init<>())
                .def_readwrite("width", &NvDsInferNetworkInfo::width)
                .def_readwrite("height", &NvDsInferNetworkInfo::height)
                .def_readwrite("channels", &NvDsInferNetworkInfo::channels)

                .def("cast",
                     [](void *data) {
                         return (NvDsInferNetworkInfo *) data;
                     },
                     py::return_value_policy::reference,
                     pydsdoc::NvInferDoc::NvDsInferNetworkInfoDoc::cast)

                .def("cast",
                     [](size_t data) {
                         return (NvDsInferNetworkInfo *) data;
                     },
                     py::return_value_policy::reference,
                     pydsdoc::NvInferDoc::NvDsInferNetworkInfoDoc::cast);


        py::class_<NvDsInferObjectDetectionInfo>(m, "NvDsInferObjectDetectionInfo",
                                                 pydsdoc::NvInferDoc::NvDsInferObjectDetectionInfoDoc::descr)
                .def(py::init<>())
                .def_readwrite("classId",
                               &NvDsInferObjectDetectionInfo::classId)
                .def_readwrite("left", &NvDsInferObjectDetectionInfo::left)
                .def_readwrite("top", &NvDsInferObjectDetectionInfo::top)
                .def_readwrite("width", &NvDsInferObjectDetectionInfo::width)
                .def_readwrite("height", &NvDsInferObjectDetectionInfo::height)
                .def_readwrite("detectionConfidence",
                               &NvDsInferObjectDetectionInfo::detectionConfidence)

                .def("cast",
                     [](void *data) {
                         return (NvDsInferObjectDetectionInfo *) data;
                     },
                     py::return_value_policy::reference,
                     pydsdoc::NvInferDoc::NvDsInferObjectDetectionInfoDoc::cast)

                .def("cast",
                     [](size_t data) {
                         return (NvDsInferObjectDetectionInfo *) data;
                     },
                     py::return_value_policy::reference,
                     pydsdoc::NvInferDoc::NvDsInferObjectDetectionInfoDoc::cast);


        py::class_<NvDsInferAttribute>(m, "NvDsInferAttribute",
                                       pydsdoc::NvInferDoc::NvDsInferAttributeDoc::descr)
                .def(py::init<>())
                .def_readonly("attributeIndex",
                              &NvDsInferAttribute::attributeIndex)
                .def_readonly("atttributeIndex",
                              &NvDsInferAttribute::attributeIndex)
                .def_readonly("attributeValue",
                              &NvDsInferAttribute::attributeValue)
                .def_readonly("attributeConfidence",
                              &NvDsInferAttribute::attributeConfidence)
                .def_readonly("attributeLabel",
                              &NvDsInferAttribute::attributeLabel)

                .def("cast",
                     [](void *data) {
                         return (NvDsInferAttribute *) data;
                     },
                     py::return_value_policy::reference,
                     pydsdoc::NvInferDoc::NvDsInferObjectDetectionInfoDoc::cast)

                .def("cast",
                     [](size_t data) {
                         return (NvDsInferAttribute *) data;
                     },
                     py::return_value_policy::reference,
                     pydsdoc::NvInferDoc::NvDsInferObjectDetectionInfoDoc::cast);


        /*Start of Bindings for /deepstream/sdk/src/gst-utils/gst-nvdsinferbase/include/gstnvdsinfer.h*/
        py::class_<NvDsInferTensorMeta>(m, "NvDsInferTensorMeta",
                                        pydsdoc::NvInferDoc::NvDsInferTensorMetaDoc::descr)
                .def(py::init<>())
                .def_readonly("network_info", &NvDsInferTensorMeta::network_info)
                .def_readonly("unique_id", &NvDsInferTensorMeta::unique_id)
                .def_readonly("num_output_layers",
                              &NvDsInferTensorMeta::num_output_layers)

                .def("output_layers_info",
                     [](NvDsInferTensorMeta &self, int j) {
                         return self.output_layers_info[j];
                     },
                     "j"_a, py::return_value_policy::reference,
                     pydsdoc::NvInferDoc::NvDsInferTensorMetaDoc::output_layers_info)

                .def_readonly("out_buf_ptrs_host",
                              &NvDsInferTensorMeta::out_buf_ptrs_host)
                .def_readonly("out_buf_ptrs_dev",
                              &NvDsInferTensorMeta::out_buf_ptrs_dev)
                .def_readonly("gpu_id", &NvDsInferTensorMeta::gpu_id)
                .def_readonly("priv_data", &NvDsInferTensorMeta::priv_data)

                .def("cast",
                     [](void *data) {
                         return (NvDsInferTensorMeta *) data;
                     },
                     py::return_value_policy::reference,
                     pydsdoc::NvInferDoc::NvDsInferTensorMetaDoc::cast)

                .def("cast",
                     [](size_t data) {
                         return (NvDsInferTensorMeta *) data;
                     },
                     py::return_value_policy::reference,
                     pydsdoc::NvInferDoc::NvDsInferTensorMetaDoc::cast);


        py::class_<NvDsInferSegmentationMeta>(m, "NvDsInferSegmentationMeta",
                                              pydsdoc::NvInferDoc::NvDsInferSegmentationMetaDoc::descr)
                .def(py::init<>())
                .def_readonly("classes", &NvDsInferSegmentationMeta::classes)
                .def_readonly("width", &NvDsInferSegmentationMeta::width)
                .def_readonly("height", &NvDsInferSegmentationMeta::height)
                .def_readonly("class_map",
                              &NvDsInferSegmentationMeta::class_map)
                .def_readonly("class_probabilities_map",
                              &NvDsInferSegmentationMeta::class_probabilities_map)

                .def("cast",
                     [](void *data) {
                         return (NvDsInferSegmentationMeta *) data;
                     },
                     py::return_value_policy::reference,
                     pydsdoc::NvInferDoc::NvDsInferSegmentationMetaDoc::cast)

                .def_readonly("priv_data",
                              &NvDsInferSegmentationMeta::priv_data);

    }

}
