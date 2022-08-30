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
// This file contains all Dims docstrings, since these are typically too long to keep in the binding code.
#pragma once


namespace pydsdoc
{
    namespace trackerdoc
    {
        namespace NvDsPastFrameObjDoc //missing doxygen comments
        {
            constexpr const char* descr = R"pyds(
                NvDsPastFrameObj

                :ivar frameNum: *int*, frameNum
                :ivar tBbox: :class:`NvOSD_RectParams`, tBbox
                :ivar confidence: *float*, confidence
                :ivar age: *int*, age

                Example usage:
                ::

                    l_user=batch_meta.batch_user_meta_list #Retrieve glist of NvDsUserMeta objects from given NvDsBatchMeta object
                    while l_user is not None:
                        try:
                            # Note that l_user.data needs a cast to pyds.NvDsUserMeta
                            # The casting is done by pyds.NvDsUserMeta.cast()
                            # The casting also keeps ownership of the underlying memory
                            # in the C code, so the Python garbage collector will leave
                            # it alone
                            user_meta=pyds.NvDsUserMeta.cast(l_user.data) 
                        except StopIteration:
                            break
                        if(user_meta and user_meta.base_meta.meta_type==pyds.NvDsMetaType.NVDS_TRACKER_PAST_FRAME_META): #Make sure metatype is correct
                            try:
                                # Note that user_meta.user_meta_data needs a cast to pyds.NvDsPastFrameObjBatch
                                # The casting is done by pyds.NvDsPastFrameObjBatch.cast()
                                # The casting also keeps ownership of the underlying memory
                                # in the C code, so the Python garbage collector will leave
                                # it alone
                                pPastFrameObjBatch = pyds.NvDsPastFrameObjBatch.cast(user_meta.user_meta_data) #See NvDsPastFrameObjBatch for details
                            except StopIteration:
                                break
                            for trackobj in pyds.NvDsPastFrameObjBatch.list(pPastFrameObjBatch): #Iterate through list of NvDsPastFrameObjStream objects
                                #Access NvDsPastFrameObjStream attributes
                                print("streamId=",trackobj.streamID)
                                print("surfaceStreamID=",trackobj.surfaceStreamID)
                                for pastframeobj in pyds.NvDsPastFrameObjStream.list(trackobj): #Iterate through list of NvDsFrameObjList objects
                                #Access NvDsPastFrameObjList attributes
                                print("numobj=",pastframeobj.numObj)
                                print("uniqueId=",pastframeobj.uniqueId)
                                print("classId=",pastframeobj.classId)
                                print("objLabel=",pastframeobj.objLabel)
                                for objlist in pyds.NvDsPastFrameObjList.list(pastframeobj): #Iterate through list of NvDsFrameObj objects
                                    #Access NvDsPastFrameObj attributes
                                    print('frameNum:', objlist.frameNum)
                                    print('tBbox.left:', objlist.tBbox.left)
                                    print('tBbox.width:', objlist.tBbox.width)
                                    print('tBbox.top:', objlist.tBbox.top)
                                    print('tBbox.right:', objlist.tBbox.height)
                                    print('confidence:', objlist.confidence)
                                    print('age:', objlist.age)
                        try:
                            l_user=l_user.next
                        except StopIteration:
                            break)pyds";

            constexpr const char* cast=R"pyds(cast given object/data to :class:`NvDsPastFrameObj`, call pyds.NvDsPastFrameObj.cast(data))pyds";
        }

        namespace NvDsPastFrameObjListDoc
        {
            constexpr const char* descr = R"pyds(
                One object in several past frames. See :class:`NvDsPastFrameObj` for example usage.

                :ivar numObj: *int*, Number of frames this object appreared in the past.
                :ivar uniqueId: *int*, Object tracking id.
                :ivar classID: *int*, Object class id.
                :ivar objLabel: An array of the string describing the object class.)pyds";

            constexpr const char* list=R"pyds(Retrieve :class:`NvDsPastFrameObjList` object as list of :class:`NvDsPastFrameObj`. Contains past frame info of this object.)pyds";
            constexpr const char* cast=R"pyds(cast given object/data to :class:`NvDsPastFrameObjList`, call pyds.NvDsPastFrameObjList.cast(data))pyds";
        }

        namespace NvDsPastFrameObjStreamDoc
        {
            constexpr const char* descr = R"pyds(
                List of objects in each stream. See :class:`NvDsPastFrameObj` for example usage.

                :ivar streamID: *int*, Stream id the same as frame_meta->pad_index.
                :ivar surfaceStreamID: *int*, Stream id used inside tracker plugin.
                :ivar numAllocated: *int*, Maximum number of objects allocated.
                :ivar numFilled: *int*, Number of objects in this frame.)pyds";

            constexpr const char* list=R"pyds(Retrieve :class:`NvDsPastFrameObjStream` object as list of :class:`NvDsPastFrameObjList`. Contains objects inside this stream.)pyds";
            constexpr const char* cast=R"pyds(cast given object/data to :class:`NvDsPastFrameObjStream`, call pyds.NvDsPastFrameObjStream.cast(data))pyds";
        }
        
        namespace NvDsPastFrameObjBatchDoc
        {
            constexpr const char* descr = R"pyds(
                Batch of lists of buffered objects. See :class:`NvDsPastFrameObj` for example usage.
                
                :ivar numAllocated: *int*, Number of blocks allocated for the list.
                :ivar numFilled: *int*, Number of filled blocks in the list.
                )pyds";

            constexpr const char* list=R"pyds(Retrieve :class:`NvDsPastFrameObjBatch` object as list of :class:`NvDsPastFrameObjStream`. Contains stream lists.)pyds";
            constexpr const char* cast=R"pyds(cast given object/data to :class:`NvDsPastFrameObjBatch`, call pyds.NvDsPastFrameObjBatch.cast(data))pyds";
        }

    }

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
            constexpr const char* MODE_HW = R"pyds(Selects NV HW engine for rectangle draw and mask. This mode works with both YUV and RGB data. It does not consider alpha parameter. Not applicable for drawing text.)pyds";
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
    }
    

    namespace nvmeta
    {
        namespace MetaTypeDoc
        {
            constexpr const char* descr = R"pyds(
                *Enumerator*. Specifies the type of meta data. 
                NVIDIA defined NvDsMetaType will be present in the range from NVDS_BATCH_META to NVDS_START_USER_META.
                User can add its own metadata type NVDS_START_USER_META onwards.)pyds";

            constexpr const char* NVDS_INVALID_META=R"pyds(NVDS_INVALID_META)pyds"; 
            constexpr const char* NVDS_BATCH_META=R"pyds(metadata type to be set for formed batch)pyds"; 
            constexpr const char* NVDS_FRAME_META=R"pyds(metadata type to be set for frame)pyds"; 
            constexpr const char* NVDS_OBJ_META=R"pyds(metadata type to be set for detected object )pyds"; 
            constexpr const char* NVDS_DISPLAY_META=R"pyds(metadata type to be set for display)pyds"; 
            constexpr const char* NVDS_CLASSIFIER_META=R"pyds(metadata type to be set for object classifier)pyds"; 
            constexpr const char* NVDS_LABEL_INFO_META=R"pyds(metadata type to be set for given label of classifier)pyds"; 
            constexpr const char* NVDS_USER_META=R"pyds(used for internal purpose)pyds"; 
            constexpr const char* NVDS_PAYLOAD_META=R"pyds(metadata type to be set for payload generated by msg converter)pyds"; 
            constexpr const char* NVDS_EVENT_MSG_META=R"pyds(metadata type to be set for payload generated by msg broker)pyds"; 
            constexpr const char* NVDS_OPTICAL_FLOW_META=R"pyds(metadata type to be set for optical flow)pyds";
            constexpr const char* NVDS_LATENCY_MEASUREMENT_META=R"pyds(metadata type to be set for latency measurement)pyds";
            constexpr const char* NVDSINFER_TENSOR_OUTPUT_META=R"pyds(metadata type of raw inference output attached by gst-nvinfer. Refer :class:`NvDsInferTensorMeta` for details.)pyds";
            constexpr const char* NVDSINFER_SEGMENTATION_META=R"pyds(metadata type of segmentation model output attached by gst-nvinfer. Refer :class:`NvDsInferSegmentationMeta` for details.)pyds";
            constexpr const char* NVDS_CROP_IMAGE_META=R"pyds(Specifies metadata type for JPEG-encoded object crops.See the deepstream-image-meta-test app for details.)pyds";
            constexpr const char* NVDS_TRACKER_PAST_FRAME_META=R"pyds(metadata type to be set for tracking previous frames)pyds";
            constexpr const char* NVDS_AUDIO_BATCH_META=R"pyds(Specifies metadata type for formed audio batch.)pyds";
            constexpr const char* NVDS_AUDIO_FRAME_META=R"pyds(Specifies metadata type for audio frame.)pyds";
            constexpr const char* NVDS_RESERVED_META=R"pyds(Reserved field)pyds";
            constexpr const char* NVDS_GST_CUSTOM_META=R"pyds(metadata type to be set for metadata attached by nvidia gstreamer plugins before nvstreammux gstreamer plugin. It is set as user metadata inside :class:`NvDsFrameMeta`. NVIDIA specific gst meta are in the range from NVDS_GST_CUSTOM_META to NVDS_GST_CUSTOM_META + 4096)pyds";
            constexpr const char* NVDS_START_USER_META=R"pyds(NVDS_START_USER_META)pyds"; 
            constexpr const char* NVDS_FORCE32_META=R"pyds(NVDS_FORCE32_META)pyds";
        }    

        namespace NvDsComp_BboxInfoDoc
        {
            constexpr const char* descr = R"pyds(
                Holds unclipped positional bounding box coordinates of the object processed by the component.
                
                :ivar org_bbox_coords: :class:`NvBbox_Coords`, org_bbox_coords)pyds";

            constexpr const char* cast=R"pyds(cast given object/data to :class:`NvDsComp_BboxInfo`, call pyds.NvDsComp_BboxInfo.cast(data))pyds";
        }

        namespace GstNvDsMetaTypeDoc
        {
            constexpr const char* descr = R"pyds(
                *Enumerator*. Specifies the type of meta data. 
                NVIDIA defined :class:`GstNvDsMetaType` values are in the range from NVDS_BATCH_GST_META to NVDS_START_USER_META.)pyds";

            constexpr const char* NVDS_GST_INVALID_META=R"pyds(NVDS_GST_INVALID_META)pyds"; 
            constexpr const char* NVDS_BATCH_GST_META=R"pyds(Specifies information of a formed batch.)pyds"; 
            constexpr const char* NVDS_DECODER_GST_META=R"pyds(NVDS_DECODER_GST_META)pyds"; 
            constexpr const char* NVDS_DEWARPER_GST_META=R"pyds(Specifies information of dewarped surfaces.)pyds"; 
            constexpr const char* NVDS_RESERVED_GST_META=R"pyds(NVDS_RESERVED_GST_META)pyds"; 
            constexpr const char* NVDS_GST_META_FORCE32=R"pyds(Specifies the first value that may be assigned to a user-defined type.)pyds"; 
            
        }

        namespace NvDsMetaDoc  
        { 
            constexpr const char* descr = R"pyds(
                Holds DeepStream meta data.

                :ivar meta: *GstMeta* object.
                :ivar meta_data: Metadata object. Must be cast to another structure based on :py:attr:`meta_type`.
                :ivar user_data: User-specific data
                :ivar meta_type: Type of metadata, one of values of :class:`GstNvDsMetaType`)pyds";

            constexpr const char* cast=R"pyds(cast given object/data to :class:`NvDsMeta`, call pyds.NvDsMeta.cast(data))pyds";
        }

        namespace MetaPoolDoc
        {
            constexpr const char* descr = R"pyds(
                Holds information about given metadata pool.

                :ivar meta_type: :class:`NvDsMetaType`, type of the pool. Used for internal purpose.
                :ivar max_elements_in_pool: *int*, max elements in the pool. Used for internal purpose.
                :ivar element_size: *int*, size of an element in the given pool. Used for internal purpose.
                :ivar num_empty_elements: *int*, number of empty elements. Used for internal purpose.
                :ivar num_full_elements: *int*, number of filled elements. These many elemnts are in use.
                :ivar empty_list: :class:`NvDsMetaList`, List containing empty elements.
                :ivar full_list: :class:`NvDsMetaList`, List containing full elements.)pyds";

            constexpr const char* cast=R"pyds(cast given object/data to :class:`NvDsMetaPool`, call pyds.NvDsMetaPool.cast(data))pyds";
        }

        namespace BaseMetaDoc
        {
            constexpr const char* descr = R"pyds(
                Holds information about base metadata of given metadata type.

                :ivar batch_meta: batch_meta
                :ivar meta_type: Metadata type of the given element.
                :ivar uContext: user context)pyds";

            constexpr const char* cast=R"pyds(cast given object/data to :class:`NvDsBaseMeta`, call pyds.NvDsBaseMeta.cast(data))pyds";
        }

        namespace BatchMetaDoc
        {
            constexpr const char* descr = R"pyds(
                Holds information a formed batched containing the frames from different sources.

                NOTE: Both Video and Audio metadata uses the same :class:`NvDsBatchMeta` type.

                NOTE: Audio batch metadata is formed within nvinferaudio plugin and will not be corresponding to any one buffer output from nvinferaudio.
                The :class:`NvDsBatchMeta` for audio is attached to the last input buffer when the audio batch buffering reach configurable threshold (audio frame length)
                and this is when inference output is available.

                :ivar base_meta: :class:`NvDsBaseMeta`, base_meta
                :ivar max_frames_in_batch: *int*, maximum number of frames those can be present the batch. 
                :ivar num_frames_in_batch: *int*, Number of frames present in the current batch.
                :ivar frame_meta_pool: :class:`NvDsMetaPool`, pool of type :class:`NvDsFrameMeta`. 
                :ivar obj_meta_pool: :class:`NvDsMetaPool`, pool of type :class:`NvDsObjMeta`.
                :ivar classifier_meta_pool: :class:`NvDsMetaPool`, pool of type :class:`NvDsClassifierMeta`. 
                :ivar display_meta_pool: :class:`NvDsMetaPool`, A pool of type :class:`NvDsDisplayMeta`.
                :ivar user_meta_pool: :class:`NvDsMetaPool`, A pool of type :class:`NvDsUserMeta`.     
                :ivar label_info_meta_pool: :class:`NvDsMetaPool`, A pool of type :class:`NvDsLabelInfo`. 
                :ivar frame_meta_list: A list of items of type :class:`NvDsFrameMeta` in use in the current batch.
                :ivar batch_user_meta_list: A list of items of type :class:`NvDsUserMeta` in use in the current batch.
                :ivar meta_mutex: *GRecMutex*, lock to be taken before accessing metadata to avoid simultaneous update of same metadata by multiple components.
                :ivar misc_batch_info: *list of int*, For additional user specific batch info.
                :ivar reserved: *int*, Reserved for internal use.

                Example usage:
                ::

                    # Retrieve batch metadata from the gst_buffer
                    # Note that pyds.gst_buffer_get_nvds_batch_meta() expects the
                    # C address of gst_buffer as input, which is obtained with hash(gst_buffer)
                    batch_meta = pyds.gst_buffer_get_nvds_batch_meta(hash(gst_buffer))
                    l_frame = batch_meta.frame_meta_list #Get list containing NvDsFrameMeta objects from retrieved NvDsBatchMeta)pyds";

            constexpr const char* cast=R"pyds(cast given object/data to :class:`NvDsBatchMeta`, call pyds.NvDsBatchMeta.cast(data))pyds";
        }

        namespace FrameMetaDoc
        {
            constexpr const char* descr = R"pyds(
                Holds metadata for a frame in a batch.

                :ivar base_meta: :class:`NvDsBaseMeta`, Base metadata for frame.
                :ivar pad_index: *int*, Pad or port index of stream muxer component for the frame in the batch.
                :ivar batch_id: *int*, Location of the frame in the batch. :class:`NvBufSurfaceParams` for the frame will be at index batch_id in the surfaceList array of :class:`NvBufSurface`.
                :ivar frame_num: *int*, Current frame number of the source.
                :ivar buf_pts: *int*, Holds the presentation timestamp (PTS) of the frame.
                :ivar ntp_timestamp: *int*, Holds the ntp (network time protocol) timestamp.
                :ivar source_id: *int*, Source_id of the frame in the batch e.g. camera_id. It need not be in sequential order.
                :ivar num_surfaces_per_frame: *int*, Number of surfaces present in this frame. This is required in case multiple surfaces per frame.
                :ivar source_frame_width: *int*, Holds the width of the frame at input to Gst-streammux.
                :ivar source_frame_height: *int*, Holds the height of the frame at input to Gst-streammux.
                :ivar surface_type: *int*, Surface type of sub frame. This is required in case multiple surfaces per frame.
                :ivar surface_index: *int*, Surface index of sub frame. This is required in case multiple surfaces per frame.
                :ivar num_obj_meta: *int*, Number of object meta elements attached to the current frame.
                :ivar bInferDone: *int*, Boolean indicating whether inference is performed on given frame.
                :ivar obj_meta_list: List of objects of type :class:`NvDsObjectMeta` in use for the given frame.
                :ivar display_meta_list: List of objects of type :class:`NvDsDisplayMeta` in use for the given frame.
                :ivar frame_user_meta_list: List of objects of type :class:`NvDsUserMeta` in use for the given frame.
                :ivar misc_frame_info: *list of int*, For additional user specific batch info.
                :ivar reserved: *int*, Reserved for internal use.

                Example usage:
                ::

                    batch_meta = pyds.gst_buffer_get_nvds_batch_meta(hash(gst_buffer)) #Retrieve batch metadata from gst_buffer
                    l_frame = batch_meta.frame_meta_list
                    while l_frame is not None:
                        try:
                            frame_meta = pyds.NvDsFrameMeta.cast(l_frame.data) #Must cast data in frame_meta_list to NvDsFrameMeta object
                        except StopIteration:
                            break

                        frame_number=frame_meta.frame_num #Retrieve current frame number from NvDsFrameMeta object
                        num_rects = frame_meta.num_obj_meta #Retrieve number of objects in frame from NvDsFrameMeta object
                        l_obj=frame_meta.obj_meta_list #Retrieve list of NvDsObjectMeta objects in frame from NvDsFrameMeta object)pyds";

            constexpr const char* cast=R"pyds(cast given object/data to :class:`NvDsFrameMeta`, call pyds.NvDsFrameMeta.cast(data))pyds";
        }

        namespace ObjectMetaDoc
        {
            constexpr const char* descr = R"pyds(
                Holds information of object metadata in the frame.

                :ivar base_meta: :class:`NvDsBaseMeta`, base_meta
                :ivar parent: the parent :class:`NvDsObjectMeta` object. Set to None if parent is not present
                :ivar unique_component_id: *int*, unique component id that attaches NvDsObjectMeta metadata
                :ivar class_id: *int*, Index of the object class infered by the primary detector/classifier
                :ivar object_id: *int*, Unique ID for tracking the object. @ref UNTRACKED_OBJECT_ID indicates the object has not been tracked
                :ivar confidence: *float*, Holds a confidence value for the object, set by the inference component. 
                    Confidence will be set to -0.1, if "Group Rectangles" mode of clustering is chosen since the algorithm does not preserve confidence values.
                    Also, for objects found by tracker and not inference component, confidence will be set to -0.1
                :ivar detector_bbox_info: :class:`NvDsComp_BboxInfo`, Holds a structure containing bounding box parameters of the object when detected by detector
                :ivar tracker_bbox_info: :class:`NvDsComp_BboxInfo`, Holds a structure containing bounding box coordinates of the object when processed by tracker
                :ivar tracker_confidence: *float*, Holds a confidence value for the object set by nvdcf_tracker. tracker_confidence will be set to -0.1 for KLT and IOU tracker
                :ivar rect_params: :class:`NvOSD_RectParams`, Structure containing the positional parameters of the object in the frame.
                    e.g. If the tracker component is after the detector component in the pipeline, then positional parameters are from tracker component.
                    Can also be used to overlay borders / semi-transparent boxes on top of objects. See :class:`NvOSD_RectParams`
                :ivar mask_params: :class:`NvOSD_MaskParams`, Holds mask parameters for the object. This mask is overlaid on object See :class:`NvOSD_MaskParams`
                :ivar text_params: :class:`NvOSD_TextParams`, Text describing the object can be overlayed using this structure. See :class:`NvOSD_TextParams`
                :ivar obj_label: An array to store the string describing the class of the detected object
                :ivar classifier_meta_list: list of objects of type :class:`NvDsClassifierMeta`
                :ivar obj_user_meta_list: list of objects of type :class:`NvDsUserMeta`
                :ivar misc_obj_info: *list of int*, For additional user specific batch info
                :ivar reserved: *int*, Reserved for internal use.

                Example usage:
                ::

                    #Initialize dict to keep count of objects of each type
                    obj_counter = {
                            PGIE_CLASS_ID_VEHICLE:0,
                            PGIE_CLASS_ID_PERSON:0,
                            PGIE_CLASS_ID_BICYCLE:0,
                            PGIE_CLASS_ID_ROADSIGN:0
                        }

                    l_obj=frame_meta.obj_meta_list #Retrieve list of NvDsObjectMeta objects in frame from an NvDsFrameMeta object. See NvDsFrameMeta documentation for more details.
                    while l_obj is not None:
                        try:
                            # Casting l_obj.data to pyds.NvDsObjectMeta
                            obj_meta=pyds.NvDsObjectMeta.cast(l_obj.data)
                            except StopIteration:
                                break
                            obj_counter[obj_meta.class_id] += 1 #Retrieve class_id from NvDsObjectMeta (i.e. PGIE_CLASS_ID_VEHICLE, PGIE_CLASS_ID_PERSON, etc.) to update count
                            obj_meta.rect_params.border_color.set(0.0, 0.0, 1.0, 0.0) #Set border color of NvDsObjectMeta object's rect_params
                            try: 
                                l_obj=l_obj.next
                            except StopIteration:
                                break)pyds";

            constexpr const char* cast=R"pyds(cast given object/data to :class:`NvDsObjectMeta`, call pyds.NvDsObjectMeta.cast(data))pyds";
        }

        namespace ClassifierMetaDoc
        {
            constexpr const char* descr = R"pyds(
                Holds classifier metadata for an object.
                
                :ivar base_meta: :class:`NvDsBaseMeta`, base_meta
                :ivar num_labels: *int*, Number of outputs/labels of the classifier.
                :ivar unique_component_id: *int*, Unique component id that attaches NvDsClassifierMeta metadata.
                :ivar label_info_list: List of objects of type :class:`NvDsLabelInfo`.)pyds";

            constexpr const char* cast=R"pyds(cast given object/data to :class:`NvDsClassifierMeta`, call pyds.NvDsClassifierMeta.cast(data))pyds";
        }

        namespace LabelInfoDoc
        {
            constexpr const char* descr = R"pyds(
                Holds information of label metadata in the classifier.

                :ivar base_meta: :class:`NvDsBaseMeta`, base_meta 
                :ivar num_classes: *int*, Number of classes of the given label.
                :ivar result_label: An array to store the string describing the label of the classified object. 
                :ivar pResult_label: *str*, An object to store the result label if it exceeds MAX_LABEL_SIZE bytes.
                :ivar result_class_id: *int*, class_id of the best result. 
                :ivar label_id: *int*, Holds the label ID in case there are multiple label classifiers.
                :ivar result_prob: *float*, Probability of best result.)pyds";

            constexpr const char* cast=R"pyds(cast given object/data to :class:`NvDsLabelInfo`, call pyds.NvDsLabelInfo.cast(data))pyds";
        }

        namespace DisplayMetaDoc
        {
            constexpr const char* descr = R"pyds(
                Holds information of display metadata that user can specify in the frame.

                :ivar base_meta: :class:`NvDsBaseMeta`, base_meta
                :ivar num_rects: *int*, Number of rectangles present in display meta. 
                :ivar num_labels: *int*, Number of labels/strings present in display meta.
                :ivar num_lines: *int*, Number of lines present in display meta.
                :ivar rect_params: List of :class:`NvOSD_RectParams`, Holds a list of positional parameters for rectangles. Used to overlay borders or semi-transparent rectangles, as required by the application. See :class:`NvOSD_RectParams`.
                :ivar text_params: List of :class:`NvOSD_TextParams`, Holds a list of text parameters for user-defined strings that can be overlayed using this structure. See :class:`NvOSD_TextParams`.
                :ivar line_params: List of :class:`NvOSD_LineParams`, Holds a list of line parameters that the user can use to draw polygons in the frame, e.g. to show a RoI in the frame. See :class:`NvOSD_LineParams`.
                :ivar num_arrows: *int*, Holds the number of arrows described.
                :ivar num_circles: *int*, Holds the number of circles described.
                :ivar arrow_params: List of :class:`NvOSD_ArrowParams`, Holds a list of arrow parameters that the user can use to draw arrows in the frame. See :class:`NvOSD_ArrowParams`: 
                :ivar circle_params: List of :class:`NvOSD_CircleParams`, Holds a list of circle parameters that the user can use to draw circle in the frame. See :class:`NvOSD_CircleParams`.
                :ivar misc_osd_data: *np.array of int*, Holds an np.array of user-defined OSD metadata.
                :ivar reserved: *list of int*, Reserved for internal use.

                Example usage:
                ::

                    display_meta=pyds.nvds_acquire_display_meta_from_pool(batch_meta) #Retrieve NvDsDisplayMeta object from pool in given NvDsBatchMeta object
                    display_meta.num_labels = 1
                    py_nvosd_text_params = display_meta.text_params[0] #Retrieve NvOSD_TextParams object from list in display meta. See NvOSD docs for more details.
                    # Setting display text to be shown on screen
                    # Note that the pyds module allocates a buffer for the string, and the
                    # memory will not be claimed by the garbage collector.
                    # Reading the display_text field here will return the C address of the
                    # allocated string. Use pyds.get_string() to get the string content.
                    py_nvosd_text_params.display_text = "Frame Number={} Number of Objects={} Vehicle_count={} Person_count={}".format(frame_number, num_rects, obj_counter[PGIE_CLASS_ID_VEHICLE], obj_counter[PGIE_CLASS_ID_PERSON])

                    print(pyds.get_string(py_nvosd_text_params.display_text))
                    pyds.nvds_add_display_meta_to_frame(frame_meta, display_meta) #Use method to add display_meta to frame_meta.)pyds";

            constexpr const char* cast=R"pyds(cast given object/data to :class:`NvDsDisplayMeta`, call pyds.NvDsDisplayMeta.cast(data))pyds";
        }

        namespace UserMetaDoc
        {
            constexpr const char* descr = R"pyds(
                Holds information of user metadata that user can specify.

                :ivar base_meta: :class:`NvDsBaseMeta`, base_meta
                :ivar user_meta_data: User data object to be attached. Refer to deepstream-user-metadata-test example for usage.

                Example usage, where user metadata is of type NVDS_TRACKER_PAST_FRAME_META:
                ::

                    l_user=batch_meta.batch_user_meta_list #Retrieve glist containing NvDsUserMeta objects from given NvDsBatchMeta object
                    while l_user is not None:
                        try:
                            # Note that l_user.data needs a cast to pyds.NvDsUserMeta
                            # The casting is done by pyds.NvDsUserMeta.cast()
                            # The casting also keeps ownership of the underlying memory
                            # in the C code, so the Python garbage collector will leave
                            # it alone
                            user_meta=pyds.NvDsUserMeta.cast(l_user.data) 
                        except StopIteration:
                            break
                        if(user_meta and user_meta.base_meta.meta_type==pyds.NvDsMetaType.NVDS_TRACKER_PAST_FRAME_META): #Check data type of user_meta
                            try:
                                # Note that user_meta.user_meta_data needs a cast to pyds.NvDsPastFrameObjBatch
                                # The casting is done by pyds.NvDsPastFrameObjBatch.cast()
                                # The casting also keeps ownership of the underlying memory
                                # in the C code, so the Python garbage collector will leave
                                # it alone
                                pPastFrameObjBatch = pyds.NvDsPastFrameObjBatch.cast(user_meta.user_meta_data)
                            except StopIteration:
                                break
                            for trackobj in pyds.NvDsPastFrameObjBatch.list(pPastFrameObjBatch):
                                ... #Examine past frame information, see NvDsTrackerMeta docs for details.
                            try:
                                l_user=l_user.next
                            except StopIteration:
                                break)pyds";

            constexpr const char* cast=R"pyds(cast given object/data to :class:`NvDsUserMeta`, call pyds.NvDsUserMeta.cast(data))pyds";
        }

    }

    namespace metaschema
    {
        namespace EventTypeDoc
        {
            constexpr const char* descr = R"pyds(*Enumerator*. Event type flags.)pyds";
            constexpr const char* NVDS_EVENT_ENTRY=R"pyds(NVDS_EVENT_ENTRY)pyds";
            constexpr const char* NVDS_EVENT_EXIT=R"pyds(NVDS_EVENT_EXIT)pyds";
            constexpr const char* NVDS_EVENT_MOVING=R"pyds(NVDS_EVENT_MOVING)pyds";
            constexpr const char* NVDS_EVENT_STOPPED=R"pyds(NVDS_EVENT_STOPPED)pyds";
            constexpr const char* NVDS_EVENT_EMPTY=R"pyds(NVDS_EVENT_EMPTY)pyds";
            constexpr const char* NVDS_EVENT_PARKED=R"pyds(NVDS_EVENT_PARKED)pyds";
            constexpr const char* NVDS_EVENT_RESET=R"pyds(NVDS_EVENT_RESET)pyds";
            constexpr const char* NVDS_EVENT_RESERVED=R"pyds(Reserved for future use. Use value greater than this for custom events.)pyds";
            constexpr const char* NVDS_EVENT_CUSTOM=R"pyds(Specifies a custom event.)pyds";
            constexpr const char* NVDS_EVENT_FORCE32=R"pyds(NVDS_EVENT_FORCE32)pyds";
        }        

        namespace ObjectTypeDoc
        {
            constexpr const char* descr = R"pyds(*Enumerator*. Object type flags.)pyds";
            constexpr const char* NVDS_OBJECT_TYPE_VEHICLE=R"pyds(NVDS_OBJECT_TYPE_VEHICLE)pyds";
            constexpr const char* NVDS_OBJECT_TYPE_PERSON=R"pyds(NVDS_OBJECT_TYPE_PERSON)pyds";
            constexpr const char* NVDS_OBJECT_TYPE_FACE=R"pyds(NVDS_OBJECT_TYPE_FACE)pyds";
            constexpr const char* NVDS_OBJECT_TYPE_BAG=R"pyds(NVDS_OBJECT_TYPE_BAG)pyds";
            constexpr const char* NVDS_OBJECT_TYPE_BICYCLE=R"pyds(NVDS_OBJECT_TYPE_BICYCLE)pyds";
            constexpr const char* NVDS_OBJECT_TYPE_ROADSIGN=R"pyds(NVDS_OBJECT_TYPE_ROADSIGN)pyds";
            constexpr const char* NVDS_OBJECT_TYPE_RESERVED=R"pyds(Reserved for future use. Use value greater than this for custom objects.)pyds";
            constexpr const char* NVDS_OBJECT_TYPE_CUSTOM=R"pyds(To support custom object.)pyds";
            constexpr const char* NVDS_OBJECT_TYPE_VEHICLE_EXT=R"pyds(NVDS_OBJECT_TYPE_VEHICLE_EXT)pyds";
            constexpr const char* NVDS_OBJECT_TYPE_PERSON_EXT=R"pyds(NVDS_OBJECT_TYPE_PERSON_EXT)pyds";
            constexpr const char* NVDS_OBJECT_TYPE_FACE_EXT=R"pyds(NVDS_OBJECT_TYPE_FACE_EXT)pyds";
            constexpr const char* NVDS_OBJECT_TYPE_UNKNOWN=R"pyds("object" key will be missing in the schema)pyds";
            constexpr const char* NVDS_OBEJCT_TYPE_FORCE32=R"pyds(NVDS_OBEJCT_TYPE_FORCE32)pyds";
        }

        namespace PayloadTypeDoc
        {
            constexpr const char* descr = R"pyds(*Enumerator*. Payload type flags.)pyds";
            constexpr const char* NVDS_PAYLOAD_DEEPSTREAM=R"pyds(NVDS_PAYLOAD_DEEPSTREAM)pyds";
            constexpr const char* NVDS_PAYLOAD_DEEPSTREAM_MINIMAL=R"pyds(NVDS_PAYLOAD_DEEPSTREAM_MINIMAL)pyds";
            constexpr const char* NVDS_PAYLOAD_RESERVED=R"pyds(Reserved for future use. Use value greater than this for custom payloads.)pyds";
            constexpr const char* NVDS_PAYLOAD_CUSTOM=R"pyds(To support custom payload. User need to implement nvds_msg2p_* interface)pyds";
            constexpr const char* NVDS_PAYLOAD_FORCE32=R"pyds(NVDS_PAYLOAD_FORCE32)pyds";
        }

        namespace RectDoc   
        {
            constexpr const char* descr = R"pyds(
                Holds a rectangle's position and size.
                
                :ivar top: *float*, Holds the position of rectangle's top in pixels.
                :ivar left: *float*, Holds the position of rectangle's left side in pixels.
                :ivar width: *float*, Holds the rectangle's width in pixels.
                :ivar height: *float*, Holds the rectangle's height in pixels.)pyds";

            constexpr const char* cast=R"pyds(cast given object/data to :class:`NvDsRect`, call pyds.NvDsRect.cast(data))pyds";
        }

        namespace GeoLocationDoc
        {
            constexpr const char* descr = R"pyds(
                Holds Geo-location parameters.

                :ivar lat: *float*, Holds the location's latitude.
                :ivar lon: *float*, Holds the location's longitude.
                :ivar alt: *float*, Holds the location's altitude.)pyds";

            constexpr const char* cast=R"pyds(cast given object/data to :class:`NvDsGeoLocation`, call pyds.NvDsGeoLocation.cast(data))pyds";
        }

        namespace CoordinateDoc
        {
            constexpr const char* descr = R"pyds(
                Hold coordinate parameters.
                
                :ivar x: *float*, Holds the coordinate's X position.
                :ivar y: *float*, Holds the coordinate's Y position.
                :ivar z: *float*, Holds the coordinate's Z position.)pyds";

            constexpr const char* cast=R"pyds(cast given object/data to :class:`NvDsCoordinate`, call pyds.NvDsCoordinate.cast(data))pyds";
        }

        namespace ObjectSignatureDoc
        {
            constexpr const char* descr = R"pyds(
                Holds object signature.
                
                :ivar signature: *list of float*, Holds signature values.
                :ivar size: *int*, Holds the number of signature values in signature.)pyds";

            constexpr const char* cast=R"pyds(cast given object/data to :class:`NvDsObjectSignature`, call pyds.NvDsObjectSignature.cast(data))pyds";
        }

        namespace VehicleObjectDoc
        {
            constexpr const char* descr = R"pyds(
                Holds vehicle object parameters.

                :ivar type: *str*, Type of the vehicle.
                :ivar make: *str*, Make of the vehicle.
                :ivar model: *str*, Model of the vehicle.
                :ivar color: *str*, Color of the vehicle.
                :ivar region: *str*, Region of the vehicle.
                :ivar license: *str*, License number of the vehicle.

                Example usage:
                ::

                    data = pyds.alloc_nvds_vehicle_object() #Allocate NvDsVehicleObject
                    obj = pyds.NvDsVehicleObject.cast(data);
                    #Set attributes
                    obj.type ="sedan"
                    obj.color="blue"
                    obj.make ="Bugatti"
                    obj.model = "M"
                    obj.license ="XX1234"
                    obj.region ="CA")pyds";

            constexpr const char* cast=R"pyds(casts to :class:`NvDsVehicleObject` object, call pyds.NvDsVehicleObject(data))pyds";
        }

        namespace PersonObjectDoc
        {
            constexpr const char* descr = R"pyds(
                Holds a person object's parameters.

                :ivar gender: *str*, Person's gender.
                :ivar hair: *str*, Person's hair color.
                :ivar cap: *str*, Type of cap the person is wearing, if any.
                :ivar apparel: *str*, Description of the person's apparel.
                :ivar age: *int*, Person's age.

                Example usage:
                ::

                    data = pyds.alloc_nvds_person_object() #Allocate NvDsPersonObject
                    obj = pyds.NvDsPersonObject.cast(data)
                    #Set attributes
                    obj.age = 45
                    obj.cap = "none"
                    obj.hair = "black"
                    obj.gender = "male"
                    obj.apparel= "formal")pyds";

            constexpr const char* cast=R"pyds(casts to :class:`NvDsPersonObject` object, call pyds.NvDsPersonObject(data))pyds";
        }

        namespace FaceObjectDoc
        {
            constexpr const char* descr = R"pyds(
                Holds face parameters.

                :ivar gender: *str*, Person's gender.
                :ivar hair: *str*, Person's hair color.
                :ivar cap: *str*, Type of cap the person is wearing, if any.
                :ivar glasses: *str*, Type of glasses the person is wearing, if any.
                :ivar facialhair: *str*, Person's facial hair color.
                :ivar name: *str*, Person's name.
                :ivar eyecolor: *str*, Person's eye color.
                :ivar age: *int*, Person's age.)pyds";

            constexpr const char* cast=R"pyds(casts to :class:`NvDsFaceObject` object, call pyds.NvDsFaceObject(data))pyds";
        }

        namespace NvDsVehicleObjectExtDoc
        {
            constexpr const char* descr = R"pyds(
                Holds a vehicle object's parameters.

                :ivar type: *str*, Type of the vehicle.
                :ivar make: *str*, Make of the vehicle.
                :ivar model: *str*, Model of the vehicle.
                :ivar color: *str*, Color of the vehicle.
                :ivar region: *str*, Region of the vehicle.
                :ivar license: *str*, License number of the vehicle.
                :ivar mask: *Glist* of polygons for vehicle mask.)pyds";

            constexpr const char* cast=R"pyds(cast given object/data to :class:`NvDsVehicleObjectExt`, call pyds.NvDsVehicleObjectExt.cast(data))pyds";
        }

        namespace NvDsPersonObjectExtDoc
        {
            constexpr const char* descr = R"pyds(
                Holds a vehicle object's parameters.

                :ivar gender: *str*, Person's gender.
                :ivar hair: *str*, Person's hair color.
                :ivar cap: *str*, Type of cap the person is wearing, if any.
                :ivar apparel: *str*, Description of the person's apparel.
                :ivar age: *int*, Person's age.
                :ivar mask: *Glist* of polygons for person mask.)pyds";

            constexpr const char* cast=R"pyds(cast given object/data to :class:`NvDsPersonObjectExt`, call pyds.NvDsPersonObjectExt.cast(data))pyds";
        }

        namespace NvDsFaceObjectWithExtDoc
        {
            constexpr const char* descr = R"pyds(
                Holds a vehicle object's parameters.
                
                :ivar gender: *str*, Person's gender.
                :ivar hair: *str*, Person's hair color.
                :ivar cap: *str*, Type of cap the person is wearing, if any.
                :ivar glasses: *str*, Type of glasses the person is wearing, if any.W
                :ivar facialhair: *str*, Person's facial hair color.Ws
                :ivar name: *str*, Person's name.
                :ivar eyecolor: *str*, Person's eye color.
                :ivar age: *int*, Person's age.
                :ivar mask: *Glist* of polygons for face mask.)pyds";

            constexpr const char* cast=R"pyds(cast given object/data to :class:`NvDsFaceObjectWithExt`, call pyds.NvDsFaceObjectWithExt.cast(data))pyds";
        }

        namespace EventmsgDoc
        {
            constexpr const char* descr = R"pyds(
                Holds event message meta data. You can attach various types of objects (vehicle, person, face, etc.) to an event by setting a pointer to the object in :py:attr:`extMsg`. 
                Similarly, you can attach a custom object to an event by setting a pointer to the object in :py:attr:`extMsg`.
                A custom object must be handled by the metadata parsing module accordingly.

                :ivar type: :class:`NvDsEventType`, Type of event.
                :ivar objType: :class:`NvDsObjectType`, Type of object.
                :ivar bbox: :class:`NvDsRect`, Bounding box of object.
                :ivar location: :class:`NvDsGeoLocation`, Geo-location of object.
                :ivar coordinate: :class:`NvDsCoordinate`, Coordinate of object.
                :ivar objSignature: :class:`NvDsObjectSignature`, Signature of object.
                :ivar objClassId: *int*, Class id of object.
                :ivar sensorId: *int*, ID of sensor that generated the event.
                :ivar moduleId: *int*, ID of analytics module that generated the event.
                :ivar placeId: *int*, ID of place related to the object.
                :ivar componentId: *int*, ID of component that generated this event.
                :ivar frameId: *int*, Video frame ID of this event.
                :ivar confidence: *int*, Confidence level of the inference.
                :ivar trackingId: *int*, Tracking ID of object.
                :ivar ts: *str*, Time stamp of generated event.
                :ivar objectId: *str*, ID of detected / inferred object.
                :ivar sensorStr: *str*, Identity string of sensor.
                :ivar otherAttrs: *str*, Other attributes associated with the object.
                :ivar videoPath: *str*, Name of video file.
                :ivar extMsg: Object to extend the event message meta data. This can be used for custom values that can't be accommodated in the existing fields 
                    OR if object(vehicle, person, face etc.) Specific values must be attached.
                :ivar extMsgSize: *int*, Size of the custom object at extMsg.

                Example usage:
                ::

                    def generate_event_msg_meta(data, class_id):
                        meta =pyds.NvDsEventMsgMeta.cast(data)
                        meta.sensorId = 0
                        meta.placeId = 0
                        meta.moduleId = 0
                        meta.sensorStr = "sensor-0"
                        meta.ts = pyds.alloc_buffer(MAX_TIME_STAMP_LEN + 1)
                        pyds.generate_ts_rfc3339(meta.ts, MAX_TIME_STAMP_LEN) #Generate timestamp

                        # This demonstrates how to attach custom objects.
                        # Any custom object as per requirement can be generated and attached
                        # like NvDsVehicleObject / NvDsPersonObject. Then that object should
                        # be handled in payload generator library (nvmsgconv.cpp) accordingly.
                        if(class_id==PGIE_CLASS_ID_VEHICLE):
                            meta.type = pyds.NvDsEventType.NVDS_EVENT_MOVING
                            meta.objType = pyds.NvDsObjectType.NVDS_OBJECT_TYPE_VEHICLE
                            meta.objClassId = PGIE_CLASS_ID_VEHICLE
                            obj = pyds.alloc_nvds_vehicle_object()
                            obj = generate_vehicle_meta(obj) #See NvDsVehicleObject example code
                            meta.extMsg = obj
                            meta.extMsgSize = sys.getsizeof(pyds.NvDsVehicleObject);
                        if(class_id == PGIE_CLASS_ID_PERSON):
                            meta.type =pyds.NvDsEventType.NVDS_EVENT_ENTRY
                            meta.objType = pyds.NvDsObjectType.NVDS_OBJECT_TYPE_PERSON;
                            meta.objClassId = PGIE_CLASS_ID_PERSON
                            obj = pyds.alloc_nvds_person_object()
                            obj=generate_person_meta(obj)
                            meta.extMsg = obj
                            meta.extMsgSize = sys.getsizeof(pyds.NvDsPersonObject)
                        return meta

                    ...

                    # Allocating an NvDsEventMsgMeta instance and getting reference
                    # to it. The underlying memory is not manged by Python so that
                    # downstream plugins can access it. Otherwise the garbage collector
                    # will free it when this probe exits.
                    msg_meta=pyds.alloc_nvds_event_msg_meta()
                    msg_meta.bbox.top =  obj_meta.rect_params.top
                    msg_meta.bbox.left =  obj_meta.rect_params.left
                    msg_meta.bbox.width = obj_meta.rect_params.width
                    msg_meta.bbox.height = obj_meta.rect_params.height
                    msg_meta.frameId = frame_number
                    msg_meta.trackingId = long_to_uint64(obj_meta.object_id)
                    msg_meta.confidence = obj_meta.confidence
                    msg_meta = generate_event_msg_meta(msg_meta, obj_meta.class_id)
                    user_event_meta = pyds.nvds_acquire_user_meta_from_pool(batch_meta)
                    if(user_event_meta):
                        user_event_meta.user_meta_data = msg_meta;
                        user_event_meta.base_meta.meta_type = pyds.NvDsMetaType.NVDS_EVENT_MSG_META
                        # Setting callbacks in the event msg meta. The bindings layer
                        # will wrap these callables in C functions. Currently only one
                        # set of callbacks is supported.
                        pyds.user_copyfunc(user_event_meta, meta_copy_func)
                        pyds.user_releasefunc(user_event_meta, meta_free_func)
                        pyds.nvds_add_user_meta_to_frame(frame_meta, user_event_meta)
                    else:
                        print("Error in attaching event meta to buffer\n"))pyds";

            constexpr const char* cast=R"pyds(casts to :class:`NvDsEventMsgMeta` object, call pyds.NvDsEventMsgMeta(data))pyds";
        }

        namespace EventDoc
        {
            constexpr const char* descr = R"pyds(
                Holds event information.

                :ivar eventType: :class:`NvDsEventType`, Type of event.
                :ivar metadata: :class:`NvDsEventMsgMeta`, object of event meta data.)pyds";

            constexpr const char* cast=R"pyds(cast given object/data to :class:`NvDsEvent`, call pyds.NvDsEvent.cast(data))pyds";
        }

        namespace PayloadDoc
        {
            constexpr const char* descr = R"pyds(
                Holds payload meta data.

                :ivar payload: Payload object.
                :ivar payloadSize: *int*, Size of payload.
                :ivar componentId: *int*, ID of component who attached the payload (Optional).)pyds";

            constexpr const char* cast=R"pyds(cast given object/data to :class:`NvDsPayload`, call pyds.NvDsPayload.cast(data))pyds";
        }
    }

    namespace meta360doc
    {
        namespace ROI_STATUS_360Ddoc
        {
            constexpr const char* descr = R"pyds(*Enumerator*. Defines DeepStream 360d metadata.)pyds";
            constexpr const char* ROI_ENTRY_360Ddoc=R"pyds(ROI_ENTRY_360D)pyds";
            constexpr const char* ROI_EXIT_360Ddoc=R"pyds(ROI_EXIT_360D.)pyds";
            constexpr const char* INSIDE_AISLE_360Ddoc=R"pyds(INSIDE_AISLE_360D.)pyds";
        }

        namespace RectDimdoc
        {
            constexpr const char* descr = R"pyds(
                RectDim

                :ivar left: *float*, left
                :ivar top: *float*, top
                :ivar width: *float*, width
                :ivar height: *float*, height
                :ivar class_id: *int*, class_id
                :ivar tracking_id: *int*, tracking_id
                :ivar gie_unique_id: *int*, gie_unique_id
                :ivar roi_status: *int*, roi_status
                :ivar text: text
                :ivar left: *float*, left)pyds";

            constexpr const char* cast=R"pyds(cast given object/data to :class:`RectDim`, call pyds.RectDim.cast(data))pyds";
        }
    }

    namespace nvdsanalyticsdoc
    {
        namespace NvDsAnalyticsObjInfoDoc
        {
            constexpr const char* descr = R"pyds(
                Holds a set of nvdsanalytics object level metadata.

                :ivar roiStatus: *list of str*, Holds the array of ROI labels in which object is present.
                :ivar ocStatus: *list of str*, Holds the array  of OverCrowding labels in which object is present.
                :ivar lcStatus: *list of str*, Holds the array of line crossing labels which object has crossed.
                :ivar dirStatus: *str*, Holds the direction string for the tracked object.
                :ivar unique_id: *int*, Holds unique identifier for nvdsanalytics instance.

                Example usage:
                ::

                    # Extract object level meta data from NvDsAnalyticsObjInfo
                    l_user_meta = obj_meta.obj_user_meta_list #Get glist containing NvDsUserMeta objects from given NvDsObjectMeta
                    # Extract object level meta data from NvDsAnalyticsObjInfo
                    while l_user_meta:
                        try:
                            user_meta = pyds.NvDsUserMeta.cast(l_user_meta.data) #Must cast glist data to NvDsUserMeta object
                            if user_meta.base_meta.meta_type == pyds.nvds_get_user_meta_type("NVIDIA.DSANALYTICSOBJ.USER_META"):             
                            user_meta_data = pyds.NvDsAnalyticsObjInfo.cast(user_meta.user_meta_data) #Must cast user metadata to NvDsAnalyticsObjInfo
                            #Access NvDsAnalyticsObjInfo attributes with user_meta_data.{attribute name}
                            if user_meta_data.dirStatus: print("Object {0} moving in direction: {1}".format(obj_meta.object_id, user_meta_data.dirStatus))
                            if user_meta_data.lcStatus: print("Object {0} line crossing status: {1}".format(obj_meta.object_id, user_meta_data.lcStatus))
                            if user_meta_data.ocStatus: print("Object {0} overcrowding status: {1}".format(obj_meta.object_id, user_meta_data.ocStatus))
                            if user_meta_data.roiStatus: print("Object {0} roi status: {1}".format(obj_meta.object_id, user_meta_data.roiStatus))
                        except StopIteration:
                            break

                        try:
                            l_user_meta = l_user_meta.next
                            except StopIteration:
                            break)pyds";

            constexpr const char* cast=R"pyds(cast given object/data to :class:`NvDsAnalyticsObjInfo`, call pyds.NvDsAnalyticsObjInfo.cast(data))pyds";
        }

        namespace NvDsAnalyticsFrameMetaDoc
        {
            constexpr const char* descr = R"pyds(
                Holds a set of nvdsanalytics object level metadata.

                :ivar ocStatus: *dict<str, bool>*, Holds a map of boolean status of overcrowding for configured ROIs,which can be accessed using key, value pair; where key is the ROI label.
                :ivar objInROIcnt: *dict<str, int>*, Holds a map of total count of valid objects in ROI  for configured ROIs,which can be accessed using key, value pair; where key is the ROI label.
                :ivar objLCCurrCnt: *dict<str, int>*, Holds a map of total count of Line crossing in current frame for configured lines, which can be accessed using key, value pair; where key is the line crossing label.
                :ivar objLCCumCnt: *dict<str, int>*, Holds a map of total cumulative count of Line crossing  for configured lines, can be accessed using key, value pair; where key is the line crossing label
                :ivar unique_id: *str*, Holds unique identifier for nvdsanalytics instance.
                :ivar objCnt: *int*, Holds a map of total count of objects for each class ID, can be accessed using key, value pair; where key is class ID.

                Example usage:
                ::

                    # Get meta data from NvDsAnalyticsFrameMeta
                    l_user = frame_meta.frame_user_meta_list #Get glist containing NvDsUserMeta objects from given NvDsFrameMeta
                    while l_user:
                        try:
                            user_meta = pyds.NvDsUserMeta.cast(l_user.data) #Must cast glist data to NvDsUserMeta object
                            if user_meta.base_meta.meta_type == pyds.nvds_get_user_meta_type("NVIDIA.DSANALYTICSFRAME.USER_META"):
                                user_meta_data = pyds.NvDsAnalyticsFrameMeta.cast(user_meta.user_meta_data) #Must cast user metadata to NvDsAnalyticsFrameMeta
                                #Access NvDsAnalyticsFrameMeta attributes with user_meta_data.{attribute name}
                                if user_meta_data.objInROIcnt: print("Objs in ROI: {0}".format(user_meta_data.objInROIcnt))                    
                                if user_meta_data.objLCCumCnt: print("Linecrossing Cumulative: {0}".format(user_meta_data.objLCCumCnt))
                                if user_meta_data.objLCCurrCnt: print("Linecrossing Current Frame: {0}".format(user_meta_data.objLCCurrCnt))
                                if user_meta_data.ocStatus: print("Overcrowding status: {0}".format(user_meta_data.ocStatus))
                        except StopIteration:
                            break
                        try:
                            l_user = l_user.next
                        except StopIteration:
                            break)pyds";

            constexpr const char* cast=R"pyds(cast given object/data to :class:`NvDsAnalyticsFrameMeta`, call pyds.NvDsAnalyticsFrameMeta.cast(data))pyds";
        }
     }
    
    namespace  nvbufdoc
    {
        namespace MemMapFlagsDoc
        {
            constexpr const char* descr = R"pyds(*Enumerator*. Specifies mapping types for :class:`NvBufSurface`.)pyds";
            constexpr const char* NVBUF_MAP_READ=R"pyds(Specifies :class:`NvBufSurface` mapping type "read.")pyds";
            constexpr const char* NVBUF_MAP_WRITE=R"pyds(Specifies :class:`NvBufSurface` mapping type "write.")pyds";
            constexpr const char* NVBUF_MAP_READ_WRITE=R"pyds(Specifies :class:`NvBufSurface` mapping type "read/write.")pyds";
        }

        namespace NvBufSurfaceColorFormatDoc
        {
            constexpr const char* descr = R"pyds(*Enumerator*. Specifies color formats for :class:`NvBufSurface`.)pyds";
            constexpr const char* NVBUF_COLOR_FORMAT_INVALID=R"pyds(Invalid color format)pyds";
            constexpr const char* NVBUF_COLOR_FORMAT_GRAY8 =R"pyds(8 bit GRAY scale - single plane)pyds";
            constexpr const char* NVBUF_COLOR_FORMAT_YUV420 =R"pyds(BT.601 colorspace - YUV420 multi-planar.)pyds";
            constexpr const char* NVBUF_COLOR_FORMAT_YVU420 =R"pyds(BT.601 colorspace - YUV420 multi-planar.)pyds";
            constexpr const char* NVBUF_COLOR_FORMAT_YUV420_ER =R"pyds(BT.601 colorspace - YUV420 ER multi-planar.)pyds";
            constexpr const char* NVBUF_COLOR_FORMAT_YVU420_ER =R"pyds(BT.601 colorspace - YVU420 ER multi-planar.)pyds";
            constexpr const char* NVBUF_COLOR_FORMAT_NV12 =R"pyds(BT.601 colorspace - Y/CbCr 4:2:0 multi-planar.)pyds";
            constexpr const char* NVBUF_COLOR_FORMAT_NV12_ER =R"pyds(BT.601 colorspace - Y/CbCr ER 4:2:0 multi-planar.)pyds";
            constexpr const char* NVBUF_COLOR_FORMAT_NV21 =R"pyds(BT.601 colorspace - Y/CbCr 4:2:0 multi-planar.)pyds";
            constexpr const char* NVBUF_COLOR_FORMAT_NV21_ER =R"pyds(BT.601 colorspace - Y/CbCr ER 4:2:0 multi-planar.)pyds";
            constexpr const char* NVBUF_COLOR_FORMAT_UYVY =R"pyds(BT.601 colorspace - YUV 4:2:2 planar.)pyds";
            constexpr const char* NVBUF_COLOR_FORMAT_UYVY_ER =R"pyds(BT.601 colorspace - YUV ER 4:2:2 planar.)pyds";
            constexpr const char* NVBUF_COLOR_FORMAT_VYUY =R"pyds(BT.601 colorspace - YUV 4:2:2 planar.)pyds";
            constexpr const char* NVBUF_COLOR_FORMAT_VYUY_ER =R"pyds(BT.601 colorspace - YUV ER 4:2:2 planar.)pyds";
            constexpr const char* NVBUF_COLOR_FORMAT_YUYV =R"pyds(BT.601 colorspace - YUV 4:2:2 planar.)pyds";
            constexpr const char* NVBUF_COLOR_FORMAT_YUYV_ER =R"pyds(BT.601 colorspace - YUV ER 4:2:2 planar.)pyds";
            constexpr const char* NVBUF_COLOR_FORMAT_YVYU =R"pyds(BT.601 colorspace - YUV 4:2:2 planar.)pyds";
            constexpr const char* NVBUF_COLOR_FORMAT_YVYU_ER =R"pyds(BT.601 colorspace - YUV ER 4:2:2 planar.)pyds";
            constexpr const char* NVBUF_COLOR_FORMAT_YUV444 =R"pyds(BT.601 colorspace - YUV444 multi-planar.)pyds";
            constexpr const char* NVBUF_COLOR_FORMAT_RGBA =R"pyds(RGBA-8-8-8-8 single plane.)pyds";
            constexpr const char* NVBUF_COLOR_FORMAT_BGRA =R"pyds(BGRA-8-8-8-8 single plane.)pyds";
            constexpr const char* NVBUF_COLOR_FORMAT_ARGB =R"pyds(ARGB-8-8-8-8 single plane.)pyds";
            constexpr const char* NVBUF_COLOR_FORMAT_ABGR =R"pyds(ABGR-8-8-8-8 single plane.)pyds";
            constexpr const char* NVBUF_COLOR_FORMAT_RGBx =R"pyds(RGBx-8-8-8-8 single plane.)pyds";
            constexpr const char* NVBUF_COLOR_FORMAT_BGRx =R"pyds(BGRx-8-8-8-8 single plane.)pyds";
            constexpr const char* NVBUF_COLOR_FORMAT_xRGB =R"pyds(xRGB-8-8-8-8 single plane.)pyds";
            constexpr const char* NVBUF_COLOR_FORMAT_xBGR =R"pyds(xBGR-8-8-8-8 single plane.)pyds";
            constexpr const char* NVBUF_COLOR_FORMAT_RGB =R"pyds(RGB-8-8-8 single plane.)pyds";
            constexpr const char* NVBUF_COLOR_FORMAT_BGR =R"pyds(BGR-8-8-8 single plane.)pyds";
            constexpr const char* NVBUF_COLOR_FORMAT_NV12_10LE =R"pyds(BT.601 colorspace - Y/CbCr 4:2:0 10-bit multi-planar.)pyds";
            constexpr const char* NVBUF_COLOR_FORMAT_NV12_12LE =R"pyds(BT.601 colorspace - Y/CbCr 4:2:0 12-bit multi-planar.)pyds";
            constexpr const char* NVBUF_COLOR_FORMAT_YUV420_709 =R"pyds(BT.709 colorspace - YUV420 multi-planar.)pyds";
            constexpr const char* NVBUF_COLOR_FORMAT_YUV420_709_ER =R"pyds(BT.709 colorspace - YUV420 ER multi-planar.)pyds";
            constexpr const char* NVBUF_COLOR_FORMAT_NV12_709 =R"pyds(BT.709 colorspace - Y/CbCr 4:2:0 multi-planar.)pyds";
            constexpr const char* NVBUF_COLOR_FORMAT_NV12_709_ER =R"pyds(BT.709 colorspace - Y/CbCr ER 4:2:0 multi-planar.)pyds";
            constexpr const char* NVBUF_COLOR_FORMAT_YUV420_2020 =R"pyds(BT.2020 colorspace - YUV420 multi-planar.)pyds";
            constexpr const char* NVBUF_COLOR_FORMAT_NV12_2020 =R"pyds(BT.2020 colorspace - Y/CbCr 4:2:0 multi-planar.)pyds";
            constexpr const char* NVBUF_COLOR_FORMAT_NV12_10LE_ER =R"pyds(BT.601 colorspace - Y/CbCr ER 4:2:0 10-bit multi-planar.)pyds";
            constexpr const char* NVBUF_COLOR_FORMAT_NV12_10LE_709 =R"pyds(BT.709 colorspace - Y/CbCr 4:2:0 10-bit multi-planar.)pyds";
            constexpr const char* NVBUF_COLOR_FORMAT_NV12_10LE_709_ER =R"pyds(BT.709 colorspace - Y/CbCr ER 4:2:0 10-bit multi-planar.)pyds";
            constexpr const char* NVBUF_COLOR_FORMAT_NV12_10LE_2020 =R"pyds(BT.2020 colorspace - Y/CbCr 4:2:0 10-bit multi-planar.)pyds";
            constexpr const char* NVBUF_COLOR_FORMAT_SIGNED_R16G16 =R"pyds(Color format for packed 2 signed shorts.)pyds";
            /* not in bind functions?
            constexpr const char* NVBUF_COLOR_FORMAT_R8_G8_B8 =R"pyds(RGB- unsigned 8 bit multiplanar plane.)pyds";
            constexpr const char* NVBUF_COLOR_FORMAT_B8_G8_R8 =R"pyds(BGR- unsigned 8 bit multiplanar plane.)pyds";
            constexpr const char* NVBUF_COLOR_FORMAT_R32F_G32F_B32F =R"pyds(RGB-32bit Floating point multiplanar plane.)pyds";
            constexpr const char* NVBUF_COLOR_FORMAT_B32F_G32F_R32F =R"pyds(BGR-32bit Floating point multiplanar plane.)pyds";
            constexpr const char*  NVBUF_COLOR_FORMAT_YUV422 =R"pyds(BT.601 colorspace - YUV422 multi-planar.)pyds";
            */
            constexpr const char* NVBUF_COLOR_FORMAT_LAST =R"pyds(NVBUF_COLOR_FORMAT_LAST)pyds";
        }

        namespace NvBufSurfaceLayoutDoc
        {
            constexpr const char* descr = R"pyds(*Enumerator*. Specifies layout formats for :class:`NvBufSurface` video planes.)pyds";
            constexpr const char* NVBUF_LAYOUT_PITCH =R"pyds(Pitch Layout.)pyds";
            constexpr const char* NVBUF_LAYOUT_BLOCK_LINEAR =R"pyds(Block Linear Layout.)pyds";
        }

        namespace NvBufSurfaceMemTypeDoc
        {
            constexpr const char* descr = R"pyds(
                *Enumerator*. Specifies the default memory type, i.e. NVBUF_MEM_CUDA_DEVICE for dGPU, NVBUF_MEM_SURFACE_ARRAY for Jetson.
                Use NVBUF_MEM_DEFAULT to allocate whichever type of memory is appropriate for the platform.)pyds";
            constexpr const char* NVBUF_MEM_DEFAULT =R"pyds(NVBUF_MEM_CUDA_DEVICE type for dGpu and NVBUF_MEM_SURFACE_ARRAY type for Jetson.)pyds";
            constexpr const char* NVBUF_MEM_CUDA_PINNED =R"pyds(CUDA Host memory type.)pyds";
            constexpr const char* NVBUF_MEM_CUDA_DEVICE =R"pyds(CUDA Device memory type.)pyds";
            constexpr const char* NVBUF_MEM_CUDA_UNIFIED =R"pyds(CUDA Unified memory type.)pyds";
            constexpr const char* NVBUF_MEM_SURFACE_ARRAY =R"pyds(NVRM Surface Array type - valid only for Jetson.)pyds";
            constexpr const char* NVBUF_MEM_HANDLE =R"pyds(NVRM Handle type - valid only for Jetson.)pyds";
            constexpr const char* NVBUF_MEM_SYSTEM =R"pyds(Memory allocated by malloc().)pyds";
        }

       namespace NvBufSurfacePlaneParamsDoc
        {
            constexpr const char* descr =R"pyds(
                Holds the planewise parameters of a buffer.

                :ivar num_planes: *int*, Holds the number of planes.
                :ivar width: *list of int*, Holds the widths of planes.
                :ivar height: *list of int*, Holds the heights of planes.
                :ivar pitch: *list of int*, Holds the pitches of planes.
                :ivar offset: *list of int*, Holds the offsets of planes.
                :ivar psize: *list of int*, Holds the sizes of planes.
                :ivar bytesPerPix: *list of int*, Holds the number of bytes occupied by a pixel in each plane.)pyds";

            constexpr const char* cast=R"pyds(cast given object/data to :class:`NvBufSurfacePlaneParams`, call pyds.NvBufSurfacePlaneParams.cast(data))pyds";
        }

        namespace NvBufSurfaceCreateParamsDocs
        {
            constexpr const char* descr =R"pyds(
                Holds parameters required to allocate an :class:`NvBufSurface`.
                
                :ivar gpuId: *int*, Holds the GPU ID. Valid only for a multi-GPU system.
                :ivar width: *int*, Holds the width of the buffer.
                :ivar height: *int*, Holds the height of the buffer.
                :ivar size: *int*, Holds the amount of memory to be allocated.
                :ivar isContiguous: *bool*, Holds a "contiguous memory" flag. If set, contiguous memory is allocated for the batch. Valid only for CUDA memory types.
                :ivar colorFormat: :class:`NvBufSurfaceColorFormat`, Holds the color format of the buffer.
                :ivar layout: :class:`NvBufSurfaceLayout`, Holds the surface layout. May be Block Linear (BL) or Pitch Linear (PL).
                :ivar memType: :class:`NvBufSurfaceMemType`, Holds the type of memory to be allocated.)pyds";

            constexpr const char* cast=R"pyds(cast given object/data to :class:`NvBufSurfaceCreateParams`, call pyds.NvBufSurfaceCreateParams.cast(data))pyds";
        }
   
        namespace NvBufSurfaceMappedAddrDoc
        {
            constexpr const char* descr =R"pyds(
                Holds objects for a mapped buffer.

                :ivar addr: Array for a planewise CPU mapped buffer.
                :ivar eglImage: An object for a mapped EGLImage.)pyds";

            constexpr const char* cast=R"pyds(cast given object/data to :class:`NvBufSurfaceMappedAddr`, call pyds.NvBufSurfaceMappedAddr.cast(data))pyds";
        }

        namespace NvBufSurfaceParamsDoc
        {
            constexpr const char* descr =R"pyds(
                Holds information about a single buffer in a batch.

                :ivar width: *int*, Holds the width of the buffer.
                :ivar height: *int*, Holds the height of the buffer.
                :ivar pitch: *int*, Holds the pitch of the buffer.
                :ivar colorFormat: :class:`NvBufSurfaceColorFormat`, Holds the color format of the buffer.
                :ivar layout: :class:`NvBufSurfaceLayout`, Holds the surface layout (PL or GL). For dGPU,, only PL is valid.
                :ivar bufferDesc: *int*, Holds a DMABUF FD. Valid only for NVBUF_MEM_SURFACE_ARRAY and NVBUF_MEM_HANDLE type memory.
                :ivar dataSize: *int*, Holds the amount of allocated memory.
                :ivar dataPtr: Allocated memory. Not valid for NVBUF_MEM_SURFACE_ARRAY or NVBUF_MEM_HANDLE.
                :ivar planeParams: :class:`NvBufSurfacePlaneParams`, Holds planewise information (width, height, pitch, offset, etc.).
                :ivar mappedAddr: :class:`NvBufSurfaceMappedAddr`, Holds mapped buffers. Initialized to None when the structure is created.)pyds";

            constexpr const char* cast=R"pyds(cast given object/data to :class:`NvBufSurfaceParams`, call pyds.NvBufSurfaceParams.cast(data))pyds";
        }

        namespace NvBufSurfaceDoc
        {
            constexpr const char* descr =R"pyds(
                Holds information about a single buffer in a batch.

                :ivar gpuId: *int*, Holds the GPU ID. Valid only for a multi-GPU system.
                :ivar batchSize: *int*, Holds the batch size.
                :ivar numFilled: *int*, Holds the number valid and filled buffers. Initialized to zero when an instance of the structure is created.
                :ivar isContiguous: *bool*, Holds an "is contiguous" flag. If set, memory allocated for the batch is contiguous.
                :ivar memType: :class:`NvBufSurfaceMemType`, Holds type of memory for buffers in the batch.
                :ivar surfaceList: *list of :class:`NvBufSurfaceParams`*, Array of batched buffers.)pyds";

            constexpr const char* cast=R"pyds(cast given object/data to :class:`NvBufSurface`, call pyds.NvBufSurface.cast(data))pyds";
        }
    }

    namespace NvInferDoc
    {
        namespace NvdsInferDimsDoc
        {
            constexpr const char* descr = R"pyds(
                Specifies dimensions of a layer.

                :ivar numDims: *int*, Number of dimesions of the layer.
                :ivar numElements: *int*, Number of elements in the layer including all dimensions.
                :ivar d: *np.array of int*, Size of the layer in each dimension.)pyds";

            constexpr const char* cast=R"pyds(cast given object/data to :class:`NvDsInferDims`, call pyds.NvDsInferDims.cast(data))pyds";
        }

        namespace  NvDsInferDimsCHWDoc
        {    
            constexpr const char* descr = R"pyds(
                Holds the dimensions of a three-dimensional layer.

                :ivar c: *int*, Channel count of the layer.
                :ivar h: *int*, Height of the layer.
                :ivar w: *int*, Width of the layer.)pyds";

            constexpr const char* cast=R"pyds(cast given object/data to :class:`NvDsInferDimsCHW`, call pyds.NvDsInferDimsCHW.cast(data))pyds";
        }

        namespace  NvDsInferDataTypeDoc
        {
            constexpr const char* descr = R"pyds(*Enumerator*, Specifies the data type of a layer.)pyds";
            constexpr const char* FLOAT =R"pyds(FP32 format.)pyds";
            constexpr const char* HALF=R"pyds(FP16 format.)pyds";
            constexpr const char* INT8 =R"pyds(INT8 format.)pyds";
            constexpr const char* INT32 =R"pyds(INT32 format.)pyds";
        }

        namespace  NvDsInferLayerInfoDoc
        {
            constexpr const char* descr = R"pyds(
                Holds information about one layer in the model.

                :ivar dataType: :class:`NvDsInferDataType`, Data type of the layer.
                :ivar dims: :class:`NvDsInferDims`, Dimensions of the layer. WARNING: to be deprecated, please change all usage to "inferDims".
                :ivar inferDims: :class:`NvDsInferDims`, Dimensions of the layer.
                :ivar bindingIndex: *int*, TensorRT binding index of the layer.
                :ivar layerName: *str*, Name of the layer.
                :ivar buffer: Buffer for the layer data.
                :ivar isInput: *int*, Holds a Boolean; true if the layer is an input layer, or false (0) if an output layer.)pyds";

            constexpr const char* cast=R"pyds(cast given object/data to :class:`NvDsInferLayerInfo`, call pyds.NvDsInferLayerInfo.cast(data))pyds";
        }

        namespace  NvDsInferNetworkInfoDoc
        {
            constexpr const char* descr = R"pyds(
                Holds information about the model network.

                :ivar width: *int*, Input width for the model.
                :ivar height: *int*, Input height for the model.
                :ivar channels: *int*, Number of input channels for the model.)pyds";

            constexpr const char* cast=R"pyds(cast given object/data to :class:`NvDsInferNetworkInfo`, call pyds.NvDsInferNetworkInfo.cast(data))pyds";
        }

        namespace  NvDsInferObjectDetectionInfoDoc
        {
            constexpr const char* descr = R"pyds(
                Holds information about one parsed object from detector's output.

                :ivar classId: *int*, ID of the class to which the object belongs.
                :ivar left: *float*, Horizontal offset of the bounding box shape for the object.
                :ivar top: *float*, Vertical offset of the bounding box shape for the object.
                :ivar width: *float*, Width of the bounding box shape for the object.
                :ivar height: *float*, Height of the bounding box shape for the object.
                :ivar detectionConfidence: *float*, Object detection confidence. Should be a float value in the range [0.0,1.0].)pyds";

            constexpr const char* cast=R"pyds(cast given object/data to :class:`NvDsInferObjectDetectionInfo`, call pyds.NvDsInferObjectDetectionInfo.cast(data))pyds";
        }

        namespace NvDsInferAttributeDoc
        {
            constexpr const char* descr = R"pyds(
                Holds information about one classified attribute.
                
                :ivar atttributeIndex: *int*, Index of the label. This index corresponds to the order of output layers specified in the outputCoverageLayerNames vector during initialization. WARNING: misspelling to be deprecated, please change all usage to "attributeIndex".
                :ivar attributeIndex: *int*, Index of the label. This index corresponds to the order of output layers specified in the outputCoverageLayerNames vector during initialization.
                :ivar attributeValue: *int*, Output for the label.
                :ivar attributeConfidence: *float*, Confidence level for the classified attribute.
                :ivar attributeLabel: *str*, String label for the attribute. Memory for the string should not be freed.)pyds";

            constexpr const char* cast=R"pyds(cast given object/data to :class:`NvDsInferAttribute`, call pyds.NvDsInferAttribute.cast(data))pyds";
        }

        namespace  NvDsInferTensorMetaDoc
        {
            constexpr const char* descr = R"pyds(
                Holds the raw tensor output information for one frame / one object.
                The "nvinfer" plugins adds this meta when the "output-tensor-meta" property  of the element instance is set to TRUE.
                This meta data is added as NvDsUserMeta to the frame_user_meta_list of the
                corresponding frame_meta or object_user_meta_list of the corresponding object
                with the meta_type set to NVDSINFER_TENSOR_OUTPUT_META.

                :ivar unique_id: *int*, Unique ID of the gst-nvinfer instance which attached this meta.
                :ivar num_output_layers: *int*, Number of bound output layers.
                :ivar out_buf_ptrs_host: Array of output host buffers for the frame / object.
                :ivar out_buf_ptrs_dev: Array of output device buffers for the frame / object.
                :ivar gpu_id: *int*, GPU device ID on which the device buffers have been allocated.
                :ivar priv_data: Private data used for the meta producer's internal memory management.)pyds";

            constexpr const char* output_layers_info =R"pyds(Retrieve the :class:`NvDsInferLayerInfo` object of layer at index j.)pyds";
            constexpr const char* cast=R"pyds(cast given object/data to :class:`NvDsInferTensorMeta`, call pyds.NvDsInferTensorMeta.cast(data))pyds";
        }

        namespace  NvDsInferSegmentationMetaDoc
        {
            constexpr const char* descr = R"pyds(
                Holds the segmentation model output information for one frame / one object.
                The "nvinfer" plugins adds this meta for segmentation models.
                This meta data is added as NvDsUserMeta to the frame_user_meta_list of the
                corresponding frame_meta or object_user_meta_list of the corresponding object
                with the meta_type set to NVDSINFER_SEGMENTATION_META. Get mask data using :py:func:`get_segmentation_masks`.

                :ivar classes: *int*, Number of classes in the segmentation output.
                :ivar width: *int*, Width of the segmentation output class map.
                :ivar height: *int*, Height of the segmentation output class map.
                :ivar class_map: Array for 2D pixel class map. The output for pixel (x,y)  will be at index (y * width + x).
                :ivar class_probabilities_map: The raw array containing the probabilities. The probability for class c and pixel (x,y) will be at index (c * width * height + y * width + x).
                :ivar priv_data: Private data used for the meta producer's internal memory management.

                Example usage:
                ::

                    def map_mask_as_display_bgr(mask):
                        """ Assigning multiple colors as image output using the information
                            contained in mask. (BGR is opencv standard.)
                        """
                        # getting a list of available classes
                        m_list = list(set(mask.flatten()))

                        shp = mask.shape
                        bgr = np.zeros((shp[0], shp[1], 3))
                        for idx in m_list:
                            bgr[mask == idx] = COLORS[idx]
                        return bgr

                    ...

                    l_user = frame_meta.frame_user_meta_list #Get glist containing NvDsUserMeta objects from given NvDsFrameMeta
                    while l_user is not None:
                        try:
                            # Note that l_user.data needs a cast to pyds.NvDsUserMeta
                            # The casting is done by pyds.NvDsUserMeta.cast()
                            # The casting also keeps ownership of the underlying memory
                            # in the C code, so the Python garbage collector will leave
                            # it alone.
                            seg_user_meta = pyds.NvDsUserMeta.cast(l_user.data)
                        except StopIteration:
                            break
                        if seg_user_meta and seg_user_meta.base_meta.meta_type == \
                            pyds.NVDSINFER_SEGMENTATION_META:
                            try:
                                # Note that seg_user_meta.user_meta_data needs a cast to
                                # pyds.NvDsInferSegmentationMeta
                                # The casting is done by pyds.NvDsInferSegmentationMeta.cast()
                                # The casting also keeps ownership of the underlying memory
                                # in the C code, so the Python garbage collector will leave
                                # it alone.
                                segmeta = pyds.NvDsInferSegmentationMeta.cast(seg_user_meta.user_meta_data)
                            except StopIteration:
                                break
                            # Retrieve mask data in the numpy format from segmeta
                            # Note that pyds.get_segmentation_masks() expects object of
                            # type NvDsInferSegmentationMeta
                            masks = pyds.get_segmentation_masks(segmeta)
                            masks = np.array(masks, copy=True, order='C')
                            # map the obtained masks to colors of 2 classes.
                            frame_image = map_mask_as_display_bgr(masks)
                            cv2.imwrite(folder_name + "/" + str(frame_number) + ".jpg", frame_image)
                        try:
                            l_user = l_user.next
                        except StopIteration:
                            break)pyds";

            constexpr const char* cast=R"pyds(cast given object/data to :class:`NvDsInferSegmentationMeta`, call pyds.NvDsInferSegmentationMeta.cast(data))pyds";
        }
    }

	namespace methodsDoc
	{
        constexpr const char* get_segmentation_masks=R"pyds(
            This function returns the inferred masks in Numpy format in the height X width shape, these height and width are obtained from the :class:`NvDsInferSegmentationMeta`.

            :arg data: An object of type :class:`NvDsInferSegmentationMeta`)pyds";

        constexpr const char* get_optical_flow_vectors=R"pyds(
            :arg of_meta: An object of type :class:`NvDsOpticalFlowMeta`

            :returns: Interleaved x, y directed optical flow vectors for a block of pixels in numpy format with shape (rows,cols,2), where rows and cols are the Optical flow outputs. These rows and cols are not equivalent to input resolution.)pyds";

        constexpr const char* get_nvds_buf_surface=R"pyds(
            This function returns the frame in NumPy format. Only RGBA format is supported. For x86_64, only unified memory is supported. For Jetson, the buffer is mapped to CPU memory. Changes to the frame image will be preserved and seen in downstream elements, with the following restrictions.
            1. No change to image color format or resolution
            2. No transpose operation on the array.

            :arg gst_buffer: address of the Gstbuffer which contains `NvBufSurface`
            :arg batchID: batch_id of the frame to be processed. This indicates the frame's index within `NvBufSurface`)pyds";

        constexpr const char* nvds_acquire_meta_lock=R"pyds(
            Acquire the lock before updating metadata.

            :arg batch_meta: An object of type :class:`NvDsBatchMeta`)pyds";

        constexpr const char* nvds_release_meta_lock=R"pyds(
            Release lock after updating metadata.

            :arg batch_meta: An object of type :class:`NvDsBatchMeta`)pyds";

        constexpr const char* nvds_create_batch_meta=R"pyds(
            Creates a :class:`NvDsBatchMeta` of given batch size.

            :arg max_batch_size: maximum number of frames those can be present in the batch
            :returns: Allocated :class:`NvDsBatchMeta` object)pyds";

        constexpr const char* nvds_destroy_batch_meta=R"pyds(
            Deletes/Releases given :class:`NvDsBatchMeta` batch_meta object.

            :arg batch_meta: An object of type :class:`NvDsBatchMeta` to be deleted/destroyed after use)pyds";

        constexpr const char* nvds_acquire_frame_meta_from_pool=R"pyds(
            Acquires :class:`NvDsFrameMeta` from frame_meta pool. User must acquire the frame_meta from frame_meta pool to fill frame metadata.

            :arg batch_meta: An object of type :class:`NvDsBatchMeta` from which :class:`NvDsFrameMeta` will be acquired

            :returns: Acquired :class:`NvDsFrameMeta` object from frame meta pool)pyds";

        constexpr const char* nvds_add_frame_meta_to_batch=R"pyds(
            After acquiring and filling frame metadata, user must add it to the batch metadata with this API.

            :arg batch_meta: An object of type :class:`NvDsBatchMeta` to which frame_meta will be attached.
            :arg frame_meta: An object of type :class:`NvDsFrameMeta` acquired from frame_meta_pool present in :class:`NvDsBatchMeta`)pyds";

        constexpr const char* nvds_remove_frame_meta_from_batch=R"pyds(
            Removes given frame meta from the batch metadata.

            :arg batch_meta: An object of type :class:`NvDsBatchMeta` from which frame_meta is to be removed.
            :arg frame_meta: A object of type :class:`NvDsFrameMeta` to be removed from batch_meta.)pyds";

        constexpr const char* nvds_acquire_obj_meta_from_pool=R"pyds(
            Acquires :class:`NvDsObjectMeta` from the object meta pool. User must acquire the object meta from the object meta pool to fill object metadata.

            :arg batch_meta: An object of type :class:`NvDsBatchMeta` from which :class:`NvDsObjectMeta` will be acquired

            :returns: Acquired :class:`NvDsObjectMeta` object from object meta pool)pyds";

        constexpr const char* nvds_add_obj_meta_to_frame =R"pyds(
            After acquiring and filling object metadata user must add it to the frame metadata with this API.

            :arg frame_meta: An object of type :class:`NvDsFrameMeta` to which obj_meta will be attached.
            :arg obj_meta: An object of type :class:`NvDsObjectMeta` acquired from obj_meta_pool present in :class:`NvDsBatchMeta`.
            :arg obj_parent: A parent object of type :class:`NvDsObjectMeta`. This will set the parent object's to obj_meta.)pyds";  

        constexpr const char* nvds_remove_obj_meta_from_frame=R"pyds(
            Removes given object meta from the frame metadata.

            :arg frame_meta: An object of type :class:`NvDsFrameMeta` from which obj_meta is to be removed.
            :arg obj_meta: An object of type :class:`NvDsObjectMeta` to be removed from frame_meta.)pyds";

        constexpr const char*  nvds_acquire_classifier_meta_from_pool=R"pyds(
            Acquires :class:`NvDsClassifierMeta` from the classifier meta pool. User must acquire the classifier meta from the classifier meta pool to fill classifier metadata.

            :arg batch_meta: An object of type :class:`NvDsBatchMeta` from which :class:`NvDsClassifierMeta` will be acquired

            :returns: Acquired :class:`NvDsClassifierMeta` object from classifier meta pool)pyds";

        constexpr const char* nvds_add_classifier_meta_to_object=R"pyds(
            After acquiring and filling classifier metadata user must add it to the object metadata with this API.

            :arg obj_meta: An object of type :class:`NvDsObjectMeta` to which classifier_meta will be attached.
            :arg classifier_meta: An object of type :class:`NvDsClassifierMeta` acquired from classifier_meta_pool present in :class:`NvDsBatchMeta`.)pyds";

        constexpr const char* nvds_remove_classifier_meta_from_obj1=R"pyds(
            Removes given classifier meta from object metadata.

            :arg obj_meta: An object of type :class:`NvDsObjectMeta` from which classifier_meta is to be removed.
            :arg classifier_meta: An object of type :class:`NvDsClassifierMeta` to be removed from obj_meta.)pyds";

        constexpr const char* nvds_acquire_display_meta_from_pool=R"pyds(
            Acquires NvDsDisplayMeta from the display meta pool. User must acquire the display meta from the display meta pool to fill display metadata.

            :arg batch_meta: An object of type :class:`NvDsBatchMeta` from which :class:`NvDsDisplayMeta` will be acquired.

            :returns: Acquired :class:`NvDsDisplayMeta` object from display meta pool)pyds";

        constexpr const char* nvds_add_display_meta_to_frame=R"pyds(
            After acquiring and filling classifier metadata user must add it to the frame metadata with this API.

            :arg frame_meta: An object of type :class:`NvDsFrameMeta` to which display_meta will be attached.
            :arg display_meta: An object of type :class:`NvDsDisplayMeta` acquired from display_meta_pool present in :class:`NvDsBatchMeta`.)pyds";

        constexpr const char* nvds_remove_display_meta_from_frame=R"pyds(
            Removes given display meta from frame metadata.

            :arg frame_meta: An object of type :class:`NvDsFrameMeta` from which display_meta is to be removed.
            :arg display_meta: An object of type :class:`NvDsDisplayMeta` to be removed from frame_meta.)pyds";

        constexpr const char* nvds_acquire_label_info_meta_from_pool=R"pyds(
            Acquires :class:`NvDsLabelInfo` from the labelinfo meta pool of given :class:`NvDsBatchMeta`. User must acquire the labelinfo meta from the labelinfo meta pool to fill labelinfo metadata.

            :arg batch_meta: An object of type :class:`NvDsBatchMeta` from which :class:`NvDsLabelInfo` will be acquired

            :returns: An object of type :class:`NvDsLabelInfo` object from label info meta pool)pyds";

        constexpr const char* nvds_add_label_info_meta_to_classifier=R"pyds(
            After acquiring and filling labelinfo metadata user must add it to the classifier metadata with this API.

            :arg classifier_meta: An object of type :class:`NvDsClassifierMeta` to which label_info_meta will be attached.
            :arg label_info_meta: An object of type :class:`NvDsLabelInfo` acquired from label_info_meta_pool present in :class:`NvDsBatchMeta`.)pyds";

        constexpr const char* nvds_remove_label_info_meta_from_classifier=R"pyds(
            Removes given labelinfo meta from the classifier metadata

            :arg classifier_meta: An object of type :class:`NvDsClassifierMeta` from which label_info_meta is to be removed.
            :arg label_info_meta: An object of type :class:`NvDsLabelInfo` to be removed from classifier_meta.)pyds";

        constexpr const char* nvds_add_user_meta_to_batch=R"pyds(
            After acquiring and filling user metadata user must add it to batch metadata if required at batch level with this API.

            :arg batch_meta: An object of type :class:`NvDsBatchMeta` to which user_meta will be attached.
            :arg user_meta: An object of type :class:`NvDsUserMeta` acquired from user_meta_pool present in :class:`NvDsBatchMeta`.)pyds";

        constexpr const char* nvds_add_user_meta_to_frame=R"pyds(
            After acquiring and filling user metadata user must add it to frame metadata if required at frame level with this API.

            :arg frame_meta: An object of type :class:`NvDsFrameMeta` to which user_meta will be attached.
            :arg user_meta: An object of type :class:`NvDsUserMeta` acquired from user_meta_pool present in :class:`NvDsBatchMeta`.)pyds";

        constexpr const char* nvds_add_user_meta_to_obj=R"pyds(
            After acquiring and filling user metadata user must add it to object metadata if required at object level with this API.

            :arg obj_meta: An object of type :class:`NvDsObjectMeta` to which user_meta will be attached.
            :arg user_meta: An object of type :class:`NvDsUserMeta` acquired from user_meta_pool present :class:`NvDsBatchMeta`.)pyds";

        constexpr const char* nvds_acquire_user_meta_from_pool=R"pyds(
            Acquires NvDsUserMeta from the user meta pool. User must acquire the user meta from the user meta pool to fill user metadata.

            :arg batch_meta: An object of type :class:`NvDsBatchMeta` from which :class:`NvDsUserMeta` will be acquired)pyds";

        constexpr const char* nvds_remove_user_meta_from_batch=R"pyds(
            Removes given user metadata from the batch metadata.

            :arg batch_meta: An object of type :class:`NvDsBatchMeta` from which user_meta is to be removed.
            :arg user_meta: An object of type :class:`NvDsUserMeta` to be removed from batch_meta.
        
            :returns: Acquired :class:`NvDsUserMeta` object from user meta pool)pyds";

        constexpr const char* nvds_remove_user_meta_from_frame=R"pyds(
            Removes given user metadata from the frame metadata.

            :arg frame_meta: An object of type :class:`NvDsFrameMeta` from which user_meta is to be removed.
            :arg user_meta: An object of type :class:`NvDsUserMeta` to be removed from frame_meta.)pyds";

        constexpr const char* nvds_remove_user_meta_from_object=R"pyds(
            Removes given user metadata from the object metadata.

            :arg obj_meta: An object of type :class:`NvDsObjectMeta` from which user_meta s to be removed.
            :arg user_meta: An object of type :class:`NvDsUserMeta` to be removed from obj_meta.)pyds";

        constexpr const char* nvds_get_current_metadata_info=R"pyds(
            Debug function to get current metadata info.

            :arg batch_meta: An object of type :class:`NvDsBatchMeta`)pyds";

        constexpr const char* nvds_batch_meta_copy_func=R"pyds(
            Copy function to copy batch_meta. It is called when meta_data needs to copied / transformed from one buffer to other.
            meta_data and user_data are passed as arguments.

            :arg data: An object of type :class:`NvDsBatchMeta` 
            :arg user_data: An object of user specific data

            :returns: An object that can be typecasted tot :class:`NvDsBatchMeta`)pyds";

        constexpr const char* nvds_batch_meta_release_func=R"pyds(
            batch_meta release function called when meta_data is going to be released.

            :arg data: An object of type :class:`NvDsBatchMeta` 
            :arg user_data: An object of user specific data)pyds";

        constexpr const char* nvds_get_nth_frame_meta=R"pyds(
            Retrieve the :class:`NvDsFrameMeta` object of the frame at index.

            :arg frame_meta_list: A list of objects of type :class:`NvDsFrameMeta`
            :arg index: index at which :class:`NvDsFrameMeta` object needs to be accessed.

            :returns:  An object of type :class:`NvDsFrameMeta` from frame_meta_list)pyds";

        constexpr const char* nvds_clear_frame_meta_list=R"pyds(
            Removes all the frame metadata present in the batch metadata.

            :arg batch_meta: An object type of :class:`NvDsBatchMeta` from which :class:`NvDsFrameMetaList` needs to be cleared
            :arg  meta_list: An object of type :class:`NvDsFrameMetaList` which needs to be cleared)pyds";

        constexpr const char* nvds_clear_obj_meta_list=R"pyds(
            Removes all the object metadata present in the frame metadata.

            :arg frame_meta: An object of type :class:`NvDsFrameMeta` from which :class:`NvDsObjectMetaList` needs to be cleared
            :arg meta_list: An object of type :class:`NvDsObjectMetaList` which needs to be cleared)pyds";
    
        constexpr const char* nvds_clear_display_meta_list=R"pyds(
            Removes all the display metadata present in the frame metadata.

            :arg frame_meta: An object of type :class:`NvDsFrameMeta` from which :class:`NvDisplayMetaList` needs to be cleared
            :arg meta_list: An object of type :class:`NvDisplayMetaList` which needs to be cleared)pyds";

        constexpr const char* nvds_clear_batch_user_meta_list=R"pyds(
            Removes all the user metadata present in the batch metadata

            :arg batch_meta: An object of type :class:`NvDsBatchMeta` from which :class:`NvDsUserMetaList` needs to be cleared
            :arg meta_list: An object of type :class:`NvDsUserMetaList` which needs to be cleared)pyds";

        constexpr const char* nvds_clear_frame_user_meta_list=R"pyds(
            Removes all the user metadata present in the frame metadata

            :arg frame_meta: An object of type :class:`NvDsFrameMeta` from which :class:`NvDsUserMetaList` needs to be cleared
            :arg meta_list: An object of type :class:`NvDsUserMetaList` which needs to be cleared)pyds";

        constexpr const char* nvds_clear_obj_user_meta_list=R"pyds(
            Removes all the user metadata present in the object metadata

            :arg object_meta: An object of type :class:`NvDsObjectMeta` from which :class:`NvDsUserMetaList` needs to be cleared
            :arg meta_list: An object of type :class:`NvDsUserMetaList` which needs to be cleared)pyds";

        constexpr const char* nvds_clear_meta_list=R"pyds(
            Removes all the metadata elements present in the given metadata list

            :arg batch_meta: An object of type :class:`NvDsBatchMeta`
            :arg meta_list: An object of type :class:`NvDsMetaList` which needs to be cleared
            :arg meta_pool: An object of type :class:`NvDsMetaPool` to which list belongs to

            :returns: An object of updated meta list)pyds";

        constexpr const char* nvds_copy_batch_user_meta_list=R"pyds(
            Deep copy of src_user_meta_list to user meta list present in the dst_batch_meta.

            :arg src_user_meta_list: An obect of type :class:`NvDsUserMetaList`
            :arg dst_batch_meta: An object of type :class:`NvDsBatchMeta`)pyds";

        constexpr const char* nvds_copy_frame_user_meta_list=R"pyds(
            Deep copy of src_user_meta_list to user meta list present in the dst_frame_meta.
        
            :arg src_user_meta_list: An object of type :class:`NvDsUserMetaList`
            :arg dst_frame_meta: An object of type :class:`NvDsFrameMeta`)pyds";

        constexpr const char* nvds_copy_display_meta_list=R"pyds(
            Deep copy of src_display_meta_list to display meta list present in the dst_frame_meta.
        
            :arg src_display_meta_list: An object of type :class:`NvDisplayMetaList`
            :arg dst_frame_meta: An object of type :class:`NvDsFrameMeta`)pyds";

        constexpr const char* nvds_copy_frame_meta_list=R"pyds(
            Deep copy of src_frame_meta_list to frame meta list present in the dst_batch_meta.
        
            :arg src_frame_meta_list: An object of type :class:`NvDsFrameMetaList`
            :arg dst_batch_meta: An object of type :class:`NvDsBatchMeta`)pyds";

        constexpr const char* nvds_copy_obj_meta_list=R"pyds(
            Deep copy of src_obj_meta_list to frame meta list present in the dst_frame_meta.
        
            :arg src_obj_meta_list: An object of type :class:`NvDsObjectMetaList`
            :arg dst_frame_meta: An object of type :class:`NvDsFrameMeta`)pyds";

        constexpr const char* nvds_get_user_meta_type1=R"pyds(
            Generates a unique user metadata type from the given string describing user specific metadata.
        
            :arg meta_descriptor: A string object describing metadata. 
            The format of the string should be specified as below:
                ORG_NAME.COMPONENT_NAME.METADATA_DESCRIPTION.

                e.g. (NVIDIA.NVINFER.TENSOR_METADATA))pyds";

        constexpr const char* nvds_copy_obj_meta_list1=R"pyds(
            Deep copy of src_obj_meta_list to frame meta list present in the dst_frame_meta.

            :arg src_obj_meta_list: An object of type :class:`NvDsObjectMetaList`
            :arg dst_frame_meta: An object of type :class:`NvDsFrameMeta`)pyds";

        constexpr const char* nvds_get_user_meta_type=R"pyds(
            Generates a unique user metadata type from the given string describing user specific metadata.

            :arg meta_descriptor: A string object describing metadata.
            The format of the string should be specified as below
                ORG_NAME.COMPONENT_NAME.METADATA_DESCRIPTION.

                e.g. (NVIDIA.NVINFER.TENSOR_METADATA))pyds";

        constexpr const char* gst_buffer_add_nvds_meta=R"pyds( 
            Adds GstMeta of type :class:`NvDsMeta` to the GstBuffer and sets the `meta_data` member of :class:`NvDsMeta`.

            :arg buffer: GstBuffer to which the function adds metadata.
            :arg meta_data: The object to which the function sets the meta_data member of :class:`NvDsMeta`.
            :arg user_data: A user specific data object
            :arg copy_func: The NvDsMetaCopyFunc function to be called when NvDsMeta is to be copied. The function is called with meta_data and user_data as parameters. NvDsMeta is to be destroyed. The function is called with meta_data and user_data as parameters.

            :returns: An object to the attached :class:`NvDsMeta` object; or NONE in case failure)pyds";

        constexpr const char* gst_buffer_get_nvds_batch_meta=R"pyds( 
            Gets the :class:`NvDsBatchMeta` added to the GstBuffer.

            :arg buffer: GstBuffer from which to retrieve the :class:`NvDsBatchMeta`

            :returns: :class:`NvDsBatchMeta` object retrieved from the buffer

            For example:
            ``batch_meta = pyds.gst_buffer_get_nvds_batch_meta(hash(gst_buffer))``)pyds";

        constexpr const char* user_copyfunc=R"pyds( 
            Set copy callback function of given :class:`NvDsUserMeta` object.

            :arg meta: :class:`NvDsUserMeta` of which to set copy function
            :arg func: User-written copy function)pyds";

        constexpr const char* user_releasefunc=R"pyds( 
            Set release callback function of given :class:`NvDsUserMeta` object.

            :arg meta: :class:`NvDsUserMeta` of which to set release function
            :arg func: User-written release function)pyds";

        constexpr const char* alloc_buffer=R"pyds( 
            Allocate buffer of given size. 

            :arg size: Size of memory to be allocated

            :returns: C address of allocated buffer)pyds";

        constexpr const char* free_buffer=R"pyds( 
            Frees memory of given buffer.

            :arg buffer: C address of the buffer to be freed)pyds";

        constexpr const char* free_gbuffer=R"pyds( 
            Frees memory of given gbuffer.

            :arg buffer: gpointer to the buffer to be freed)pyds";

        constexpr const char* get_string=R"pyds( 
            Cast given pointer to string. 

            :arg ptr: C address of the string

            :returns: Reference to the string object)pyds";

        constexpr const char* get_ptr=R"pyds( 
            Gets the C address of given object.

            :arg ptr: Object of which to retrieve C address "pointer"

            :returns: C address of given data)pyds";

        constexpr const char* memdup=R"pyds( 
            Allocate memory and duplicate given object into it. 

            :arg ptr: C address of object to duplicate. See :py:func:`get_ptr`
            :arg size: Size of object to duplicate

            :returns: C address of allocated duplicate)pyds";

        constexpr const char* alloc_nvds_vehicle_object=R"pyds( 
            Allocate an :class:`NvDsVehicleObject`. 

            :returns: Allocated :class:`NvDsVehicleObject`)pyds";

        constexpr const char* alloc_nvds_person_object=R"pyds( 
            Allocate an :class:`NvDsPersonObject`. 

            :returns: Allocated :class:`NvDsPersonObject`)pyds";

        constexpr const char* alloc_nvds_face_object=R"pyds( 
            Allocate an :class:`NvDsFaceObject`. 

            :returns: Allocated :class:`NvDsFaceObject`)pyds";

        constexpr const char* alloc_nvds_event_msg_meta=R"pyds( 
            Allocate an :class:`NvDsEventMsgMeta`. 

            :returns: Allocated :class:`NvDsEventMsgMeta`)pyds";

        constexpr const char* alloc_nvds_event=R"pyds( 
            Allocate an :class:`NvDsEvent`. 

            :returns: Allocated :class:`NvDsEvent`)pyds";

        constexpr const char* generate_ts_rfc3339=R"pyds( 
            Generate RFC3339 timestamp.

            :arg buffer: Buffer into which timestamp content is copied
            :arg size: Maximum timestamp length)pyds";

        constexpr const char* alloc_nvds_payload=R"pyds( 
            Allocate an :class:`NvDsPayload`. 

            :returns: Allocated :class:`NvDsPayload`)pyds";

        constexpr const char* NvBufSurfaceCreate=R"pyds(
            Allocate batch of buffers.
            
            Allocates memory for batchSize buffers and returns in surf object allocated :class:`NvBufSurface`.
            params object should have allocation parameters of single object. If size field in
            params is set, buffer of that size will be allocated and all other
            parameters (w, h, color format etc.) will be ignored.
            
            Use :py:func:`NvBufSurfaceDestroy` to free all the resources.
            
            :arg surf: pointer to allocated batched buffers.
            :arg batchSize: batch size of buffers.
            :arg params: pointer to :class:`NvBufSurfaceCreateParams` structure.
            
            :returns: 0 for success, -1 for failure.)pyds";

        constexpr const char* NvBufSurfaceDestroy=R"pyds(
            Free the batched buffers previously allocated through NvBufSurfaceCreate.
            
            :arg surf: An object to :class:`NvBufSurface` to free.
            
            :returns: 0 for success, -1 for failure.)pyds";

        constexpr const char* NvBufSurfaceMap=R"pyds(
            Map HW batched buffers to HOST CPU address space.
            
            Valid for NVBUF_MEM_CUDA_UNIFIED type of memory for dGPU and NVBUF_MEM_SURFACE_ARRAY and NVBUF_MEM_HANDLE type of memory for Jetson.
            
            This function will fill addr array of :class:`NvBufSurfaceMappedAddr` field of :class:`NvBufSurfaceParams` with the CPU mapped memory pointers.
            
            The client must call :py:func:`NvBufSurfaceSyncForCpu` with the virtual address populated by this function before accessing the mapped memory in CPU.
            
            After memory mapping is complete, mapped memory modification must be coordinated between the CPU and hardware device as follows:
                - CPU: If the CPU modifies any mapped memory, the client must call :py:func:`NvBufSurfaceSyncForDevice` before any hardware device accesses the memory.
                - Hardware device: If the mapped memory is modified by any hardware device, the client must call :py:func:`NvBufSurfaceSyncForCpu` before CPU accesses the memory.
            
            Use :py:func:`NvBufSurfaceUnMap` to unmap buffer(s) and release any resource.
            
            :arg surf: pointer to :class:`NvBufSurface` structure.
            :arg index: index of buffer in the batch. -1 for all buffers in batch.
            :arg plane: index of plane in buffer. -1 for all planes in buffer.
            :arg type: flag for mapping type.
            
            :returns: 0 for success, -1 for failure.)pyds";

        constexpr const char* NvBufSurfaceUnMap=R"pyds(
            Unmap the previously mapped buffer(s).
            
            :arg surf: pointer to :class:`NvBufSurface` structure.
            :arg index: index of buffer in the batch. -1 for all buffers in batch.
            :arg plane: index of plane in buffer. -1 for all planes in buffer.
            
            :returns: 0 for success, -1 for failure.)pyds";

        constexpr const char* NvBufSurfaceCopy=R"pyds(
            Copy the memory content of source batched buffer(s) to memory of destination batched buffer(s).
            
            This function can be used to copy source buffer(s) of one memory type
            to destination buffer(s) of different memory type.
            e.g. CUDA Host to CUDA Device or malloced memory to CUDA device etc.
            
            Both source and destination :class:`NvBufSurface` must have same buffer and batch size.
            
            :arg srcSurf: pointer to source :class:`NvBufSurface` structure.
            :arg dstSurf: pointer to destination :class:`NvBufSurface`  structure.
            
            :returns: 0 for success, -1 for failure.)pyds";

        constexpr const char* NvBufSurfaceSyncForCpu=R"pyds(
            Syncs the HW memory cache for the CPU.
            
            Valid only for NVBUF_MEM_SURFACE_ARRAY and NVBUF_MEM_HANDLE memory types.
            
            :arg surf: pointer to :class:`NvBufSurface` structure.
            :arg index: index of buffer in the batch. -1 for all buffers in batch.
            :arg plane: index of plane in buffer. -1 for all planes in buffer.
            
            :returns: 0 for success, -1 for failure.)pyds";

        constexpr const char* NvBufSurfaceSyncForDevice=R"pyds(
            Syncs the HW memory cache for the device.
            
            Valid only for NVBUF_MEM_SURFACE_ARRAY and NVBUF_MEM_HANDLE memory types.
            
            :arg surf: pointer to :class:`NvBufSurface` structure.
            :arg index: index of buffer in the batch. -1 for all buffers in batch.
            :arg plane: index of plane in buffer. -1 for all planes in buffer.
            
            :returns: 0 for success, -1 for failure.)pyds";

        constexpr const char* NvBufSurfaceFromFd=R"pyds(
            Get the :class:`NvBufSurface` from the dmabuf fd.
            
            :arg dmabuf_fd: dmabuf fd of the buffer.
            :arg buffer: pointer to :class:`NvBufSurface` .
            
            :returns: 0 for success, -1 for failure.)pyds";

        constexpr const char* NvBufSurfaceMemSet=R"pyds(
            Fill each byte of buffer(s) in :class:`NvBufSurface` with provided value.
            
            This function can also be used to reset the buffer(s) in the batch.
            
            :arg surf: pointer to :class:`NvBufSurface` structure.
            :arg index: index of buffer in the batch. -1 for all buffers in batch.
            :arg plane: index of plane in buffer. -1 for all planes in buffer.
            :arg value: value to be set.
            
            :returns: 0 for success, -1 for failure.)pyds";

        constexpr const char* NvBufSurfaceMapEglImage=R"pyds(
            Creates an EGLImage from memory of :class:`NvBufSurface` buffer(s).
            
            Only memory type NVBUF_MEM_SURFACE_ARRAY is supported.
            This function will set eglImage pointer of :class:`NvBufSurfaceMappedAddr` field of :class:`NvBufSurfaceParams` with EGLImageKHR.
            
            This function can be used in scenarios where CUDA operation on Jetson HW
            memory (NVBUF_MEM_SURFACE_ARRAY) is required. EGLImageKHR provided by this
            function can then be register with CUDA for further CUDA operations.
            
            :arg surf: pointer to NvBufSurface structure.
            :arg index: index of buffer in the batch. -1 for all buffers in batch.
            
            :returns: 0 for success, -1 for failure.)pyds";

        constexpr const char* gst_element_send_nvevent_new_stream_reset=R"pyds(
            Sends a "custom reset" event on the given element for the specified source.
            This nvevent_new_stream_reset event is propogated downstream.

            This function, along with other reset events, can be used to reset the source
            in case RTSP reconnection is required.

            :arg gst_element: element for to which the generated event needs to be sent.
            :arg source_id: source id for which this event needs to be generated
            :returns: True for success.)pyds";
	}

	namespace nvoptical
	{
		namespace  NvOFFlowVector
		{
            constexpr const char* descr = R"pyds(
                Holds motion vector information about an element.

                :ivar flowx: *int*, x component of motion vector
                :ivar flowy: *int*, y component of motion vector)pyds";

            constexpr const char* cast=R"pyds(casts to :class:`NvOFFlowVector`, call pyds.NvOFFlowVector(data))pyds";
		}

		namespace NvDsOpticalFlowMeta
		{
			constexpr const char* descr = R"pyds(
                Holds optical flow metadata about a frame.

                :ivar rows: *int*, Number of rows present in the frame for given block size
                    e.g. if block size is 4 and frame height is 720, then
                    number of rows = (720 / 4) = 180
                :ivar cols: *int*, Number of columns present in the frame for given block size
                    e.g. if block size is 4 and frame width is 1280, then
                    number of columns = (1280 / 4) = 320
                :ivar mv_size: *int*, Size of motion vector. Refer :class:`NvOFFlowVector`.
                :ivar frame_num: *int*, Current frame number of the source.
                :ivar data: Holds the motion vector.
                :ivar priv: Reserved field, for internal purpose only.
                :ivar reserved: Reserved field, for internal purpose only.

                Example usage:
                ::

                    def visualize_optical_flowvectors(flow):
                        """
                        Converts the flow u, v vectors into visualization by mapping them into
                        grey color space
                        :param flow: flow vectors
                        :return: bgr image
                        """
                        shape_visual = (flow.shape[0], flow.shape[1], 3)
                        mag, ang = cv2.cartToPolar(flow[..., 0], flow[..., 1])
                        hsv = np.full(shape_visual, 255, dtype=np.uint8)
                        hsv[..., 1] = 255
                        hsv[..., 0] = ang * 180 / np.pi / 2
                        hsv[..., 2] = cv2.normalize(mag, None, 0, 255, cv2.NORM_MINMAX)
                        bgr = cv2.cvtColor(hsv, cv2.COLOR_HSV2BGR)
                        bgr = 255 - bgr
                        return bgr

                    ...

                    l_user = frame_meta.frame_user_meta_list #Retrieve glist containing NvDsUserMeta objects from given NvDsFrameMeta object
                    while l_user is not None:
                        try:
                            # Casting l_user.data to pyds.NvDsUserMeta
                            of_user_meta = pyds.NvDsUserMeta.cast(l_user.data)
                            except StopIteration:
                                break
                            try:
                                # Casting of_user_meta.user_meta_data to pyds.NvDsOpticalFlowMeta
                                of_meta = pyds.NvDsOpticalFlowMeta.cast(of_user_meta.user_meta_data)
                                # Get Flow vectors as np array
                                flow_vectors = pyds.get_optical_flow_vectors(of_meta)
                                # Reshape the obtained flow vectors into proper shape
                                flow_vectors = flow_vectors.reshape(of_meta.rows, of_meta.cols, 2)
                                # map the flow vectors in HSV color space for visualization
                                flow_visual = visualize_optical_flowvectors(flow_vectors)
                                got_visual = True
                            except StopIteration:
                                break
                            try:
                                l_user = l_user.next
                            except StopIteration:
                                break)pyds";

            constexpr const char* cast=R"pyds(casts to :class:`NvDsOpticalFlowMeta`, call pyds.NvDsOpticalFlowMeta(data))pyds"; 
		}
	}
}
