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
}