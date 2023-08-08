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

#include "bind_string_property_definitions.h"
#include "bindfunctions.hpp"

namespace py = pybind11;
using namespace std;
namespace pydeepstream {

    void bindfunctions(py::module &m) {
        m.def("nvds_acquire_meta_lock",
              &nvds_acquire_meta_lock,
              "batch_meta"_a,
              pydsdoc::methodsDoc::nvds_acquire_meta_lock);

        m.def("nvds_release_meta_lock",
              &nvds_release_meta_lock,
              "batch_meta"_a,
              pydsdoc::methodsDoc::nvds_release_meta_lock);

        m.def("nvds_create_batch_meta",
              &nvds_create_batch_meta,
              "max_batch_size"_a,
              pydsdoc::methodsDoc::nvds_create_batch_meta);

        m.def("nvds_destroy_batch_meta",
              &nvds_destroy_batch_meta,
              "batch_meta"_a,
              pydsdoc::methodsDoc::nvds_destroy_batch_meta);

        m.def("nvds_acquire_frame_meta_from_pool",
              &nvds_acquire_frame_meta_from_pool,
              "batch_meta"_a,
              pydsdoc::methodsDoc::nvds_acquire_frame_meta_from_pool);

        m.def("nvds_add_frame_meta_to_batch",
              &nvds_add_frame_meta_to_batch,
              "batch_meta"_a,
              "frame_meta"_a,
              pydsdoc::methodsDoc::nvds_add_frame_meta_to_batch);

        m.def("nvds_remove_frame_meta_from_batch",
              &nvds_remove_frame_meta_from_batch,
              "batch_meta"_a,
              "frame_meta"_a,
              pydsdoc::methodsDoc::nvds_remove_frame_meta_from_batch);

        m.def("nvds_acquire_obj_meta_from_pool",
              &nvds_acquire_obj_meta_from_pool,
              "batch_meta"_a,
              py::return_value_policy::reference,
              pydsdoc::methodsDoc::nvds_acquire_obj_meta_from_pool);

        m.def("nvds_add_obj_meta_to_frame",
              &nvds_add_obj_meta_to_frame,
              "frame_meta"_a,
              "obj_meta"_a,
              "obj_parent"_a,
              pydsdoc::methodsDoc::nvds_add_obj_meta_to_frame);

        m.def("nvds_remove_obj_meta_from_frame",
              &nvds_remove_obj_meta_from_frame,
              "frame_meta"_a,
              "obj_meta"_a,
              pydsdoc::methodsDoc::nvds_remove_obj_meta_from_frame);

        m.def("nvds_acquire_classifier_meta_from_pool",
              &nvds_acquire_classifier_meta_from_pool,
              "batch_meta"_a,
              py::return_value_policy::reference,
              pydsdoc::methodsDoc::nvds_acquire_classifier_meta_from_pool);

        m.def("nvds_add_classifier_meta_to_object",
              &nvds_add_classifier_meta_to_object,
              "obj_meta"_a,
              "classifier_meta"_a,
              pydsdoc::methodsDoc::nvds_add_classifier_meta_to_object);

        m.def("nvds_remove_classifier_meta_from_obj",
              &nvds_remove_classifier_meta_from_obj,
              "obj_meta"_a,
              "classifier_meta"_a,
              pydsdoc::methodsDoc::nvds_remove_classifier_meta_from_obj1);

        m.def("nvds_acquire_display_meta_from_pool",
              &nvds_acquire_display_meta_from_pool,
              "batch_meta"_a,
              py::return_value_policy::reference,
              pydsdoc::methodsDoc::nvds_acquire_display_meta_from_pool);

        m.def("nvds_add_display_meta_to_frame",
              &nvds_add_display_meta_to_frame,
              "frame_meta"_a,
              "display_meta"_a,
              pydsdoc::methodsDoc::nvds_add_display_meta_to_frame);

        m.def("nvds_remove_display_meta_from_frame",
              &nvds_remove_display_meta_from_frame,
              "frame_meta"_a,
              "display_meta"_a,
              pydsdoc::methodsDoc::nvds_remove_display_meta_from_frame);

        m.def("nvds_acquire_label_info_meta_from_pool",
              &nvds_acquire_label_info_meta_from_pool,
              "batch_meta"_a,
              py::return_value_policy::reference,
              pydsdoc::methodsDoc::nvds_acquire_label_info_meta_from_pool);

        m.def("nvds_add_label_info_meta_to_classifier",
              &nvds_add_label_info_meta_to_classifier,
              "classifier_meta"_a,
              "label_info_meta"_a,
              pydsdoc::methodsDoc::nvds_add_label_info_meta_to_classifier);

        m.def("nvds_remove_label_info_meta_from_classifier",
              &nvds_remove_label_info_meta_from_classifier,
              "classifier_meta"_a,
              "label_info_meta"_a,
              pydsdoc::methodsDoc::nvds_remove_label_info_meta_from_classifier);

        m.def("nvds_add_user_meta_to_batch",
              &nvds_add_user_meta_to_batch,
              "batch_meta"_a,
              "user_meta"_a,
              pydsdoc::methodsDoc::nvds_add_user_meta_to_batch);

        m.def("nvds_add_user_meta_to_frame",
              &nvds_add_user_meta_to_frame,
              "frame_meta"_a,
              "user_meta"_a,
              pydsdoc::methodsDoc::nvds_add_user_meta_to_frame);

        m.def("nvds_add_user_meta_to_obj",
              &nvds_add_user_meta_to_obj,
              "obj_meta"_a,
              "user_meta"_a,
              pydsdoc::methodsDoc::nvds_add_user_meta_to_obj);

        m.def("nvds_acquire_user_meta_from_pool",
              &nvds_acquire_user_meta_from_pool,
              "batch_meta"_a,
              py::return_value_policy::reference,
              pydsdoc::methodsDoc::nvds_acquire_user_meta_from_pool);

        m.def("nvds_remove_user_meta_from_batch",
              &nvds_remove_user_meta_from_batch,
              "batch_meta"_a,
              "user_meta"_a,
              pydsdoc::methodsDoc::nvds_remove_user_meta_from_batch);

        m.def("nvds_remove_user_meta_from_frame",
              &nvds_remove_user_meta_from_frame,
              "frame_meta"_a,
              "user_meta"_a,
              pydsdoc::methodsDoc::nvds_remove_user_meta_from_frame);

        m.def("nvds_remove_user_meta_from_object",
              &nvds_remove_user_meta_from_object,
              "obj_meta"_a,
              "user_meta"_a,
              pydsdoc::methodsDoc::nvds_remove_user_meta_from_object);

        m.def("nvds_get_current_metadata_info",
              &nvds_get_current_metadata_info,
              "batch_meta"_a,
              pydsdoc::methodsDoc::nvds_get_current_metadata_info);

        m.def("nvds_batch_meta_copy_func",
              &nvds_batch_meta_copy_func,
              "data"_a,
              "user_meta"_a,
              pydsdoc::methodsDoc::nvds_batch_meta_copy_func);

        m.def("nvds_batch_meta_release_func",
              &nvds_batch_meta_release_func,
              "data"_a,
              "user_data"_a,
              pydsdoc::methodsDoc::nvds_batch_meta_release_func);

        m.def("nvds_get_nth_frame_meta",
              &nvds_get_nth_frame_meta,
              "frame_meta_list"_a,
              "index"_a,
              pydsdoc::methodsDoc::nvds_get_nth_frame_meta);

        m.def("nvds_clear_frame_meta_list",
              &nvds_clear_frame_meta_list,
              "batch_meta"_a,
              "meta_list"_a,
              pydsdoc::methodsDoc::nvds_clear_frame_meta_list);

        m.def("nvds_clear_obj_meta_list",
              &nvds_clear_obj_meta_list,
              "frame_meta"_a,
              "meta_list"_a,
              pydsdoc::methodsDoc::nvds_clear_obj_meta_list);

        m.def("nvds_clear_display_meta_list",
              &nvds_clear_display_meta_list,
              "frame_meta"_a,
              "meta_list"_a,
              pydsdoc::methodsDoc::nvds_clear_display_meta_list);

        m.def("nvds_clear_batch_user_meta_list",
              &nvds_clear_batch_user_meta_list,
              "batch_meta"_a,
              "meta_list"_a,
              pydsdoc::methodsDoc::nvds_clear_batch_user_meta_list);

        m.def("nvds_clear_frame_user_meta_list",
              &nvds_clear_frame_user_meta_list,
              "frame_meta"_a,
              "meta_list"_a,
              pydsdoc::methodsDoc::nvds_clear_frame_user_meta_list);

        m.def("nvds_clear_obj_user_meta_list",
              &nvds_clear_obj_user_meta_list,
              "object_meta"_a,
              "meta_list"_a,
              pydsdoc::methodsDoc::nvds_clear_obj_user_meta_list);

        m.def("nvds_clear_meta_list",
              &nvds_clear_meta_list,
              "batch_meta"_a,
              "meta_list"_a,
              "meta_pool"_a,
              pydsdoc::methodsDoc::nvds_clear_meta_list);

        m.def("nvds_copy_batch_user_meta_list",
              &nvds_copy_batch_user_meta_list,
              "src_user_meta_list"_a,
              "dst_batch_meta"_a,
              pydsdoc::methodsDoc::nvds_copy_batch_user_meta_list);

        m.def("nvds_copy_frame_user_meta_list",
              &nvds_copy_frame_user_meta_list,
              "src_user_meta_list"_a,
              "dst_frame_meta"_a,
              pydsdoc::methodsDoc::nvds_copy_frame_user_meta_list);

        m.def("nvds_copy_display_meta_list",
              &nvds_copy_display_meta_list,
              "src_display_meta"_a,
              "dst_frame_meta"_a,
              pydsdoc::methodsDoc::nvds_copy_display_meta_list);

        m.def("nvds_copy_frame_meta_list",
              &nvds_copy_frame_meta_list,
              "src_frame_meta_list"_a,
              "dst_batch_meta"_a,
              pydsdoc::methodsDoc::nvds_copy_frame_meta_list);

        m.def("nvds_copy_obj_meta_list",
              &nvds_copy_obj_meta_list,
              "src_obj_meta_list"_a,
              "dst_object_meta"_a,
              pydsdoc::methodsDoc::nvds_copy_obj_meta_list1);

        m.def("nvds_get_user_meta_type",
              &nvds_get_user_meta_type,
              "meta_descriptor"_a,
              pydsdoc::methodsDoc::nvds_get_user_meta_type1);

        m.def("gst_buffer_add_nvds_meta",
              &gst_buffer_add_nvds_meta,
              "buffer"_a,
              "meta_data"_a,
              "user_data"_a,
              "copy_func"_a,
              "release_func"_a,
              pydsdoc::methodsDoc::gst_buffer_add_nvds_meta);


        /** Gets the NvDsBatchMeta added to the GstBuffer.
         *
         * @param[in] buffer GstBuffer
         *
         * @return A pointer to the NvDsBatchMeta structure; or NULL if no
         * NvDsMeta was attached.
         */
        m.def("gst_buffer_get_nvds_batch_meta",
              [](size_t gst_buffer) {
                  auto *buffer = reinterpret_cast<GstBuffer *>(gst_buffer);
                  return gst_buffer_get_nvds_batch_meta(buffer);
              },
              "buffer"_a, py::return_value_policy::reference,
              pydsdoc::methodsDoc::gst_buffer_get_nvds_batch_meta);


        /**
         * Returns the frame in the numpy format
         * @param[in] address of the buffer
         * @param[in] batch_id
         */
        m.def("get_nvds_buf_surface",
              [](size_t gst_buffer, int batchID) {
                  auto *buffer = reinterpret_cast<GstBuffer *>(gst_buffer);
                  GstMapInfo inmap;
                  gst_buffer_map(buffer, &inmap, GST_MAP_READ);
                  auto *inputnvsurface = reinterpret_cast<NvBufSurface *>(inmap.data);
                  gst_buffer_unmap(buffer, &inmap);

                  if (inputnvsurface->surfaceList->colorFormat !=
                      NVBUF_COLOR_FORMAT_RGBA) {
                      throw std::runtime_error(
                              "get_nvds_buf_Surface: Currently we only support RGBA color Format");
                  }

                  int channels = 4;
                  /* use const reference here so input_surface is not altered
                     during mapping and syncing for CPU */
                  const NvBufSurfaceParams &input_surface = inputnvsurface->surfaceList[batchID];
#ifdef __aarch64__
                  /* Map the buffer if it has not been mapped already, before syncing the
                     mapped buffer to CPU.*/
                  if (nullptr == input_surface.mappedAddr.addr[0]) {
                      int ret = NvBufSurfaceMap(inputnvsurface, batchID, -1,
                                                NVBUF_MAP_READ_WRITE);
                      if (ret < 0) {
                          cout << "get_nvds_buf_surface: Failed to map "
                                  << "buffer to CPU" << endl;
                      }
                  }
                  if (NvBufSurfaceSyncForCpu(inputnvsurface, batchID, -1) != 0) {
                      cout << "get_nvds_buf_surface: Failed to sync "
                              << "buffer to CPU " << endl;
                  }

                  int height = input_surface.height;
                  int width = input_surface.width;
                  int pitch = input_surface.pitch;
                  auto dtype = py::dtype(
                          py::format_descriptor<unsigned char>::format());
                  return py::array(dtype, {height, width, channels},
                                   {sizeof(unsigned char) * pitch,
                                    sizeof(unsigned char) * channels,
                                    sizeof(unsigned char)},
                                   (const unsigned char *) input_surface.mappedAddr.addr[0],
                                   py::cast(input_surface.mappedAddr.addr[0]));
#else
                  int height = input_surface.height;
                  int width = input_surface.width;
                  int pitch = input_surface.pitch;
                  auto dtype = py::dtype(
                          py::format_descriptor<unsigned char>::format());
                  return py::array(dtype,
                                   {height, width, channels},
                                   {sizeof(unsigned char) * pitch,
                                    sizeof(unsigned char) * channels,
                                    sizeof(unsigned char)},
                                   (const unsigned char *) input_surface.dataPtr,
                                   py::cast(input_surface.dataPtr)
                  );
#endif
              },
              "gst_buffer"_a,
              "batchID"_a,
              py::return_value_policy::reference,
              pydsdoc::methodsDoc::get_nvds_buf_surface
        );


        m.def("get_nvds_buf_surface_gpu",
              [](size_t gst_buffer, int batchID) {
                  auto *buffer = reinterpret_cast<GstBuffer *>(gst_buffer);
                  GstMapInfo inmap;
                  gst_buffer_map(buffer, &inmap, GST_MAP_READ);

                  auto *inputnvsurface = reinterpret_cast<NvBufSurface *>(inmap.data);
                  gst_buffer_unmap(buffer, &inmap);

                  if (inputnvsurface->surfaceList->colorFormat !=
                      NVBUF_COLOR_FORMAT_RGBA) {
                      throw std::runtime_error(
                              "get_nvds_buf_surface_gpu: Currently we only support RGBA color Format");
                  }

#ifdef __aarch64__
                  /* Map the buffer if it has not been mapped already, otherwise sync the
                     mapped buffer to CPU.*/
                  throw std::runtime_error(
                          "get_nvds_buf_surface_gpu: Currently we only support x86");
#else
                  int channels = 4;
                  int height = inputnvsurface->surfaceList[batchID].height;
                  int width = inputnvsurface->surfaceList[batchID].width;
                  int pitch = inputnvsurface->surfaceList[batchID].pitch;
                  int size = inputnvsurface->surfaceList[batchID].dataSize;
                  auto dtype = py::dtype(
                          py::format_descriptor<unsigned char>::format());
                  return py::make_tuple(dtype,
                                        py::make_tuple(height, width, channels),
                                        py::make_tuple(
                                                sizeof(unsigned char) * pitch,
                                                sizeof(unsigned char) *
                                                channels,
                                                sizeof(unsigned char)),
                                        py::cast(
                                                inputnvsurface->surfaceList[batchID].dataPtr),
                                        size);
#endif
              },
              "gst_buffer"_a, "batchID"_a,
              py::return_value_policy::reference,
              pydsdoc::methodsDoc::get_nvds_buf_surface_gpu);


        /**
         * Unmaps the NvBufSurface of the frame
         * @param[in] address of the buffer
         * @param[in] batch_id
         */
        m.def("unmap_nvds_buf_surface",
              [](size_t gst_buffer, int batchID) {
                  auto *buffer = reinterpret_cast<GstBuffer *>(gst_buffer);
                  GstMapInfo inmap;
                  gst_buffer_map(buffer, &inmap, GST_MAP_READ);
                  auto *inputnvsurface = reinterpret_cast<NvBufSurface *>(inmap.data);
                  gst_buffer_unmap(buffer, &inmap);

                  /* use const reference here so input_surface is not altered
                     during mapping and syncing for CPU */
                  const NvBufSurfaceParams &input_surface = inputnvsurface->surfaceList[batchID];
                  /* Map the buffer if it has not been mapped already, before syncing the
                     mapped buffer to CPU.*/
                  if (nullptr != input_surface.mappedAddr.addr[0]) {
                      int ret = NvBufSurfaceUnMap(inputnvsurface, batchID, -1);
                      if (ret < 0) {
                          cout << "get_nvds_buf_Surface: Failed to unmap "
                                  << "buffer" << endl;
                      }
                  }
              },
              "gst_buffer"_a,
              "batchID"_a,
              pydsdoc::methodsDoc::unmap_nvds_buf_surface
        );

        //FIXME: Find a better way of doing this
        /**
        * Type casting to @NvDsBatchMeta
        */
        m.def("glist_get_nvds_batch_meta",
              [](void *data) {
                  return (NvDsBatchMeta *) data;
              },
              py::return_value_policy::reference);
        /**
         * Type casting to @NvDsFrameMeta
         */
        m.def("glist_get_nvds_frame_meta",
              [](void *data) {
                  return (NvDsFrameMeta *) data;
              },
              py::return_value_policy::reference);
        /**
         * Type casting to @NvDsObjectMeta
         */
        m.def("glist_get_nvds_object_meta",
              [](void *data) {
                  return (NvDsObjectMeta *) data;
              },
              py::return_value_policy::reference);
        /**
         * Type casting to @NvDsUserMeta
         */
        m.def("glist_get_nvds_user_meta",
              [](void *data) {
                  return (NvDsUserMeta *) data;
              },
              py::return_value_policy::reference);
        /**
         * Type casting to @NvDsClassifierMeta
         */
        m.def("glist_get_nvds_classifier_meta",
              [](void *data) {
                  return (NvDsClassifierMeta *) data;
              },
              py::return_value_policy::reference);
        /**
         * Type casting to @NvDsDisplayMeta
         */
        m.def("glist_get_nvds_display_meta",
              [](void *data) {
                  return (NvDsDisplayMeta *) data;
              },
              py::return_value_policy::reference);
        /**
         * Type casting to @NvDsLabelInfo
         */
        m.def("glist_get_nvds_label_info",
              [](void *data) {
                  return (NvDsLabelInfo *) data;
              },
              py::return_value_policy::reference);
        /**
         * Type casting to @NvDsEventMsgMeta
         */
        m.def("glist_get_nvds_event_msg_meta",
              [](void *data) {
                  return (NvDsEventMsgMeta *) data;
              },
              py::return_value_policy::reference);

        m.def("glist_get_nvds_event_msg_meta",
              [](size_t data) {
                  return (NvDsEventMsgMeta *) data;
              },
              py::return_value_policy::reference);
        /**
         * Type casting to @NvDsVehicleObject
         */
        m.def("glist_get_nvds_vehicle_object",
              [](void *data) {
                  return (NvDsVehicleObject *) data;
              },
              py::return_value_policy::reference);
        /**
         * Type casting to @NvDsPersonObject
         */
        m.def("glist_get_nvds_person_object",
              [](void *data) {
                  return (NvDsPersonObject *) data;
              },
              py::return_value_policy::reference);
        /**
         * Type casting to @NvDsInferTensorMeta
         */
        m.def("glist_get_nvds_tensor_meta",
              [](void *data) {
                  return (NvDsInferTensorMeta *) data;
              },
              py::return_value_policy::reference);

        // Required for backward compatibility
        m.def("register_user_copyfunc",
              [](std::function<utils::COPYFUNC_SIG> const &func) {
              });

        // Set a callback copy function defined in the user python code
        m.def("user_copyfunc",
              [](NvDsUserMeta *meta,
                 std::function<utils::COPYFUNC_SIG> const &func) {
                  utils::set_copyfunc(meta, func);
              },
	      py::call_guard<py::gil_scoped_release>(),
              "meta"_a,
              "func"_a,
              pydsdoc::methodsDoc::user_copyfunc);

        // Set a callback copy function defined in the user python code
        m.def("set_user_copyfunc",
              [](NvDsUserMeta *meta,
                 std::function<utils::COPYFUNC_SIG> const &func) {
                  utils::set_copyfunc(meta, func);
              });

        // Required for backward compatibility
        m.def("register_user_releasefunc",
              [](std::function<utils::RELEASEFUNC_SIG> const &func) {
              });


        // Set a callback release function defined in the user python code
        m.def("user_releasefunc",
              [](NvDsUserMeta *meta,
                 std::function<utils::RELEASEFUNC_SIG> const &func) {
                  utils::set_freefunc(meta, func);
              },
	      py::call_guard<py::gil_scoped_release>(),
              "meta"_a,
              "func"_a,
              pydsdoc::methodsDoc::user_releasefunc);

        // Set a callback release function defined in the user python code
        m.def("set_user_releasefunc",
              [](NvDsUserMeta *meta,
                 std::function<utils::RELEASEFUNC_SIG> const &func) {
                  utils::set_freefunc(meta, func);
              });

        // Required for backward compatibility
        m.def("unset_callback_funcs",
              []() {
            utils::release_all_func();
        },
              py::call_guard<py::gil_scoped_release>()
	);

        m.def("alloc_char_buffer",
              [](size_t size) {
                  return (size_t) g_malloc0(size);
              },
              py::return_value_policy::reference);

        m.def("alloc_buffer",
              [](size_t size) {
                  return (size_t) g_malloc0(size);
              },
              "size"_a,
              py::return_value_policy::reference,
              pydsdoc::methodsDoc::alloc_buffer);

        m.def("free_buffer",
              [](size_t buffer) {
                  if (buffer)
                      g_free((char *) buffer);
              },
              "buffer"_a, pydsdoc::methodsDoc::free_buffer);

        m.def("free_gbuffer",
              [](gpointer buffer) {
                  if (buffer)
                      g_free(buffer);
              },
              "buffer"_a, pydsdoc::methodsDoc::free_gbuffer);

        m.def("get_string",
              [](size_t ptr) {
                  return (char *) ptr;
              },
              "ptr"_a,
              py::return_value_policy::reference,
              pydsdoc::methodsDoc::get_string);

        m.def("get_ptr",
              [](void *ptr) {
                  return (size_t) ptr;
              },
              "ptr"_a,
              py::return_value_policy::reference,
              pydsdoc::methodsDoc::get_ptr);

        m.def("strdup",
              [](size_t ptr) -> size_t {
                  char *str = (char *) ptr;
                  if (str != nullptr)
                      return (size_t) g_strdup(str);
                  else
                      return (size_t) nullptr;
              },
              py::return_value_policy::reference);

        m.def("strdup2str",
              [](size_t ptr) -> std::string {
                  char *str = (char *) ptr;
                  if (str != nullptr)
                      return {str};
                  else
                      return "";
              },
              py::return_value_policy::reference);

        m.def("memdup",
              [](size_t ptr, size_t size) -> size_t {
                  auto buffer = (gpointer) ptr;
                  if (buffer != nullptr)
                      return (size_t) g_memdup(buffer, size);
                  else
                      return (size_t) nullptr;
              },
              "ptr"_a, "size"_a,
              py::return_value_policy::reference);


        /* Start binding for /nvutils/nvbufsurface/nvbufsurface.c */
        m.def("NvBufSurfaceCreate",
              (int (*)(NvBufSurface *, int,
                       NvBufSurfaceCreateParams)) &NvBufSurfaceCreate,
              "surf"_a, "batchSize"_a,
              "params"_a, pydsdoc::methodsDoc::NvBufSurfaceCreate);

        m.def("NvBufSurfaceDestroy", &NvBufSurfaceDestroy,
              "surf"_a, pydsdoc::methodsDoc::NvBufSurfaceDestroy);

        m.def("NvBufSurfaceMap", &NvBufSurfaceMap,
              "surf"_a, "index"_a,
              "plane"_a, "type"_a,
              pydsdoc::methodsDoc::NvBufSurfaceMap);

        m.def("NvBufSurfaceUnMap", &NvBufSurfaceUnMap,
              "surf"_a, "index"_a,
              "plane"_a,
              pydsdoc::methodsDoc::NvBufSurfaceUnMap);

        m.def("NvBufSurfaceCopy", &NvBufSurfaceCopy,
              "srcSurf"_a, "dstSurf"_a,
              pydsdoc::methodsDoc::NvBufSurfaceCopy);

        m.def("NvBufSurfaceSyncForCpu", &NvBufSurfaceSyncForCpu,
              "surf"_a, "index"_a,
              "plane"_a,
              pydsdoc::methodsDoc::NvBufSurfaceSyncForCpu);

        m.def("NvBufSurfaceSyncForDevice", &NvBufSurfaceSyncForDevice,
              "surf"_a, "index"_a,
              "plane"_a,
              pydsdoc::methodsDoc::NvBufSurfaceSyncForDevice);

        m.def("NvBufSurfaceFromFd", (int (*)(int, void *)) &NvBufSurfaceFromFd,
              py::return_value_policy::reference,
              "dmabuf"_a, "buffer"_a,
              pydsdoc::methodsDoc::NvBufSurfaceFromFd);

        m.def("NvBufSurfaceMemSet", &NvBufSurfaceMemSet,
              "surf"_a, "index"_a,
              "plane"_a,
              "value"_a,
              pydsdoc::methodsDoc::NvBufSurfaceMemSet);

        m.def("NvBufSurfaceMapEglImage", &NvBufSurfaceMapEglImage,
              "surf"_a, "index"_a,
              pydsdoc::methodsDoc::NvBufSurfaceMapEglImage);


        /**
         * Type casting to @NvDsUserMeta
         */
        m.def("glist_get_nvds_Surface_Params",
              [](void *data) {
                  return (NvBufSurfaceParams *) data;
              },
              py::return_value_policy::reference);

        m.def("get_detections",
              [](void *data, int i) {
                  const auto *detections = (const float *) (data);
                  return detections[i];
              },
              py::return_value_policy::reference);

        m.def("get_optical_flow_vectors",
              [](void *data) {
                  auto *META = (NvDsOpticalFlowMeta *) data;
                  auto *DATA = (NvOFFlowVector *) META->data;
                  uint total = META->rows * META->cols;
                  py::array_t<float> flowvec = py::array_t<float>(total * 2);
                  auto mutable_arr = flowvec.mutable_unchecked<1>();
                  for (py::ssize_t i = 0; i < total; ++i) {
                      auto elm = DATA[i];
                      py::ssize_t index = i * 2;
                      mutable_arr(index) = static_cast<float>(elm.flowx);
                      mutable_arr(index + 1) = static_cast<float>(elm.flowy);
                  }
                  return flowvec;
              },
              "data"_a, pydsdoc::methodsDoc::get_optical_flow_vectors);

        m.def("get_nvds_LayerInfo",
              [](void *data, int j) {
                  auto *META = (NvDsInferTensorMeta *) data;
                  NvDsInferLayerInfo *info = &META->output_layers_info[j];
                  info->buffer = META->out_buf_ptrs_host[j];
                  return info;
              },
              py::return_value_policy::reference);

        m.def("get_segmentation_masks",
              [](void *data) {
                  auto *META = (NvDsInferSegmentationMeta *) data;
                  int width = META->width;
                  int height = META->height;
                  auto dtype = py::dtype(py::format_descriptor<int>::format());
                  return py::array(dtype, {height, width},
                                   {sizeof(int) * width, sizeof(int)},
                                   META->class_map);
              },
              "data"_a,
              pydsdoc::methodsDoc::get_segmentation_masks);

        /* Start binding for /sources/includes/gst-nvevent.h */
        /**
         * Sends the custom nvevent_new_stream_reset
         * for the element it is called upon. This event
         * is propogated downstream. The function returns
         * True if the event was handled.
         */
        m.def("gst_element_send_nvevent_new_stream_reset",
              [](size_t gst_element, int source_id) {
                  auto *element = reinterpret_cast<GstElement *>(gst_element);
                  return gst_element_send_event(element, gst_nvevent_new_stream_reset(source_id));
              },
              pydsdoc::methodsDoc::gst_element_send_nvevent_new_stream_reset);

        m.def("configure_source_for_ntp_sync",
            [](size_t src_elem) {
                  auto *element = reinterpret_cast<GstElement *>(src_elem);
                  configure_source_for_ntp_sync(element);
                  return;
              },
              "src_elem"_a,
              pydsdoc::methodsDoc::configure_source_for_ntp_sync);

    }
}
