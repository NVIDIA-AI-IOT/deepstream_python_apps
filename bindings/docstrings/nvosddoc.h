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
 
#pragma once

namespace pydsdoc
{    
    namespace NvOSD
    {

        namespace NvOSD_Arrow_Head_Direction
        {
            constexpr const char* descr = R"pyds(*Enumerator*. Lists arrow head positions.)pyds";
            constexpr const char* START_HEAD = R"pyds(Arrow head only at start = 0.)pyds";
            constexpr const char* END_HEAD = R"pyds(Arrow head only at end = 1.)pyds";
            constexpr const char* BOTH_HEAD = R"pyds(Arrow head at both sides = 2.)pyds";
        }

        namespace NvBbox_Coords
        {
            constexpr const char* descr = R"pyds(
                Holds unclipped bounding box coordinates of the object.

                :ivar left: *float*, Holds the box's left coordinate in pixels.
                :ivar top: *float*, Holds the box's top coordinate in pixels.
                :ivar width: *float*, Holds the box's width in pixels.
                :ivar height: *float*, Holds the box's height in pixels.)pyds";

            constexpr const char* cast=R"pyds(cast given object/data to :class:`NvBbox_Coords`, call pyds.NvBbox_Coords.cast(data))pyds";
        }

        namespace NvOSD_FrameTextParams
        {
            constexpr const char* descr = R"pyds(
                Holds information about the text in a frame.

                :ivar buf_ptr: :class:`NvBufSurfaceParams`, Holds the buffer containing frame.
                :ivar mode: :class:`NvOSD_Mode`, Holds OSD Mode to be used for processing.
                :ivar num_strings: *int*, Holds number of strings.
                :ivar text_params_list: list of :class:`NvOSD_TextParams`, Holds the strings' text parameters.)pyds";

            constexpr const char* cast=R"pyds(cast given object/data to :class:`NvOSD_FrameTextParams`, call pyds.NvOSD_FrameTextParams.cast(data))pyds";
        }

        namespace NvOSD_FrameRectParams
        {
            constexpr const char* descr = R"pyds(
                Holds information about the rectangles in a frame.

                :ivar buf_ptr: :class:`NvBufSurfaceParams`, Holds the buffer containing frame.
                :ivar mode: :class:`NvOSD_Mode`, Holds OSD Mode to be used for processing.
                :ivar num_rects: *int*, Holds number of rectangles.
                :ivar rect_params_list: list of :class:`NvOSD_RectParams`, Holds the rectangles' parameters.)pyds";

            constexpr const char* cast=R"pyds(cast given object/data to :class:`NvOSD_FrameRectParams`, call pyds.NvOSD_FrameRectParams.cast(data))pyds";
        }

        namespace NvOSD_FrameLineParams
        {
            constexpr const char* descr = R"pyds(
                Holds information about the lines in a frame.
                
                :ivar buf_ptr: :class:`NvBufSurfaceParams`, Holds the buffer containing frame.
                :ivar mode: :class:`NvOSD_Mode`, Holds OSD Mode to be used for processing.
                :ivar num_lines: *int*, Holds number of lines.
                :ivar line_params_list: list of :class:`NvOSD_LineParams`, Holds the lines' parameters.)pyds";

            constexpr const char* cast=R"pyds(cast given object/data to :class:`NvOSD_FrameLineParams`, call pyds.NvOSD_FrameLineParams.cast(data))pyds";
        }

        namespace NvOSD_FrameArrowParams
        {
            constexpr const char* descr = R"pyds(
                Holds information about the arrows in a frame.

                :ivar buf_ptr: :class:`NvBufSurfaceParams`, Holds the buffer containing frame.
                :ivar mode: :class:`NvOSD_Mode`, Holds OSD Mode to be used for processing.
                :ivar num_arrows: *int*, Holds number of arrows.
                :ivar arrow_params_list: list of :class:`NvOSD_ArrowParams`, Holds the arrows' parameters.)pyds";

            constexpr const char* cast=R"pyds(cast given object/data to :class:`NvOSD_FrameArrowParams`, call pyds.NvOSD_FrameArrowParams.cast(data))pyds";
        }

        namespace NvOSD_FrameCircleParams
        {
            constexpr const char* descr = R"pyds(
                Holds information about the circles in a frame.
                
                :ivar buf_ptr: :class:`NvBufSurfaceParams`, Holds the buffer containing frame.
                :ivar mode: :class:`NvOSD_Mode`, Holds OSD Mode to be used for processing.
                :ivar num_circles: *int*, Holds number of circles.
                :ivar circle_params_list: list of :class:`NvOSD_CircleParams`, Holds the circles' parameters.)pyds";

            constexpr const char* cast=R"pyds(cast given object/data to :class:`NvOSD_FrameCircleParams`, call pyds.NvOSD_FrameCircleParams.cast(data))pyds";
        }

        namespace ColorParamsDoc
        {
            constexpr const char* descr = R"pyds(
                Holds the color parameters of the box or text to be overlayed. See :class:`NvOSD_TextParams` docs for example usage.
                
                :ivar red: *float*, Holds red component of color. Value must be in the range 0-1.
                :ivar green: *float*, Holds green component of color. Value must be in the range 0-1.
                :ivar blue: *float*, Holds blue component of color. Value must be in the range 0-1.
                :ivar alpha: *float*, Holds alpha component of color. Value must be in the range 0-1.)pyds";

            constexpr const char* cast=R"pyds(cast given object/data to :class:`NvOSD_ColorParams`, call pyds.NvOSD_ColorParams.cast(data))pyds";

            constexpr const char* set=R"pyds(
                Sets the color values.

                :arg red: Value for red component (must be in range 0.-1.)
                :arg green: Value for green component (must be in range 0.-1.)
                :arg blue: Value for blue component (must be in range 0.-1.)
                :arg alpha: Value for alpha component (must be in range 0.-1.))pyds";
        }

        namespace NvOSD_Mode
        {
            constexpr const char* descr = R"pyds(*Enumerator*. List modes used to overlay boxes and text.)pyds";
            constexpr const char* MODE_CPU = R"pyds(Selects CPU for OSD processing. Works with RGBA data only.)pyds";
            constexpr const char* MODE_GPU = R"pyds(Selects GPU for OSD processing. Yet to be implemented.)pyds";
            constexpr const char* MODE_NONE = R"pyds(Invalid mode. Instead GPU mode will be used.)pyds";
        }	

        namespace  NvOSD_ArrowParams
        {
            constexpr const char* descr = R"pyds(
                Holds arrow parameters to be overlaid.
                
                :ivar x1: *int*, Holds start horizontal coordinate in pixels.
                :ivar y1: *int*, Holds start vertical coordinate in pixels.
                :ivar x2: *int*, Holds end horizontal coordinate in pixels.
                :ivar y2: *int*, Holds end vertical coordinate in pixels.
                :ivar arrow_width: *int*, Holds the arrow shaft width in pixels.
                :ivar arrow_color: :class:`NvOSD_ColorParams`, Holds the color parameters of the arrow box.
                :ivar arrow_head: :class:`NvOSD_Arrow_Head_Direction`, Holds the arrowhead position.
                :ivar reserved: *int*, reserved field for future usage. For internal purpose only.)pyds";

            constexpr const char* cast=R"pyds(cast given object/data to :class:`NvOSD_ArrowParams`, call pyds.NvOSD_ArrowParams.cast(data))pyds";
        }

        namespace NvOSD_CircleParams
        {
            constexpr const char* descr = R"pyds(
                Holds the circle parameters to be overlayed.
                
                :ivar xc: *int*, Holds start horizontal coordinate in pixels.
                :ivar yc: *int*, Holds start vertical coordinate in pixels.
                :ivar radius: *int*, Holds radius of circle in pixels.
                :ivar circle_color: :class:`NvOSD_ColorParams`, Holds color params of the circle.
                :ivar has_bg_color: *int*, Holds boolean value indicating whethercircle has background color.
                :ivar bg_color: :class:`NvOSD_ColorParams`, Holds the circle's background color.
                :ivar reserved: *int*, Reserved field for future usage. For internal purpose only.)pyds";

            constexpr const char* cast=R"pyds(cast given object/data to :class:`NvOSD_CircleParams`, call pyds.NvOSD_CircleParams.cast(data))pyds";
        }

        namespace FontParamsDoc
        {
            constexpr const char* descr = R"pyds(
                Holds the font parameters of the text to be overlayed. See :class:`NvOSD_TextParams` docs for example usage.
                
                :ivar fontname: *str*, Holds the font name. The list of supported fonts can be obtained by running fc-list command
                :ivar fontsize: *int*, Holds size of the font.
                :ivar fontcolor: :class:`NvOSD_ColorParams`, Holds the font color.)pyds";

            constexpr const char* cast=R"pyds(cast given object/data to :class:`NvOSD_FontParams`, call pyds.NvOSD_FontParams.cast(data))pyds";
        }

        namespace TextParamsDoc
        {
            constexpr const char* descr = R"pyds(
                Holds the parameters of the text to be overlaid.

                :ivar display_text: *str*, Holds the text to be overlaid.
                :ivar x_offset: *int*, Holds horizontal offset w.r.t top left pixel of the frame. 
                :ivar y_offset: *int*, Holds vertical offset w.r.t top left pixel of the frame.  
                :ivar font_params: :class:`NvOSD_FontParams`, Holds the font parameters of the text to be overlaid.   
                :ivar set_bg_clr: *int*, Boolean to indicate text has background color.  
                :ivar text_bg_clr: :class:`NvOSD_ColorParams`, Holds the text's background color, if specified.

                Example usage:
                ::

                    display_meta=pyds.nvds_acquire_display_meta_from_pool(batch_meta) #Retrieve NvDsDisplayMeta object from given NvDsBatchMeta object. See NvDsMeta docs for more details.
                    display_meta.num_labels = 1
                    py_nvosd_text_params = display_meta.text_params[0] #Retrieve NvOSD_TextParams object from list in display meta. 
                    # Setting display text to be shown on screen
                    # Note that the pyds module allocates a buffer for the string, and the
                    # memory will not be claimed by the garbage collector.
                    # Reading the display_text field here will return the C address of the
                    # allocated string. Use pyds.get_string() to get the string content.
                    py_nvosd_text_params.display_text = "Frame Number={} Number of Objects={} Vehicle_count={} Person_count={}".format(frame_number, num_rects, obj_counter[PGIE_CLASS_ID_VEHICLE], obj_counter[PGIE_CLASS_ID_PERSON])

                    # Now set the offsets where the string should appear
                    py_nvosd_text_params.x_offset = 10
                    py_nvosd_text_params.y_offset = 12

                    # Font , font-color and font-size
                    py_nvosd_text_params.font_params.font_name = "Serif" #Set attributes of our NvOSD_TextParams object's NvOSD_FontParams member 
                    py_nvosd_text_params.font_params.font_size = 10
                    # set(red, green, blue, alpha); set to White
                    py_nvosd_text_params.font_params.font_color.set(1.0, 1.0, 1.0, 1.0) #See NvOSD_ColorParams for more details.

                    # Text background color
                    py_nvosd_text_params.set_bg_clr = 1 #Set boolean indicating that text has bg color to true. 
                    # set(red, green, blue, alpha); set to Black
                    py_nvosd_text_params.text_bg_clr.set(0.0, 0.0, 0.0, 1.0)
                    # Using pyds.get_string() to get display_text as string
                    print(pyds.get_string(py_nvosd_text_params.display_text))
                    pyds.nvds_add_display_meta_to_frame(frame_meta, display_meta) #Add display meta to frame after setting text params attributes.)pyds";

                constexpr const char* cast=R"pyds(cast given object/data to :class:`NvOSD_TextParams`, call pyds.NvOSD_TextParams.cast(data))pyds";
        }

        //TODO, doxygen comments missing
        namespace Color_infoDoc
        {
            constexpr const char* descr=R"pyds(
                NvOSD_Color_info.

                :ivar id: id
                :ivar color: color)pyds";

            constexpr const char* cast=R"pyds(cast given object/data to :class:`NvOSD_Color_info`, call pyds.NvOSD_Color_info.cast(data))pyds";
        }

        namespace RectParamsDoc
        {
            constexpr const char* descr = R"pyds(
                Holds the box parameters of the box to be overlaid.

                :ivar left: *float*, Holds left coordinate of the box in pixels.
                :ivar top: *float*, Holds top coordinate of the box in pixels.
                :ivar width: *float*, Holds width of the box in pixels.
                :ivar height: *float*, Holds height of the box in pixels.
                :ivar border_width: *int*, Holds border_width of the box in pixels.
                :ivar border_color: :class:`NvOSD_ColorParams`, Holds color params of the border of the box. 
                :ivar has_bg_color: *int*, Holds boolean value indicating whether box has background color.  
                :ivar bg_color: :class:`NvOSD_ColorParams`, Holds background color of the box.
                :ivar has_color_info: *int*, color_info
                :ivar color_id: *int*, id of the color
                :ivar reserved: *int*, Reserved field for future usage. For internal purpose only.)pyds";

            constexpr const char* cast=R"pyds(cast given object/data to :class:`NvOSD_RectParams`, call pyds.NvOSD_RectParams.cast(data))pyds";
        }

        namespace LineParamsDoc
        {
            constexpr const char* descr = R"pyds(
                Holds the box parameters of the line to be overlaid.

                :ivar x1: *int*, Holds left coordinate of the box in pixels.
                :ivar y1: *int*, Holds top coordinate of the box in pixels.
                :ivar x2: *int*, Holds width of the box in pixels.
                :ivar y2: *int*, Holds height of the box in pixels.
                :ivar line_width: *int*, Holds border_width of the box in pixels.
                :ivar line_color: :class:`NvOSD_ColorParams`, Holds color params of the border of the box.)pyds";

            constexpr const char* cast=R"pyds(cast given object/data to :class:`NvOSD_LineParams`, call pyds.NvOSD_LineParams.cast(data))pyds";
        }

        namespace NvOSD_MaskParams
        {
            constexpr const char* descr = R"pyds(
                Holds the mask parameters of the segment to be overlayed.
                
                :ivar data: *float**, Mask buffer.
                :ivar size: *int*, Size of the mask buffer in bytes.
                :ivar threshold: *int*, Threshold for binarization.
                :ivar height: *int*, Mask height.
                :ivar width: *int*, Mask width.)pyds";

            constexpr const char* get_mask_array=R"pyds(Retrieve mask data as numpy array)pyds";
            constexpr const char* cast=R"pyds(cast given object/data to :class:`NvOSD_MaskParams`, call pyds.NvOSD_MaskParams.cast(data))pyds";
        }
    }
}