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

// NvDsTrackerMeta

#include "bind_string_property_definitions.h"
#include "bindtrackermeta.hpp"

namespace py = pybind11;

namespace pydeepstream {
    void bindtrackermeta(py::module &m) {
        /*Start of Bindings for nvds_tracker_meta.h*/
        py::class_<NvDsTargetMiscDataFrame>(m, "NvDsTargetMiscDataFrame",
                                     pydsdoc::trackerdoc::NvDsTargetMiscDataFrameDoc::descr)
                .def(py::init<>())
                .def_readwrite("frameNum", &NvDsTargetMiscDataFrame::frameNum)
                .def_readwrite("tBbox", &NvDsTargetMiscDataFrame::tBbox)
                .def_readwrite("confidence", &NvDsTargetMiscDataFrame::confidence)
                .def_readwrite("age", &NvDsTargetMiscDataFrame::age)

                .def("cast",
                     [](void *data) {
                         return (NvDsTargetMiscDataFrame *) data;
                     },
                     py::return_value_policy::reference,
                     pydsdoc::trackerdoc::NvDsTargetMiscDataFrameDoc::cast);


        py::class_<NvDsTargetMiscDataObject>(m, "NvDsTargetMiscDataObject",
                                         pydsdoc::trackerdoc::NvDsTargetMiscDataObjectDoc::descr)
                .def(py::init<>())
                .def_readwrite("numObj", &NvDsTargetMiscDataObject::numObj)
                .def_readwrite("uniqueId", &NvDsTargetMiscDataObject::uniqueId)
                .def_readwrite("classId", &NvDsTargetMiscDataObject::classId)
                .def_property("objLabel",
                              STRING_CHAR_ARRAY(NvDsTargetMiscDataObject, objLabel))

                .def("cast",
                     [](void *data) {
                         return (NvDsTargetMiscDataObject *) data;
                     },
                     py::return_value_policy::reference,
                     pydsdoc::trackerdoc::NvDsTargetMiscDataObjectDoc::cast)

                .def("list",
                     [](NvDsTargetMiscDataObject &self) {
                         return py::make_iterator(self.list,
                                                  self.list + self.numObj);
                     },
                     py::keep_alive<0, 1>(), py::return_value_policy::reference,
                     pydsdoc::trackerdoc::NvDsTargetMiscDataObjectDoc::list);


        py::class_<NvDsTargetMiscDataStream>(m, "NvDsTargetMiscDataStream",
                                           pydsdoc::trackerdoc::NvDsTargetMiscDataStreamDoc::descr)
                .def(py::init<>())
                .def_readwrite("streamID", &NvDsTargetMiscDataStream::streamID)
                .def_readwrite("surfaceStreamID",
                               &NvDsTargetMiscDataStream::surfaceStreamID)
                .def_readwrite("numAllocated",
                               &NvDsTargetMiscDataStream::numAllocated)
                .def_readwrite("numFilled", &NvDsTargetMiscDataStream::numFilled)

                .def("cast",
                     [](void *data) {
                         return (NvDsTargetMiscDataStream *) data;
                     },
                     py::return_value_policy::reference,
                     pydsdoc::trackerdoc::NvDsTargetMiscDataStreamDoc::cast)

                .def("list",
                     [](NvDsTargetMiscDataStream &self) {
                         return py::make_iterator(self.list,
                                                  self.list + self.numFilled);
                     },
                     py::keep_alive<0, 1>(), py::return_value_policy::reference,
                     pydsdoc::trackerdoc::NvDsTargetMiscDataStreamDoc::list);


        py::class_<NvDsTargetMiscDataBatch>(m, "NvDsTargetMiscDataBatch",
                                          pydsdoc::trackerdoc::NvDsTargetMiscDataBatchDoc::descr)
                .def(py::init<>())
                .def_readwrite("numAllocated",
                               &NvDsTargetMiscDataBatch::numAllocated)
                .def_readwrite("numFilled", &NvDsTargetMiscDataBatch::numFilled)

                .def("cast",
                     [](void *data) {
                         return (NvDsTargetMiscDataBatch *) data;
                     },
                     py::return_value_policy::reference,
                     pydsdoc::trackerdoc::NvDsTargetMiscDataBatchDoc::cast)

                .def("list",
                     [](NvDsTargetMiscDataBatch &self) {
                         return py::make_iterator(self.list,
                                                  self.list + self.numFilled);
                     },
                     py::keep_alive<0, 1>(), py::return_value_policy::reference,
                     pydsdoc::trackerdoc::NvDsTargetMiscDataBatchDoc::list);


         py::class_<NvDsObjReid>(m, "NvDsObjReid",
                                pydsdoc::trackerdoc::NvDsObjReidDoc::descr)
                .def(py::init<>())
                .def_readwrite("featureSize",
                               &NvDsObjReid::featureSize)
                // Expose a method to get the ReID vector as a NumPy array
                .def("get_host_reid_vector", [](NvDsObjReid &self) {
                    return py::array_t<float>(
                        {self.featureSize},       // Shape of the array
                        {sizeof(float)},          // Stride of the array
                        self.ptr_host           // Data pointer (ptr_host from C++)
                    );
                }, "Returns Host ReID vector as NumPy array")
                .def("cast",
                     [](void *data) {
                         return (NvDsObjReid *) data;
                     },
                     py::return_value_policy::reference,
                     pydsdoc::trackerdoc::NvDsObjReidDoc::cast);
    }

}
