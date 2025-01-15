/*
 * SPDX-FileCopyrightText: Copyright (c) 2019-2021 NVIDIA CORPORATION & AFFILIATES. All rights reserved.
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

#ifndef _NVDS_360D_META_H_
#define _NVDS_360D_META_H_

#ifdef __cplusplus
extern "C"
{
#endif

/**
 * Defines DeepStream 360d metadata.
 */
typedef enum
{
  ROI_ENTRY_360D = 0x01,
  ROI_EXIT_360D = 0x02,
  INSIDE_AISLE_360D = 0x04
} ROI_STATUS_360D;

typedef struct _RectDim {
  float left;
  float top;
  float width;
  float height;
  int class_id;
  int tracking_id;
  int gie_unique_id;
  int roi_status;
  void *text;
}RectDim;

#ifdef __cplusplus
}
#endif

#endif
