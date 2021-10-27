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

// NvBufSurface

#include "bindnvbufsurface.hpp"

namespace py = pybind11;

namespace pydeepstream {

    void bindnvbufsurface(py::module &m) {
        /*Start of Bindings for /nvutils/nvbufsurface/nvbufsurface.h*/
        py::enum_<NvBufSurfaceMemMapFlags>(m, "NvBufSurfaceMemMapFlags",
                                           pydsdoc::nvbufdoc::MemMapFlagsDoc::descr)
                .value("NVBUF_MAP_READ", NVBUF_MAP_READ,
                       pydsdoc::nvbufdoc::MemMapFlagsDoc::NVBUF_MAP_READ)
                .value("NVBUF_MAP_WRITE", NVBUF_MAP_WRITE,
                       pydsdoc::nvbufdoc::MemMapFlagsDoc::NVBUF_MAP_WRITE)
                .value("NVBUF_MAP_READ_WRITE", NVBUF_MAP_READ_WRITE,
                       pydsdoc::nvbufdoc::MemMapFlagsDoc::NVBUF_MAP_READ_WRITE)
                .export_values();


        py::enum_<NvBufSurfaceColorFormat>(m, "NvBufSurfaceColorFormat",
                                           pydsdoc::nvbufdoc::NvBufSurfaceColorFormatDoc::descr)
                .value("NVBUF_COLOR_FORMAT_INVALID", NVBUF_COLOR_FORMAT_INVALID,
                       pydsdoc::nvbufdoc::NvBufSurfaceColorFormatDoc::NVBUF_COLOR_FORMAT_INVALID)
                .value("NVBUF_COLOR_FORMAT_GRAY8", NVBUF_COLOR_FORMAT_GRAY8,
                       pydsdoc::nvbufdoc::NvBufSurfaceColorFormatDoc::NVBUF_COLOR_FORMAT_GRAY8)
                .value("NVBUF_COLOR_FORMAT_YUV420", NVBUF_COLOR_FORMAT_YUV420,
                       pydsdoc::nvbufdoc::NvBufSurfaceColorFormatDoc::NVBUF_COLOR_FORMAT_YUV420)
                .value("NVBUF_COLOR_FORMAT_YVU420", NVBUF_COLOR_FORMAT_YVU420,
                       pydsdoc::nvbufdoc::NvBufSurfaceColorFormatDoc::NVBUF_COLOR_FORMAT_YVU420)
                .value("NVBUF_COLOR_FORMAT_YUV420_ER",
                       NVBUF_COLOR_FORMAT_YUV420_ER,
                       pydsdoc::nvbufdoc::NvBufSurfaceColorFormatDoc::NVBUF_COLOR_FORMAT_YUV420_ER)
                .value("NVBUF_COLOR_FORMAT_YVU420_ER",
                       NVBUF_COLOR_FORMAT_YVU420_ER,
                       pydsdoc::nvbufdoc::NvBufSurfaceColorFormatDoc::NVBUF_COLOR_FORMAT_YVU420_ER)
                .value("NVBUF_COLOR_FORMAT_NV12", NVBUF_COLOR_FORMAT_NV12,
                       pydsdoc::nvbufdoc::NvBufSurfaceColorFormatDoc::NVBUF_COLOR_FORMAT_NV12)
                .value("NVBUF_COLOR_FORMAT_NV12_ER", NVBUF_COLOR_FORMAT_NV12_ER,
                       pydsdoc::nvbufdoc::NvBufSurfaceColorFormatDoc::NVBUF_COLOR_FORMAT_NV12_ER)
                .value("NVBUF_COLOR_FORMAT_NV21", NVBUF_COLOR_FORMAT_NV21,
                       pydsdoc::nvbufdoc::NvBufSurfaceColorFormatDoc::NVBUF_COLOR_FORMAT_NV21)
                .value("NVBUF_COLOR_FORMAT_NV21_ER", NVBUF_COLOR_FORMAT_NV21_ER,
                       pydsdoc::nvbufdoc::NvBufSurfaceColorFormatDoc::NVBUF_COLOR_FORMAT_NV21_ER)
                .value("NVBUF_COLOR_FORMAT_UYVY", NVBUF_COLOR_FORMAT_UYVY,
                       pydsdoc::nvbufdoc::NvBufSurfaceColorFormatDoc::NVBUF_COLOR_FORMAT_UYVY)
                .value("NVBUF_COLOR_FORMAT_UYVY_ER", NVBUF_COLOR_FORMAT_UYVY_ER,
                       pydsdoc::nvbufdoc::NvBufSurfaceColorFormatDoc::NVBUF_COLOR_FORMAT_UYVY_ER)
                .value("NVBUF_COLOR_FORMAT_VYUY", NVBUF_COLOR_FORMAT_VYUY,
                       pydsdoc::nvbufdoc::NvBufSurfaceColorFormatDoc::NVBUF_COLOR_FORMAT_VYUY)
                .value("NVBUF_COLOR_FORMAT_VYUY_ER", NVBUF_COLOR_FORMAT_VYUY_ER,
                       pydsdoc::nvbufdoc::NvBufSurfaceColorFormatDoc::NVBUF_COLOR_FORMAT_VYUY_ER)
                .value("NVBUF_COLOR_FORMAT_YUYV", NVBUF_COLOR_FORMAT_YUYV,
                       pydsdoc::nvbufdoc::NvBufSurfaceColorFormatDoc::NVBUF_COLOR_FORMAT_YUYV)
                .value("NVBUF_COLOR_FORMAT_YUYV_ER", NVBUF_COLOR_FORMAT_YUYV_ER,
                       pydsdoc::nvbufdoc::NvBufSurfaceColorFormatDoc::NVBUF_COLOR_FORMAT_YUYV_ER)
                .value("NVBUF_COLOR_FORMAT_YVYU", NVBUF_COLOR_FORMAT_YVYU,
                       pydsdoc::nvbufdoc::NvBufSurfaceColorFormatDoc::NVBUF_COLOR_FORMAT_YVYU)
                .value("NVBUF_COLOR_FORMAT_YVYU_ER", NVBUF_COLOR_FORMAT_YVYU_ER,
                       pydsdoc::nvbufdoc::NvBufSurfaceColorFormatDoc::NVBUF_COLOR_FORMAT_YVYU_ER)
                .value("NVBUF_COLOR_FORMAT_YUV444", NVBUF_COLOR_FORMAT_YUV444,
                       pydsdoc::nvbufdoc::NvBufSurfaceColorFormatDoc::NVBUF_COLOR_FORMAT_YUV444)
                .value("NVBUF_COLOR_FORMAT_RGBA", NVBUF_COLOR_FORMAT_RGBA,
                       pydsdoc::nvbufdoc::NvBufSurfaceColorFormatDoc::NVBUF_COLOR_FORMAT_RGBA)
                .value("NVBUF_COLOR_FORMAT_BGRA", NVBUF_COLOR_FORMAT_BGRA,
                       pydsdoc::nvbufdoc::NvBufSurfaceColorFormatDoc::NVBUF_COLOR_FORMAT_BGRA)
                .value("NVBUF_COLOR_FORMAT_ARGB", NVBUF_COLOR_FORMAT_ARGB,
                       pydsdoc::nvbufdoc::NvBufSurfaceColorFormatDoc::NVBUF_COLOR_FORMAT_ARGB)
                .value("NVBUF_COLOR_FORMAT_ABGR", NVBUF_COLOR_FORMAT_ABGR,
                       pydsdoc::nvbufdoc::NvBufSurfaceColorFormatDoc::NVBUF_COLOR_FORMAT_ABGR)
                .value("NVBUF_COLOR_FORMAT_RGBx", NVBUF_COLOR_FORMAT_RGBx,
                       pydsdoc::nvbufdoc::NvBufSurfaceColorFormatDoc::NVBUF_COLOR_FORMAT_RGBx)
                .value("NVBUF_COLOR_FORMAT_BGRx", NVBUF_COLOR_FORMAT_BGRx,
                       pydsdoc::nvbufdoc::NvBufSurfaceColorFormatDoc::NVBUF_COLOR_FORMAT_BGRx)
                .value("NVBUF_COLOR_FORMAT_xRGB", NVBUF_COLOR_FORMAT_xRGB,
                       pydsdoc::nvbufdoc::NvBufSurfaceColorFormatDoc::NVBUF_COLOR_FORMAT_xRGB)
                .value("NVBUF_COLOR_FORMAT_xBGR", NVBUF_COLOR_FORMAT_xBGR,
                       pydsdoc::nvbufdoc::NvBufSurfaceColorFormatDoc::NVBUF_COLOR_FORMAT_xBGR)
                .value("NVBUF_COLOR_FORMAT_RGB", NVBUF_COLOR_FORMAT_RGB,
                       pydsdoc::nvbufdoc::NvBufSurfaceColorFormatDoc::NVBUF_COLOR_FORMAT_RGB)
                .value("NVBUF_COLOR_FORMAT_BGR", NVBUF_COLOR_FORMAT_BGR,
                       pydsdoc::nvbufdoc::NvBufSurfaceColorFormatDoc::NVBUF_COLOR_FORMAT_BGR)
                .value("NVBUF_COLOR_FORMAT_NV12_10LE",
                       NVBUF_COLOR_FORMAT_NV12_10LE,
                       pydsdoc::nvbufdoc::NvBufSurfaceColorFormatDoc::NVBUF_COLOR_FORMAT_NV12_10LE)
                .value("NVBUF_COLOR_FORMAT_NV12_12LE",
                       NVBUF_COLOR_FORMAT_NV12_12LE,
                       pydsdoc::nvbufdoc::NvBufSurfaceColorFormatDoc::NVBUF_COLOR_FORMAT_NV12_12LE)
                .value("NVBUF_COLOR_FORMAT_YUV420_709",
                       NVBUF_COLOR_FORMAT_YUV420_709,
                       pydsdoc::nvbufdoc::NvBufSurfaceColorFormatDoc::NVBUF_COLOR_FORMAT_YUV420_709)
                .value("NVBUF_COLOR_FORMAT_YUV420_709_ER",
                       NVBUF_COLOR_FORMAT_YUV420_709_ER,
                       pydsdoc::nvbufdoc::NvBufSurfaceColorFormatDoc::NVBUF_COLOR_FORMAT_YUV420_709_ER)
                .value("NVBUF_COLOR_FORMAT_NV12_709",
                       NVBUF_COLOR_FORMAT_NV12_709,
                       pydsdoc::nvbufdoc::NvBufSurfaceColorFormatDoc::NVBUF_COLOR_FORMAT_NV12_709)
                .value("NVBUF_COLOR_FORMAT_NV12_709_ER",
                       NVBUF_COLOR_FORMAT_NV12_709_ER,
                       pydsdoc::nvbufdoc::NvBufSurfaceColorFormatDoc::NVBUF_COLOR_FORMAT_NV12_709_ER)
                .value("NVBUF_COLOR_FORMAT_YUV420_2020",
                       NVBUF_COLOR_FORMAT_YUV420_2020,
                       pydsdoc::nvbufdoc::NvBufSurfaceColorFormatDoc::NVBUF_COLOR_FORMAT_YUV420_2020)
                .value("NVBUF_COLOR_FORMAT_NV12_2020",
                       NVBUF_COLOR_FORMAT_NV12_2020,
                       pydsdoc::nvbufdoc::NvBufSurfaceColorFormatDoc::NVBUF_COLOR_FORMAT_NV12_2020)
                .value("NVBUF_COLOR_FORMAT_NV12_10LE_ER",
                       NVBUF_COLOR_FORMAT_NV12_10LE_ER,
                       pydsdoc::nvbufdoc::NvBufSurfaceColorFormatDoc::NVBUF_COLOR_FORMAT_NV12_10LE_ER)
                .value("NVBUF_COLOR_FORMAT_NV12_10LE_709",
                       NVBUF_COLOR_FORMAT_NV12_10LE_709,
                       pydsdoc::nvbufdoc::NvBufSurfaceColorFormatDoc::NVBUF_COLOR_FORMAT_NV12_10LE_709)
                .value("NVBUF_COLOR_FORMAT_NV12_10LE_709_ER",
                       NVBUF_COLOR_FORMAT_NV12_10LE_709_ER,
                       pydsdoc::nvbufdoc::NvBufSurfaceColorFormatDoc::NVBUF_COLOR_FORMAT_NV12_10LE_709_ER)
                .value("NVBUF_COLOR_FORMAT_NV12_10LE_2020",
                       NVBUF_COLOR_FORMAT_NV12_10LE_2020,
                       pydsdoc::nvbufdoc::NvBufSurfaceColorFormatDoc::NVBUF_COLOR_FORMAT_NV12_10LE_2020)
                .value("NVBUF_COLOR_FORMAT_SIGNED_R16G16",
                       NVBUF_COLOR_FORMAT_SIGNED_R16G16,
                       pydsdoc::nvbufdoc::NvBufSurfaceColorFormatDoc::NVBUF_COLOR_FORMAT_SIGNED_R16G16)
                .value("NVBUF_COLOR_FORMAT_LAST", NVBUF_COLOR_FORMAT_LAST,
                       pydsdoc::nvbufdoc::NvBufSurfaceColorFormatDoc::NVBUF_COLOR_FORMAT_LAST)
                .export_values();


        py::enum_<NvBufSurfaceLayout>(m, "NvBufSurfaceLayout",
                                      pydsdoc::nvbufdoc::NvBufSurfaceLayoutDoc::descr)
                .value("NVBUF_LAYOUT_PITCH", NVBUF_LAYOUT_PITCH,
                       pydsdoc::nvbufdoc::NvBufSurfaceLayoutDoc::NVBUF_LAYOUT_PITCH)
                .value("NVBUF_LAYOUT_BLOCK_LINEAR", NVBUF_LAYOUT_BLOCK_LINEAR,
                       pydsdoc::nvbufdoc::NvBufSurfaceLayoutDoc::NVBUF_LAYOUT_BLOCK_LINEAR)
                .export_values();


        py::enum_<NvBufSurfaceMemType>(m, "NvBufSurfaceMemType",
                                       pydsdoc::nvbufdoc::NvBufSurfaceMemTypeDoc::descr)
                .value("NVBUF_MEM_DEFAULT", NVBUF_MEM_DEFAULT,
                       pydsdoc::nvbufdoc::NvBufSurfaceMemTypeDoc::NVBUF_MEM_DEFAULT)
                .value("NVBUF_MEM_CUDA_PINNED", NVBUF_MEM_CUDA_PINNED,
                       pydsdoc::nvbufdoc::NvBufSurfaceMemTypeDoc::NVBUF_MEM_CUDA_PINNED)
                .value("NVBUF_MEM_CUDA_DEVICE", NVBUF_MEM_CUDA_DEVICE,
                       pydsdoc::nvbufdoc::NvBufSurfaceMemTypeDoc::NVBUF_MEM_CUDA_DEVICE)
                .value("NVBUF_MEM_CUDA_UNIFIED", NVBUF_MEM_CUDA_UNIFIED,
                       pydsdoc::nvbufdoc::NvBufSurfaceMemTypeDoc::NVBUF_MEM_CUDA_UNIFIED)
                .value("NVBUF_MEM_SURFACE_ARRAY", NVBUF_MEM_SURFACE_ARRAY,
                       pydsdoc::nvbufdoc::NvBufSurfaceMemTypeDoc::NVBUF_MEM_SURFACE_ARRAY)
                .value("NVBUF_MEM_HANDLE", NVBUF_MEM_HANDLE,
                       pydsdoc::nvbufdoc::NvBufSurfaceMemTypeDoc::NVBUF_MEM_HANDLE)
                .value("NVBUF_MEM_SYSTEM", NVBUF_MEM_SYSTEM,
                       pydsdoc::nvbufdoc::NvBufSurfaceMemTypeDoc::NVBUF_MEM_SYSTEM)
                .export_values();


        py::class_<NvBufSurfacePlaneParams>(m, "NvBufSurfacePlaneParams",
                                            py::buffer_protocol(),
                                            pydsdoc::nvbufdoc::NvBufSurfacePlaneParamsDoc::descr)
                .def(py::init<>())
                .def_readwrite("num_planes",
                               &NvBufSurfacePlaneParams::num_planes)

                .def_property("width",
                              [](NvBufSurfacePlaneParams &self) -> py::array {
                                  auto dtype = py::dtype(
                                          py::format_descriptor<int>::format());
                                  auto base = py::array(dtype,
                                                        {NVBUF_MAX_PLANES},
                                                        {sizeof(int)});
                                  return py::array(dtype, {NVBUF_MAX_PLANES},
                                                   {sizeof(int)}, self.width,
                                                   base);
                              },
                              [](NvBufSurfacePlaneParams &self) {})

                .def_property("height",
                              [](NvBufSurfacePlaneParams &self) -> py::array {
                                  auto dtype = py::dtype(
                                          py::format_descriptor<int>::format());
                                  auto base = py::array(dtype,
                                                        {NVBUF_MAX_PLANES},
                                                        {sizeof(int)});
                                  return py::array(dtype, {NVBUF_MAX_PLANES},
                                                   {sizeof(int)}, self.height,
                                                   base);
                              },
                              [](NvBufSurfacePlaneParams &self) {})

                .def_property("pitch",
                              [](NvBufSurfacePlaneParams &self) -> py::array {
                                  auto dtype = py::dtype(
                                          py::format_descriptor<int>::format());
                                  auto base = py::array(dtype,
                                                        {NVBUF_MAX_PLANES},
                                                        {sizeof(int)});
                                  return py::array(dtype, {NVBUF_MAX_PLANES},
                                                   {sizeof(int)}, self.pitch,
                                                   base);
                              },
                              [](NvBufSurfacePlaneParams &self) {})

                .def_property("offset",
                              [](NvBufSurfacePlaneParams &self) -> py::array {
                                  auto dtype = py::dtype(
                                          py::format_descriptor<int>::format());
                                  auto base = py::array(dtype,
                                                        {NVBUF_MAX_PLANES},
                                                        {sizeof(int)});
                                  return py::array(dtype, {NVBUF_MAX_PLANES},
                                                   {sizeof(int)}, self.offset,
                                                   base);
                              },
                              [](NvBufSurfacePlaneParams &self) {})

                .def_property("psize",
                              [](NvBufSurfacePlaneParams &self) -> py::array {
                                  auto dtype = py::dtype(
                                          py::format_descriptor<int>::format());
                                  auto base = py::array(dtype,
                                                        {NVBUF_MAX_PLANES},
                                                        {sizeof(int)});
                                  return py::array(dtype, {NVBUF_MAX_PLANES},
                                                   {sizeof(int)}, self.psize,
                                                   base);
                              },
                              [](NvBufSurfacePlaneParams &self) {})

                .def_property("bytesPerPix",
                              [](NvBufSurfacePlaneParams &self) -> py::array {
                                  auto dtype = py::dtype(
                                          py::format_descriptor<int>::format());
                                  auto base = py::array(dtype,
                                                        {NVBUF_MAX_PLANES},
                                                        {sizeof(int)});
                                  return py::array(dtype, {NVBUF_MAX_PLANES},
                                                   {sizeof(int)},
                                                   self.bytesPerPix, base);
                              },
                              [](NvBufSurfacePlaneParams &self) {})

                .def("cast",
                     [](void *data) {
                         return (NvBufSurfacePlaneParams *) data;
                     },
                     py::return_value_policy::reference,
                     pydsdoc::nvbufdoc::NvBufSurfacePlaneParamsDoc::cast)

                .def("cast",
                     [](size_t data) {
                         return (NvBufSurfacePlaneParams *) data;
                     },
                     py::return_value_policy::reference,
                     pydsdoc::nvbufdoc::NvBufSurfacePlaneParamsDoc::cast);

        py::class_<NvBufSurfaceCreateParams>(m, "NvBufSurfaceCreateParams",
                                             pydsdoc::nvbufdoc::NvBufSurfaceCreateParamsDocs::descr)
                .def(py::init<>())
                .def_readonly("gpuId", &NvBufSurfaceCreateParams::gpuId)
                .def_readonly("width", &NvBufSurfaceCreateParams::width)
                .def_readonly("height", &NvBufSurfaceCreateParams::height)
                .def_readonly("size", &NvBufSurfaceCreateParams::size)
                .def_readonly("isContiguous",
                              &NvBufSurfaceCreateParams::isContiguous)
                .def_readonly("colorFormat",
                              &NvBufSurfaceCreateParams::colorFormat)
                .def_readonly("layout", &NvBufSurfaceCreateParams::layout)
                .def_readonly("memType", &NvBufSurfaceCreateParams::memType)

                .def("cast",
                     [](void *data) {
                         return (NvBufSurfaceCreateParams *) data;
                     },
                     py::return_value_policy::reference,
                     pydsdoc::nvbufdoc::NvBufSurfaceCreateParamsDocs::cast)

                .def("cast",
                     [](size_t data) {
                         return (NvBufSurfaceCreateParams *) data;
                     },
                     py::return_value_policy::reference,
                     pydsdoc::nvbufdoc::NvBufSurfaceCreateParamsDocs::cast);


        py::class_<NvBufSurfaceMappedAddr>(m, "NvBufSurfaceMappedAddr",
                                           py::buffer_protocol(),
                                           pydsdoc::nvbufdoc::NvBufSurfaceMappedAddrDoc::descr)
                .def(py::init<>())

                .def_property("addr",
                              [](NvBufSurfaceMappedAddr &self) -> py::array {
                                  auto dtype = py::dtype(
                                          py::format_descriptor<uintptr_t>::format());
                                  auto base = py::array(dtype,
                                                        {NVBUF_MAX_PLANES},
                                                        {sizeof(uintptr_t)});
                                  return py::array(dtype, {NVBUF_MAX_PLANES},
                                                   {sizeof(uintptr_t)},
                                                   self.addr, base);
                              },
                              [](NvBufSurfaceMappedAddr &self) {})

                .def_readonly("eglImage", &NvBufSurfaceMappedAddr::eglImage)

                .def("cast",
                     [](void *data) {
                         return (NvBufSurfaceMappedAddr *) data;
                     },
                     py::return_value_policy::reference,
                     pydsdoc::nvbufdoc::NvBufSurfaceMappedAddrDoc::cast)

                .def("cast",
                     [](size_t data) {
                         return (NvBufSurfaceMappedAddr *) data;
                     },
                     py::return_value_policy::reference,
                     pydsdoc::nvbufdoc::NvBufSurfaceMappedAddrDoc::cast);

        py::class_<NvBufSurfaceParams>(m, "NvBufSurfaceParams",
                                       pydsdoc::nvbufdoc::NvBufSurfaceParamsDoc::descr)
                .def(py::init<>())
                .def_readonly("width", &NvBufSurfaceParams::width)
                .def_readonly("height", &NvBufSurfaceParams::height)
                .def_readonly("pitch", &NvBufSurfaceParams::pitch)
                .def_readonly("colorFormat", &NvBufSurfaceParams::colorFormat)
                .def_readonly("layout", &NvBufSurfaceParams::layout)
                .def_readonly("bufferDesc", &NvBufSurfaceParams::bufferDesc)
                .def_readonly("dataSize", &NvBufSurfaceParams::dataSize)
                .def_readonly("dataPtr", &NvBufSurfaceParams::dataPtr)
                .def_readonly("planeParams", &NvBufSurfaceParams::planeParams)
                .def_readonly("mappedAddr", &NvBufSurfaceParams::mappedAddr)

                .def("cast",
                     [](void *data) {
                         return (NvBufSurfaceParams *) data;
                     },
                     py::return_value_policy::reference,
                     pydsdoc::nvbufdoc::NvBufSurfaceParamsDoc::cast)

                .def("cast",
                     [](size_t data) {
                         return (NvBufSurfaceParams *) data;
                     },
                     py::return_value_policy::reference,
                     pydsdoc::nvbufdoc::NvBufSurfaceParamsDoc::cast);

        py::class_<NvBufSurface>(m, "NvBufSurface",
                                 pydsdoc::nvbufdoc::NvBufSurfaceDoc::descr)
                .def(py::init<>())
                .def_readonly("gpuId", &NvBufSurface::gpuId)
                .def_readonly("batchSize", &NvBufSurface::batchSize)
                .def_readonly("numFilled", &NvBufSurface::numFilled)
                .def_readonly("isContiguous", &NvBufSurface::isContiguous)
                .def_readonly("memType", &NvBufSurface::memType)
                .def_readonly("surfaceList", &NvBufSurface::surfaceList)

                .def("cast",
                     [](void *data) {
                         return (NvBufSurface *) data;
                     },
                     py::return_value_policy::reference,
                     pydsdoc::nvbufdoc::NvBufSurfaceDoc::cast)

                .def("cast",
                     [](size_t data) {
                         return (NvBufSurface *) data;
                     },
                     py::return_value_policy::reference,
                     pydsdoc::nvbufdoc::NvBufSurfaceDoc::cast);
    }
}
