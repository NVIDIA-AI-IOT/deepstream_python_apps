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

#include "pybind11/pybind11.h"
#include <string>

namespace py = pybind11;

#define STRING_PROPERTY(TYPE, FIELD)                               \
        [](const TYPE &self)->size_t {                             \
            return (size_t)self.FIELD;                             \
        },                                                         \
        [](TYPE &self, std::string str) {                          \
            int strSize = str.size();                              \
            self.FIELD = (char*)calloc(strSize + 1, sizeof(char)); \
            str.copy(self.FIELD, strSize);                         \
        },                                                         \
        py::return_value_policy::reference

#define STRING_FREE_EXISTING(TYPE, FIELD)                          \
        [](const TYPE &self)->size_t {                             \
            return (size_t)self.FIELD;                             \
        },                                                         \
        [](TYPE &self, std::string str) {                          \
            if (self.FIELD != nullptr)                             \
                free(self.FIELD);                                  \
            int strSize = str.size();                              \
            self.FIELD = (char*)calloc(strSize + 1, sizeof(char)); \
            str.copy(self.FIELD, strSize);                         \
        },                                                         \
        py::return_value_policy::reference

#define STRING_CHAR_ARRAY(TYPE, FIELD)                             \
        [](const TYPE &self)->std::string {                        \
            return std::string(self.FIELD);                        \
        },                                                         \
        [](TYPE &self, std::string str) {                          \
            int strSize = str.size();                              \
            str.copy(self.FIELD, strSize);                         \
        },                                                         \
        py::return_value_policy::reference

#define BUFFER_PROPERTY(TYPE, FIELD)                               \
        [](const TYPE &self)->size_t {                             \
            return (size_t)self.FIELD;                             \
        },                                                         \
        [](TYPE &self, size_t ptr) {                               \
            self.FIELD = (char*)ptr;                               \
        },                                                         \
        py::return_value_policy::reference

