/*
 * SPDX-FileCopyrightText: Copyright (c) 2022 NVIDIA CORPORATION & AFFILIATES. All rights reserved.
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

// CustomDataStruct

#include "bind_string_property_definitions.h"
#include "include/bindcustom.hpp"

namespace py = pybind11;

namespace pydeepstream {

    void * copy_custom_struct(void* data, void* user_data) {
        NvDsUserMeta * srcMeta = (NvDsUserMeta*) data;
        CustomDataStruct * srcData = (CustomDataStruct *) srcMeta->user_meta_data;
        CustomDataStruct *destData = (CustomDataStruct *) g_malloc0(
                        sizeof(CustomDataStruct));
        destData->structId = srcData->structId;
        destData->sampleInt = srcData->sampleInt;
        if (srcData->message != nullptr) {
            char* srcString = (char *) srcData->message;
            int strSize = strlen(srcString);
            destData->message = (char*)calloc(strSize + 1, sizeof(char));
            strcpy(destData->message, srcData->message);
        }
        return destData;
    }

    void release_custom_struct(void * data, void * user_data) {
        NvDsUserMeta * srcMeta = (NvDsUserMeta*) data;
        if (srcMeta != nullptr) {
            CustomDataStruct * srcData = (CustomDataStruct *) srcMeta->user_meta_data;
            if (srcData != nullptr) {
                auto * message = srcData->message;
                srcData->structId = 0;
                srcData->sampleInt = 0;
                if (srcData->message != nullptr)
                {
                    free(srcData->message);
                }
                g_free(srcData);
            }
        }
    }

    void bindcustom(py::module &m) {
                /* CustomDataStruct bindings to be used with NvDsUserMeta */
                py::class_<CustomDataStruct>(m, "CustomDataStruct",
                                pydsdoc::custom::CustomDataStructDoc::descr)
                .def(py::init<>())
                .def_readwrite("structId", &CustomDataStruct::structId)
                .def_property("message", STRING_FREE_EXISTING(CustomDataStruct, message))
                .def_readwrite("sampleInt", &CustomDataStruct::sampleInt)

                .def("cast",
                     [](void *data) {
                         return (CustomDataStruct *) data;
                     },
                     py::return_value_policy::reference,
                     pydsdoc::custom::CustomDataStructDoc::cast);

        m.def("alloc_custom_struct",
              [](NvDsUserMeta *meta) {
                  auto *mem = (CustomDataStruct *) g_malloc0(
                          sizeof(CustomDataStruct));
                  meta->base_meta.copy_func = (NvDsMetaCopyFunc) pydeepstream::copy_custom_struct;
                  meta->base_meta.release_func = (NvDsMetaReleaseFunc) pydeepstream::release_custom_struct;
                  return mem;
              },
              py::return_value_policy::reference,
              pydsdoc::methodsDoc::alloc_custom_struct);

    }

}