/*
 * SPDX-FileCopyrightText: Copyright (c) 2021-2023 NVIDIA CORPORATION &
 * AFFILIATES. All rights reserved. SPDX-License-Identifier: Apache-2.0
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

namespace pydsdoc {
namespace utilsdoc {

namespace NvDsObjEncOutParamsDoc {
constexpr const char *descr = R"pyds(
                output parameters of NVDS_CROP_IMAGE_META

                :ivar outBuffer: *np.array of char*, The output buffer JPEG Encoded Object.)pyds";

constexpr const char *cast =
    R"pyds(cast given object/data to :class:`NvDsObjEncOutParams`, call pyds.NvDsObjEncOutParams.cast(data))pyds";
} // namespace NvDsObjEncOutParamsDoc

namespace NvDsObjEncUsrArgsDoc {
constexpr const char *descr = R"pyds(
                user parameters for a nvds_obj_enc_process call

                :ivar saveImg: *bool*, Boolean variable to save image.
                :ivar attachUsrMeta: *bool*, Variable to attach user metadata.
                                             Metadata Type is "NVDS_CROP_IMAGE_META".
                :ivar scaleImg: *bool*, Boolean variable to scale image.
                :ivar scaledWidth: *int*, Width Parameter for scaling.
                :ivar scaledHeight: *int*, Height Paramater for scaling.
                :ivar fileNameImg: An array to store the string describing the path of the JPEG file.
                                   If user specifies the filename then it'll be used otherwise the
                                   following naming convention is used to create filename of the encoded
                                   objects -
                                   "frame-number_stream-number_object-number_object-type_widthxheight.jpg".
                                   For example - 0_2_3_PERSON_126x148.jpg
                :ivar objNum: *int*, Object number in the frame .
                :ivar quality: *bool*, Image quality value.
                :ivar isFrame: *bool*, Variable for frame/object encoding. 
                                       1: Encodes the entire frame.
                                       0: Encodes object of specified resolution
                :ivar calcEncodeTime: *bool*, Boolean variable to calculate time of encode.)pyds";

constexpr const char *cast =
    R"pyds(cast given object/data to :class:`NvDsObjEncUsrArgs`, call pyds.NvDsObjEncUsrArgs.cast(data))pyds";
} // namespace NvDsObjEncUsrArgsDoc

} // namespace utilsdoc
} // namespace pydsdoc