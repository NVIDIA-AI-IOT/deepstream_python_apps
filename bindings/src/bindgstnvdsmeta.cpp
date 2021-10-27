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

// GstNvDsMeta

#include "bind_string_property_definitions.h"
#include "bindgstnvdsmeta.hpp"

namespace py = pybind11;

namespace pydeepstream {

    void bindgstnvdsmeta(py::module &m) {
        /*Start of Bindings for gstnvdsmeta.h*/
        /**
         * Specifies the type of meta data. NVIDIA defined GstNvDsMetaType will be present
         * in the range from @ref NVDS_BATCH_GST_META to @ref NVDS_START_USER_META
         * (refer nvdsmeta.h)
         * User can add it's own metadata type NVDS_RESERVED_GST_META onwards.
         */
        py::enum_<GstNvDsMetaType>(m, "GstNvDsMetaType",
                                   pydsdoc::nvmeta::GstNvDsMetaTypeDoc::descr)
                .value("NVDS_GST_INVALID_META", NVDS_GST_INVALID_META,
                       pydsdoc::nvmeta::GstNvDsMetaTypeDoc::NVDS_GST_INVALID_META)
                        /* contains information of formed batch */
                .value("NVDS_BATCH_GST_META", NVDS_BATCH_GST_META,
                       pydsdoc::nvmeta::GstNvDsMetaTypeDoc::NVDS_BATCH_GST_META)
                .value("NVDS_DECODER_GST_META", NVDS_DECODER_GST_META,
                       pydsdoc::nvmeta::GstNvDsMetaTypeDoc::NVDS_DECODER_GST_META)
                        /* contains information of dewarped surfaces */
                .value("NVDS_DEWARPER_GST_META", NVDS_DEWARPER_GST_META,
                       pydsdoc::nvmeta::GstNvDsMetaTypeDoc::NVDS_DEWARPER_GST_META)
                .value("NVDS_RESERVED_GST_META", NVDS_RESERVED_GST_META,
                       pydsdoc::nvmeta::GstNvDsMetaTypeDoc::NVDS_RESERVED_GST_META)
                        /* User can start adding it's own gst metadata from here onwards */
                .value("NVDS_GST_META_FORCE32", NVDS_GST_META_FORCE32,
                       pydsdoc::nvmeta::GstNvDsMetaTypeDoc::NVDS_GST_META_FORCE32)
                .export_values();


        py::class_<NvDsMeta>(m, "NvDsMeta", pydsdoc::nvmeta::NvDsMetaDoc::descr)
                .def(py::init<>())
                .def_readwrite("meta", &NvDsMeta::meta)
                .def_readwrite("meta_data", &NvDsMeta::meta_data)
                .def_readwrite("user_data", &NvDsMeta::user_data)
                .def_readwrite("meta_type", &NvDsMeta::meta_type)

                .def("cast",
                     [](void *data) {
                         return (NvDsMeta *) data;
                     },
                     py::return_value_policy::reference,
                     pydsdoc::nvmeta::NvDsMetaDoc::cast)

                .def("cast",
                     [](size_t data) {
                         return (NvDsMeta *) data;
                     },
                     py::return_value_policy::reference,
                     pydsdoc::nvmeta::NvDsMetaDoc::cast);
    }
}
