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
    namespace NvDsRoiMetaDoc 
    {
        namespace NvDsDataTypeDoc {
            constexpr const char* descr = R"pyds(*Enumerator*. Specifies the type of meta data.)pyds";
            
            constexpr const char* NvDsDataType_FP32=R"pyds(NvDsDataType_FP32)pyds"; 
            constexpr const char* NvDsDataType_UINT8=R"pyds(NvDsDataType_UINT8)pyds";
            constexpr const char* NvDsDataType_INT8=R"pyds(NvDsDataType_INT8)pyds"; 
            constexpr const char* NvDsDataType_UINT32=R"pyds(NvDsDataType_UINT32)pyds";
            constexpr const char* NvDsDataType_INT32=R"pyds(NvDsDataType_INT32)pyds";
            constexpr const char* NvDsDataType_FP16=R"pyds(NvDsDataType_FP16)pyds";
        }

        namespace NvDsUnitTypeDoc {
            constexpr const char* descr = R"pyds(*Enumerator*. Specifies the type of meta data.)pyds";
            
            constexpr const char* NvDsUnitType_FullFrame=R"pyds(NvDsUnitType_FullFrame)pyds"; 
            constexpr const char* NvDsUnitType_ROI=R"pyds(NvDsUnitType_ROI)pyds";
            constexpr const char* NvDsUnitType_Object=R"pyds(NvDsUnitType_Object)pyds"; 
        }

        namespace NvDsRoiMetaDoc {
            constexpr const char* descr = R"pyds(Batch metadata structure for roi operations)pyds";
            constexpr const char* cast = R"pyds(Casts a pointer to NvDsRoiMetaDoc)pyds";
        }

        namespace NvBufSurfaceParams {
            constexpr const char* descr = R"pyds(Batch metadata structure for roi operations)pyds";
            constexpr const char* cast = R"pyds(Casts a pointer to NvBufSurfaceParams)pyds";
        }

        namespace NvDsFrameMeta {
            constexpr const char* descr = R"pyds(Batch metadata structure for roi operations)pyds";
            constexpr const char* cast = R"pyds(Casts a pointer to NvDsFrameMeta)pyds";
        }

        namespace NvDsObjectMeta {
            constexpr const char* descr = R"pyds(Batch metadata structure for roi operations)pyds";
            constexpr const char* cast = R"pyds(Casts a pointer to NvDsObjectMeta)pyds";
        }
    }  
}  
