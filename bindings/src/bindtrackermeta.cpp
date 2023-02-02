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
        py::class_<NvDsPastFrameObj>(m, "NvDsPastFrameObj",
                                     pydsdoc::trackerdoc::NvDsPastFrameObjDoc::descr)
                .def(py::init<>())
                .def_readwrite("frameNum", &NvDsPastFrameObj::frameNum)
                .def_readwrite("tBbox", &NvDsPastFrameObj::tBbox)
                .def_readwrite("confidence", &NvDsPastFrameObj::confidence)
                .def_readwrite("age", &NvDsPastFrameObj::age)

                .def("cast",
                     [](void *data) {
                         return (NvDsPastFrameObj *) data;
                     },
                     py::return_value_policy::reference,
                     pydsdoc::trackerdoc::NvDsPastFrameObjDoc::cast);


        py::class_<NvDsPastFrameObjList>(m, "NvDsPastFrameObjList",
                                         pydsdoc::trackerdoc::NvDsPastFrameObjListDoc::descr)
                .def(py::init<>())
                .def_readwrite("numObj", &NvDsPastFrameObjList::numObj)
                .def_readwrite("uniqueId", &NvDsPastFrameObjList::uniqueId)
                .def_readwrite("classId", &NvDsPastFrameObjList::classId)
                .def_property("objLabel",
                              STRING_CHAR_ARRAY(NvDsPastFrameObjList, objLabel))

                .def("cast",
                     [](void *data) {
                         return (NvDsPastFrameObjList *) data;
                     },
                     py::return_value_policy::reference,
                     pydsdoc::trackerdoc::NvDsPastFrameObjListDoc::cast)

                .def("list",
                     [](NvDsPastFrameObjList &self) {
                         return py::make_iterator(self.list,
                                                  self.list + self.numObj);
                     },
                     py::keep_alive<0, 1>(), py::return_value_policy::reference,
                     pydsdoc::trackerdoc::NvDsPastFrameObjListDoc::list);


        py::class_<NvDsPastFrameObjStream>(m, "NvDsPastFrameObjStream",
                                           pydsdoc::trackerdoc::NvDsPastFrameObjStreamDoc::descr)
                .def(py::init<>())
                .def_readwrite("streamID", &NvDsPastFrameObjStream::streamID)
                .def_readwrite("surfaceStreamID",
                               &NvDsPastFrameObjStream::surfaceStreamID)
                .def_readwrite("numAllocated",
                               &NvDsPastFrameObjStream::numAllocated)
                .def_readwrite("numFilled", &NvDsPastFrameObjStream::numFilled)

                .def("cast",
                     [](void *data) {
                         return (NvDsPastFrameObjStream *) data;
                     },
                     py::return_value_policy::reference,
                     pydsdoc::trackerdoc::NvDsPastFrameObjStreamDoc::cast)

                .def("list",
                     [](NvDsPastFrameObjStream &self) {
                         return py::make_iterator(self.list,
                                                  self.list + self.numFilled);
                     },
                     py::keep_alive<0, 1>(), py::return_value_policy::reference,
                     pydsdoc::trackerdoc::NvDsPastFrameObjStreamDoc::list);


        py::class_<NvDsPastFrameObjBatch>(m, "NvDsPastFrameObjBatch",
                                          pydsdoc::trackerdoc::NvDsPastFrameObjBatchDoc::descr)
                .def(py::init<>())
                .def_readwrite("numAllocated",
                               &NvDsPastFrameObjBatch::numAllocated)
                .def_readwrite("numFilled", &NvDsPastFrameObjBatch::numFilled)

                .def("cast",
                     [](void *data) {
                         return (NvDsPastFrameObjBatch *) data;
                     },
                     py::return_value_policy::reference,
                     pydsdoc::trackerdoc::NvDsPastFrameObjBatchDoc::cast)

                .def("list",
                     [](NvDsPastFrameObjBatch &self) {
                         return py::make_iterator(self.list,
                                                  self.list + self.numFilled);
                     },
                     py::keep_alive<0, 1>(), py::return_value_policy::reference,
                     pydsdoc::trackerdoc::NvDsPastFrameObjBatchDoc::list);

    }

}
