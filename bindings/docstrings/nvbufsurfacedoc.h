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
}