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

// NvOSD

#include "bind_string_property_definitions.h"
#include "utils.hpp"
#include "bindnvosd.hpp"

namespace py = pybind11;

namespace pydeepstream {

    void bindnvosd(py::module &m) {
        /*Start of Bindings for nvll_osd_struct.h*/
        py::enum_<NvOSD_Mode>(m, "NvOSD_Mode",
                              pydsdoc::NvOSD::NvOSD_Mode::descr)
                .value("MODE_CPU", MODE_CPU,
                       pydsdoc::NvOSD::NvOSD_Mode::MODE_CPU)
                .value("MODE_GPU", MODE_GPU,
                       pydsdoc::NvOSD::NvOSD_Mode::MODE_GPU)
                .value("MODE_NONE", MODE_NONE, pydsdoc::NvOSD::NvOSD_Mode::MODE_NONE)
                .export_values();


        py::enum_<NvOSD_Arrow_Head_Direction>(m, "NvOSD_Arrow_Head_Direction",
                                              pydsdoc::NvOSD::NvOSD_Arrow_Head_Direction::descr)
                .value("START_HEAD", START_HEAD,
                       pydsdoc::NvOSD::NvOSD_Arrow_Head_Direction::START_HEAD)
                .value("END_HEAD", END_HEAD,
                       pydsdoc::NvOSD::NvOSD_Arrow_Head_Direction::END_HEAD)
                .value("BOTH_HEAD", BOTH_HEAD,
                       pydsdoc::NvOSD::NvOSD_Arrow_Head_Direction::BOTH_HEAD)
                .export_values();


        py::class_<NvBbox_Coords>(m, "NvBbox_Coords",
                                  pydsdoc::NvOSD::NvBbox_Coords::descr)
                .def(py::init<>())
                .def_readwrite("left", &NvBbox_Coords::left)
                .def_readwrite("top", &NvBbox_Coords::top)
                .def_readwrite("width", &NvBbox_Coords::width)
                .def_readwrite("height", &NvBbox_Coords::height)

                .def("cast", [](void *data) {
                         return (NvBbox_Coords *) data;
                     },
                     py::return_value_policy::reference,
                     pydsdoc::NvOSD::NvBbox_Coords::cast)

                .def("cast", [](size_t data) {
                         return (NvBbox_Coords *) data;
                     },
                     py::return_value_policy::reference,
                     pydsdoc::NvOSD::NvBbox_Coords::cast);

        py::class_<NvOSD_ColorParams>(m, "NvOSD_ColorParams",
                                      pydsdoc::NvOSD::ColorParamsDoc::descr)
                .def(py::init<>())
                .def_readwrite("red", &NvOSD_ColorParams::red)
                .def_readwrite("green", &NvOSD_ColorParams::green)
                .def_readwrite("blue", &NvOSD_ColorParams::blue)
                .def_readwrite("alpha", &NvOSD_ColorParams::alpha)

                .def("cast",
                     [](void *data) {
                         return (NvOSD_ColorParams *) data;
                     },
                     py::return_value_policy::reference,
                     pydsdoc::NvOSD::ColorParamsDoc::cast)

                .def("cast",
                     [](size_t data) {
                         return (NvOSD_ColorParams *) data;
                     },
                     py::return_value_policy::reference,
                     pydsdoc::NvOSD::ColorParamsDoc::cast)

                .def("set",
                     [](NvOSD_ColorParams *color, double red, double green,
                        double blue, double alpha) {
                         if (color) {
                             color->red = red;
                             color->green = green;
                             color->blue = blue;
                             color->alpha = alpha;
                         }
                     },
                     "red"_a, "green"_a, "blue"_a,
                     "alpha"_a, pydsdoc::NvOSD::ColorParamsDoc::set);


        py::class_<NvOSD_FontParams>(m, "NvOSD_FontParams",
                                     pydsdoc::NvOSD::FontParamsDoc::descr)
                .def(py::init<>())
                .def_property("font_name",
                              utils::get_field_content_lambda<NvOSD_FontParams>(
                                      &NvOSD_FontParams::font_name),
                              utils::set_field_content_string_lambda<NvOSD_FontParams>(
                                      &NvOSD_FontParams::font_name),
                              py::return_value_policy::reference)
                .def_readwrite("font_size", &NvOSD_FontParams::font_size)
                .def_readwrite("font_color", &NvOSD_FontParams::font_color)

                .def("cast",
                     [](void *data) {
                         return (NvOSD_FontParams *) data;
                     },
                     py::return_value_policy::reference,
                     pydsdoc::NvOSD::FontParamsDoc::cast)

                .def("cast",
                     [](size_t data) {
                         return (NvOSD_FontParams *) data;
                     },
                     py::return_value_policy::reference,
                     pydsdoc::NvOSD::FontParamsDoc::cast);


        py::class_<NvOSD_TextParams>(m, "NvOSD_TextParams",
                                     pydsdoc::NvOSD::TextParamsDoc::descr)
                .def(py::init<>())
                .def_property("display_text",
                              STRING_FREE_EXISTING(NvOSD_TextParams,
                                                   display_text))
                .def_readwrite("x_offset", &NvOSD_TextParams::x_offset)
                .def_readwrite("y_offset", &NvOSD_TextParams::y_offset)
                .def_readwrite("font_params", &NvOSD_TextParams::font_params)
                .def_readwrite("set_bg_clr", &NvOSD_TextParams::set_bg_clr)
                .def_readwrite("text_bg_clr", &NvOSD_TextParams::text_bg_clr)

                .def("cast",
                     [](void *data) {
                         return (NvOSD_TextParams *) data;
                     },
                     py::return_value_policy::reference,
                     pydsdoc::NvOSD::TextParamsDoc::cast)

                .def("cast",
                     [](size_t data) {
                         return (NvOSD_TextParams *) data;
                     },
                     py::return_value_policy::reference,
                     pydsdoc::NvOSD::TextParamsDoc::cast);


        py::class_<NvOSD_Color_info>(m, "NvOSD_Color_info",
                                     pydsdoc::NvOSD::Color_infoDoc::descr)
                .def(py::init<>())
                .def_readwrite("id", &NvOSD_Color_info::id)
                .def_readwrite("color", &NvOSD_Color_info::color)

                .def("cast",
                     [](void *data) {
                         return (NvOSD_Color_info *) data;
                     },
                     py::return_value_policy::reference,
                     pydsdoc::NvOSD::Color_infoDoc::cast)

                .def("cast",
                     [](size_t data) {
                         return (NvOSD_Color_info *) data;
                     },
                     py::return_value_policy::reference,
                     pydsdoc::NvOSD::Color_infoDoc::cast);


        py::class_<NvOSD_RectParams>(m, "NvOSD_RectParams",
                                     pydsdoc::NvOSD::RectParamsDoc::descr)
                .def(py::init<>())
                .def_readwrite("left", &NvOSD_RectParams::left)
                .def_readwrite("top", &NvOSD_RectParams::top)
                .def_readwrite("width", &NvOSD_RectParams::width)
                .def_readwrite("height", &NvOSD_RectParams::height)
                .def_readwrite("border_width", &NvOSD_RectParams::border_width)
                .def_readwrite("border_color", &NvOSD_RectParams::border_color)
                .def_readwrite("has_bg_color", &NvOSD_RectParams::has_bg_color)
                .def_readwrite("reserved", &NvOSD_RectParams::reserved)
                .def_readwrite("bg_color", &NvOSD_RectParams::bg_color)
                .def_readwrite("has_color_info",
                               &NvOSD_RectParams::has_color_info)
                .def_readwrite("color_id", &NvOSD_RectParams::color_id)

                .def("cast",
                     [](void *data) {
                         return (NvOSD_RectParams *) data;
                     },
                     py::return_value_policy::reference,
                     pydsdoc::NvOSD::RectParamsDoc::cast)

                .def("cast",
                     [](size_t data) {
                         return (NvOSD_RectParams *) data;
                     },
                     py::return_value_policy::reference,
                     pydsdoc::NvOSD::RectParamsDoc::cast);


        py::class_<NvOSD_LineParams>(m, "NvOSD_LineParams",
                                     pydsdoc::NvOSD::LineParamsDoc::descr)
                .def(py::init<>())
                .def_readwrite("x1", &NvOSD_LineParams::x1)
                .def_readwrite("y1", &NvOSD_LineParams::y1)
                .def_readwrite("x2", &NvOSD_LineParams::x2)
                .def_readwrite("y2", &NvOSD_LineParams::y2)
                .def_readwrite("line_width", &NvOSD_LineParams::line_width)
                .def_readwrite("line_color", &NvOSD_LineParams::line_color)

                .def("cast",
                     [](void *data) {
                         return (NvOSD_LineParams *) data;
                     },
                     py::return_value_policy::reference,
                     pydsdoc::NvOSD::LineParamsDoc::cast)
                .def("cast",
                     [](size_t data) {
                         return (NvOSD_LineParams *) data;
                     },
                     py::return_value_policy::reference,
                     pydsdoc::NvOSD::LineParamsDoc::cast);


        py::class_<NvOSD_ArrowParams>(m, "NvOSD_ArrowParams",
                                      pydsdoc::NvOSD::NvOSD_ArrowParams::descr)
                .def(py::init<>())
                .def_readwrite("x1", &NvOSD_ArrowParams::x1)
                .def_readwrite("y1", &NvOSD_ArrowParams::y1)
                .def_readwrite("x2", &NvOSD_ArrowParams::x2)
                .def_readwrite("y2", &NvOSD_ArrowParams::y2)
                .def_readwrite("arrow_width", &NvOSD_ArrowParams::arrow_width)
                .def_readwrite("arrow_head", &NvOSD_ArrowParams::arrow_head)
                .def_readwrite("arrow_color", &NvOSD_ArrowParams::arrow_color)
                .def_readwrite("reserved", &NvOSD_ArrowParams::reserved)

                .def("cast",
                     [](void *data) {
                         return (NvOSD_ArrowParams *) data;
                     },
                     py::return_value_policy::reference,
                     pydsdoc::NvOSD::NvOSD_ArrowParams::cast)

                .def("cast",
                     [](size_t data) {
                         return (NvOSD_ArrowParams *) data;
                     },
                     py::return_value_policy::reference,
                     pydsdoc::NvOSD::NvOSD_ArrowParams::cast);


        py::class_<NvOSD_CircleParams>(m, "NvOSD_CircleParams",
                                       pydsdoc::NvOSD::NvOSD_CircleParams::descr)
                .def(py::init<>())
                .def_readwrite("xc", &NvOSD_CircleParams::xc)
                .def_readwrite("yc", &NvOSD_CircleParams::yc)
                .def_readwrite("radius", &NvOSD_CircleParams::radius)
                .def_readwrite("circle_color",
                               &NvOSD_CircleParams::circle_color)
                .def_readwrite("has_bg_color",
                               &NvOSD_CircleParams::has_bg_color)
                .def_readwrite("bg_color", &NvOSD_CircleParams::bg_color)
                .def_readwrite("reserved", &NvOSD_CircleParams::reserved)

                .def("cast",
                     [](void *data) {
                         return (NvOSD_CircleParams *) data;
                     },
                     py::return_value_policy::reference,
                     pydsdoc::NvOSD::NvOSD_CircleParams::cast)

                .def("cast",
                     [](size_t data) {
                         return (NvOSD_CircleParams *) data;
                     },
                     py::return_value_policy::reference,
                     pydsdoc::NvOSD::NvOSD_CircleParams::cast);


        /*Start of Bindings for nvll_osd_api.h*/
        py::class_<NvOSD_FrameTextParams>(m, "NvOSD_FrameTextParams",
                                          pydsdoc::NvOSD::NvOSD_FrameTextParams::descr)
                .def(py::init<>())
                .def_readwrite("buf_ptr", &NvOSD_FrameTextParams::buf_ptr)
                .def_readwrite("mode", &NvOSD_FrameTextParams::mode)
                .def_readwrite("num_strings",
                               &NvOSD_FrameTextParams::num_strings)
                .def_readwrite("text_params_list",
                               &NvOSD_FrameTextParams::text_params_list)

                .def("cast",
                     [](void *data) {
                         return (NvOSD_FrameTextParams *) data;
                     },
                     py::return_value_policy::reference,
                     pydsdoc::NvOSD::NvOSD_FrameTextParams::cast)

                .def("cast",
                     [](size_t data) {
                         return (NvOSD_FrameTextParams *) data;
                     },
                     py::return_value_policy::reference,
                     pydsdoc::NvOSD::NvOSD_FrameTextParams::cast);


        py::class_<NvOSD_FrameRectParams>(m, "NvOSD_FrameRectParams",
                                          pydsdoc::NvOSD::NvOSD_FrameRectParams::descr)
                .def(py::init<>())
                .def_readwrite("buf_ptr", &NvOSD_FrameRectParams::buf_ptr)
                .def_readwrite("mode", &NvOSD_FrameRectParams::mode)
                .def_readwrite("num_rects", &NvOSD_FrameRectParams::num_rects)
                .def_readwrite("rect_params_list",
                               &NvOSD_FrameRectParams::rect_params_list)

                .def("cast",
                     [](void *data) {
                         return (NvOSD_FrameRectParams *) data;
                     },
                     py::return_value_policy::reference,
                     pydsdoc::NvOSD::NvOSD_FrameRectParams::cast)

                .def("cast",
                     [](size_t data) {
                         return (NvOSD_FrameRectParams *) data;
                     },
                     py::return_value_policy::reference,
                     pydsdoc::NvOSD::NvOSD_FrameRectParams::cast);


        py::class_<NvOSD_FrameLineParams>(m, "NvOSD_FrameLineParams",
                                          pydsdoc::NvOSD::NvOSD_FrameLineParams::descr)
                .def(py::init<>())
                .def_readwrite("buf_ptr", &NvOSD_FrameLineParams::buf_ptr)
                .def_readwrite("mode", &NvOSD_FrameLineParams::mode)
                .def_readwrite("num_lines", &NvOSD_FrameLineParams::num_lines)
                .def_readwrite("line_params_list",
                               &NvOSD_FrameLineParams::line_params_list)

                .def("cast",
                     [](void *data) {
                         return (NvOSD_FrameLineParams *) data;
                     },
                     py::return_value_policy::reference,
                     pydsdoc::NvOSD::NvOSD_FrameLineParams::cast)

                .def("cast",
                     [](size_t data) {
                         return (NvOSD_FrameLineParams *) data;
                     },
                     py::return_value_policy::reference,
                     pydsdoc::NvOSD::NvOSD_FrameLineParams::cast);


        py::class_<NvOSD_FrameArrowParams>(m, "NvOSD_FrameArrowParams",
                                           pydsdoc::NvOSD::NvOSD_FrameArrowParams::descr)
                .def(py::init<>())
                .def_readwrite("buf_ptr", &NvOSD_FrameArrowParams::buf_ptr)
                .def_readwrite("mode", &NvOSD_FrameArrowParams::mode)
                .def_readwrite("num_arrows",
                               &NvOSD_FrameArrowParams::num_arrows)
                .def_readwrite("arrow_params_list",
                               &NvOSD_FrameArrowParams::arrow_params_list)

                .def("cast",
                     [](void *data) {
                         return (NvOSD_FrameArrowParams *) data;
                     },
                     py::return_value_policy::reference,
                     pydsdoc::NvOSD::NvOSD_FrameArrowParams::cast)

                .def("cast",
                     [](size_t data) {
                         return (NvOSD_FrameArrowParams *) data;
                     },
                     py::return_value_policy::reference,
                     pydsdoc::NvOSD::NvOSD_FrameArrowParams::cast);


        py::class_<NvOSD_FrameCircleParams>(m, "NvOSD_FrameCircleParams",
                                            pydsdoc::NvOSD::NvOSD_FrameCircleParams::descr)
                .def(py::init<>())
                .def_readwrite("buf_ptr", &NvOSD_FrameCircleParams::buf_ptr)
                .def_readwrite("mode", &NvOSD_FrameCircleParams::mode)
                .def_readwrite("num_circles",
                               &NvOSD_FrameCircleParams::num_circles)
                .def_readwrite("circle_params_list",
                               &NvOSD_FrameCircleParams::circle_params_list)

                .def("cast",
                     [](void *data) {
                         return (NvOSD_FrameCircleParams *) data;
                     },
                     py::return_value_policy::reference,
                     pydsdoc::NvOSD::NvOSD_FrameCircleParams::cast)

                .def("cast",
                     [](size_t data) {
                         return (NvOSD_FrameCircleParams *) data;
                     },
                     py::return_value_policy::reference,
                     pydsdoc::NvOSD::NvOSD_FrameCircleParams::cast);

         py::class_<NvOSD_MaskParams>(m, "NvOSD_MaskParams",
                                     pydsdoc::NvOSD::NvOSD_MaskParams::descr)
                .def(py::init<>())
                .def_readwrite("data", &NvOSD_MaskParams::data)
                .def_readwrite("size", &NvOSD_MaskParams::size)
                .def_readwrite("threshold", &NvOSD_MaskParams::threshold)
                .def_readwrite("width", &NvOSD_MaskParams::width)
                .def_readwrite("height", &NvOSD_MaskParams::height)

                .def("get_mask_array", 
                     [](NvOSD_MaskParams &self) -> py::array {
                         auto dtype = py::dtype(py::format_descriptor<float>::format());
                         return py::array(dtype, {self.size / sizeof(float)}, {sizeof(float)}, self.data, py::cast(self.data));
                    },
                     py::return_value_policy::reference,
                     pydsdoc::NvOSD::NvOSD_MaskParams::get_mask_array)
                    
                .def("cast",
                     [](void *data) {
                         return (NvOSD_MaskParams *) data;
                     },
                     py::return_value_policy::reference,
                     pydsdoc::NvOSD::NvOSD_MaskParams::cast)

                .def("cast",
                     [](size_t data) {
                         return (NvOSD_MaskParams *) data;
                     },
                     py::return_value_policy::reference,
                     pydsdoc::NvOSD::NvOSD_MaskParams::cast);
    }

}
