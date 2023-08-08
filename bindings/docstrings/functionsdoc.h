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

            For Jetson, a matching call to :py:func:`unmap_nvds_buf_surface` must be made.

            :arg gst_buffer: address of the Gstbuffer which contains `NvBufSurface`
            :arg batchID: batch_id of the frame to be processed. This indicates the frame's index within :class:`NvBufSurface`
            
            :returns: NumPy array containing the frame image buffer.)pyds";
        
        constexpr const char* get_nvds_buf_surface_gpu=R"pyds(
            This function returns the dtype, shape of the array, strides, pointer to the GPU buffer, and size of the allocated memory for the buffer. Only x86 and RGBA format is supported. This information can be used to create a CuPy array (see deepstream-imagedata-multistream-cupy).
            Changes to the frame image will be preserved and seen in downstream elements, with the following restrictions.
            1. No change to image color format or resolution
            2. No transpose operation on the array.

            :arg gst_buffer: address of the Gstbuffer which contains `NvBufSurface`
            :arg batchID: batch_id of the frame to be processed. This indicates the frame's index within :class:`NvBufSurface`
            
            :returns: dtype, shape, strides, pointer to buffer, size of allocated memory of the GPU buffer)pyds";

        constexpr const char* unmap_nvds_buf_surface=R"pyds(
            This function unmaps the NvBufSurface of the given Gst buffer and batch id, if previously mapped. For Jetson, a matching call to this function must be made for every call to :py:func:`get_nvds_buf_surface`.

            The array can no longer be accessed after this call, as the memory is released.

            :arg gst_buffer: address of the Gstbuffer which contains `NvBufSurface`
            :arg batchID: batch_id of the frame to be processed. This indicates the frame's index within :class:`NvBufSurface`)pyds";

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
        
        constexpr const char* alloc_custom_struct=R"pyds( 
            Allocate an :class:`CustomDataStruct`. 

            :returns: Allocated :class:`CustomDataStruct`)pyds";

        constexpr const char* configure_source_for_ntp_sync=R"pyds(
            Configure the source to generate NTP sync values for RTSP sources.

            These values are used by the DeepStream GStreamer element NvStreamMux to calculate the NTP time of the frames at the source.

            This functionality is dependent on the RTSP sending the RTCP Sender Reports. source.

            This function only works for RTSP sources i.e. GStreamer elements "rtspsrc" or "uridecodebin" with an RTSP uri.

            :arg src_elem: GStreamer source element to be configured.)pyds";
	}
}