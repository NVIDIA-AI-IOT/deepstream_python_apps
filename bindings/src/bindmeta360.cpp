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

// NvDs360DMeta

#include "bindmeta360.hpp"

namespace py = pybind11;

namespace pydeepstream {

    void bindmeta360(py::module &m) {
        /*Start of Bindings for nvds_360d_meta.h*/
        py::enum_<ROI_STATUS_360D>(m, "ROI_STATUS_360D",
                                   pydsdoc::meta360doc::ROI_STATUS_360Ddoc::descr)
                .value("ROI_ENTRY_360D", ROI_ENTRY_360D,
                       pydsdoc::meta360doc::ROI_STATUS_360Ddoc::ROI_ENTRY_360Ddoc)
                .value("ROI_EXIT_360D", ROI_EXIT_360D,
                       pydsdoc::meta360doc::ROI_STATUS_360Ddoc::ROI_EXIT_360Ddoc)
                .value("INSIDE_AISLE_360D", INSIDE_AISLE_360D,
                       pydsdoc::meta360doc::ROI_STATUS_360Ddoc::INSIDE_AISLE_360Ddoc)
                .export_values();


        py::class_<RectDim>(m, "RectDim",
                            pydsdoc::meta360doc::RectDimdoc::descr)
                .def(py::init<>())
                .def_readwrite("left", &RectDim::left)
                .def_readwrite("top", &RectDim::top)
                .def_readwrite("width", &RectDim::width)
                .def_readwrite("height", &RectDim::height)
                .def_readwrite("class_id", &RectDim::class_id)
                .def_readwrite("tracking_id", &RectDim::tracking_id)
                .def_readwrite("gie_unique_id", &RectDim::gie_unique_id)
                .def_readwrite("roi_status", &RectDim::roi_status)
                .def_readwrite("text", &RectDim::text)

                .def("cast",
                     [](void *data) {
                         return (RectDim *) data;
                     },
                     py::return_value_policy::reference,
                     pydsdoc::meta360doc::RectDimdoc::cast)

                .def("cast",
                     [](size_t data) {
                         return (RectDim *) data;
                     },
                     py::return_value_policy::reference,
                     pydsdoc::meta360doc::RectDimdoc::cast);
    }
}