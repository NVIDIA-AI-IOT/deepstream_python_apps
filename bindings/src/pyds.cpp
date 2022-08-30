/*
 * SPDX-FileCopyrightText: Copyright (c) 2019-2021 NVIDIA CORPORATION & AFFILIATES. All rights reserved.
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


#include "bindanalyticsmeta.hpp"
#include "bindfunctions.hpp"
#include "bindgstnvdsmeta.hpp"
#include "bindmeta360.hpp"
#include "bindnvbufsurface.hpp"
#include "bindnvdsinfer.hpp"
#include "bindnvdsmeta.hpp"
#include "bindnvosd.hpp"
#include "bindopticalflow.hpp"
#include "bindschema.hpp"
#include "bindtrackermeta.hpp"

#include "pyds.hpp"

/*#define NPY_NO_DEPRECATED_API NPY_1_7_API_VERSION

#include <ndarrayobject.h>*/

#define PYDS_VERSION "1.1.4"

using namespace std;
namespace py = pybind11;

namespace pydeepstream {

    PYBIND11_MODULE(pyds, m) {
        m.doc() = "pybind11 bindings for gstnvdsmeta"; /* this will be the doc string*/
        m.attr("__version__") = PYDS_VERSION;

        py::class_<GList>(m, "GList")
                .def(py::init<>())
                .def_readwrite("data", &GList::data)
                .def_readwrite("next", &GList::next)
                .def_readwrite("prev", &GList::prev);

        bindnvosd(m);
        bindnvdsmeta(m);
        bindschema(m);
        bindfunctions(m);
        bindtrackermeta(m);
        bindmeta360(m);
        bindanalyticsmeta(m);
        bindgstnvdsmeta(m);
        bindnvbufsurface(m);
        bindnvdsinfer(m);
        bindopticalflowmeta(m);

    }   // end PYBIND11_MODULE(pyds, m)
}


