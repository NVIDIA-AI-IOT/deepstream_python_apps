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
}