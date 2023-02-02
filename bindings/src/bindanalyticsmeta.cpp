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

// NvDsAnalyticsMeta

#include "bind_string_property_definitions.h"
#include "bindanalyticsmeta.hpp"

namespace py = pybind11;

namespace pydeepstream {

    void bindanalyticsmeta(py::module &m) {
        /*Start of Bindings for nvds_analytics_meta.h*/
        py::class_<NvDsAnalyticsObjInfo>(m, "NvDsAnalyticsObjInfo",
                pydsdoc::nvdsanalyticsdoc::NvDsAnalyticsObjInfoDoc::descr
        )
                .def(py::init<>())
                .def_readwrite("roiStatus", &NvDsAnalyticsObjInfo::roiStatus)
                .def_readwrite("ocStatus", &NvDsAnalyticsObjInfo::ocStatus)
                .def_readwrite("lcStatus", &NvDsAnalyticsObjInfo::lcStatus)
                .def_readwrite("dirStatus", &NvDsAnalyticsObjInfo::dirStatus)
                .def_readwrite("unique_id", &NvDsAnalyticsObjInfo::unique_id)

                .def_static("cast",
                            [](void *data) {
                                return (NvDsAnalyticsObjInfo *) data;
                            },
                            "data"_a, py::return_value_policy::reference,
                            pydsdoc::nvdsanalyticsdoc::NvDsAnalyticsObjInfoDoc::cast);


        py::class_<NvDsAnalyticsFrameMeta>(m, "NvDsAnalyticsFrameMeta",
                                           pydsdoc::nvdsanalyticsdoc::NvDsAnalyticsFrameMetaDoc::descr)
                .def(py::init<>())
                .def_readwrite("ocStatus", &NvDsAnalyticsFrameMeta::ocStatus)
                .def_readwrite("objInROIcnt",
                               &NvDsAnalyticsFrameMeta::objInROIcnt)
                .def_readwrite("objLCCurrCnt",
                               &NvDsAnalyticsFrameMeta::objLCCurrCnt)
                .def_readwrite("objLCCumCnt",
                               &NvDsAnalyticsFrameMeta::objLCCumCnt)
                .def_readwrite("unique_id", &NvDsAnalyticsFrameMeta::unique_id)
                .def_readwrite("objCnt", &NvDsAnalyticsFrameMeta::objCnt)

                .def_static("cast",
                            [](void *data) {
                                return (NvDsAnalyticsFrameMeta *) data;
                            },
                            "data"_a, py::return_value_policy::reference,
                            pydsdoc::nvdsanalyticsdoc::NvDsAnalyticsFrameMetaDoc::cast);
    }
}