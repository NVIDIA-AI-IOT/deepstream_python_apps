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

// NvDsOpticalFlow

#include "bind_string_property_definitions.h"
#include "bindopticalflow.hpp"

namespace py = pybind11;

namespace pydeepstream {

    void bindopticalflowmeta(py::module &m) {
        /*Start of Bindings for nvds_opticalflow_meta.h*/
        py::class_<NvOFFlowVector>(m, "NvOFFlowVector",
                                   pydsdoc::nvoptical::NvOFFlowVector::descr)
                .def_readwrite("flowx", &NvOFFlowVector::flowx)
                .def_readwrite("flowy", &NvOFFlowVector::flowy)

                .def("cast",
                     [](void *data) {
                         return (NvOFFlowVector *) data;
                     },
                     py::return_value_policy::reference,
                     pydsdoc::nvoptical::NvOFFlowVector::cast)

                .def("cast",
                     [](size_t data) {
                         return (NvOFFlowVector *) data;
                     },
                     py::return_value_policy::reference,
                     pydsdoc::nvoptical::NvOFFlowVector::cast);


        py::class_<NvDsOpticalFlowMeta>(m, "NvDsOpticalFlowMeta",
                                        pydsdoc::nvoptical::NvDsOpticalFlowMeta::descr)
                .def_readwrite("rows", &NvDsOpticalFlowMeta::rows)
                .def_readwrite("cols", &NvDsOpticalFlowMeta::cols)
                .def_readwrite("mv_size", &NvDsOpticalFlowMeta::mv_size)
                .def_readwrite("frame_num", &NvDsOpticalFlowMeta::frame_num)
                .def_readwrite("data", &NvDsOpticalFlowMeta::data)
                .def_readwrite("priv", &NvDsOpticalFlowMeta::priv)

                .def("cast",
                     [](void *data) {
                         return (NvDsOpticalFlowMeta *) data;
                     },
                     py::return_value_policy::reference,
                     pydsdoc::nvoptical::NvDsOpticalFlowMeta::cast)

                .def_readwrite("reserved", &NvDsOpticalFlowMeta::reserved);

    }

}