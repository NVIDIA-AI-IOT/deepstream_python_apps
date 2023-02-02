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
                Holds a set of nvdsanalytics frame level metadata.

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
}