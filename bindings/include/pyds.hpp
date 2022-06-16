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

#pragma  once

#include <memory>
#include <optional>
#include <pybind11.h>
#include "pybind11/pybind11.h"
#include "pybind11/cast.h"
#include "pybind11/pytypes.h"
#include "pybind11/numpy.h"
#include "pybind11/functional.h"
#include "pybind11/stl.h"
#include "gstnvdsmeta.h"
#include "nvdsmeta.h"
#include "nvbufsurface.h"
#include "nvds_latency_meta.h"
#include "nvdsmeta_schema.h"
#include "nvdsinfer.h"
#include "gstnvdsinfer.h"
#include "gst-nvevent.h"
#include <iostream>

#include <mutex>
#include "utils.hpp"
#include <Python.h>
#include "../docstrings/pydocumentation.h"
#include "nvds_opticalflow_meta.h"
#include "nvll_osd_struct.h"
#include "nvll_osd_api.h"
#include "nvds_analytics_meta.h"
#include "nvds_360d_meta.h"
#include "nvds_tracker_meta.h"

namespace py = pybind11;

namespace pydeepstream {
    // rewritting ""_a operator from pybind11 namespace and putting it into
    // pydeepstream namespace
    py::arg operator ""_a(const char *str, size_t len);
}