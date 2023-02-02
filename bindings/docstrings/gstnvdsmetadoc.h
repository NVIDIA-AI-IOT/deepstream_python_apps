
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
    namespace gstnvdsmetadoc
    {
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
    }

}