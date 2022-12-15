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
    namespace trackerdoc
    {
        namespace NvDsPastFrameObjDoc //missing doxygen comments
        {
            constexpr const char* descr = R"pyds(
                NvDsPastFrameObj

                :ivar frameNum: *int*, frameNum
                :ivar tBbox: :class:`NvOSD_RectParams`, tBbox
                :ivar confidence: *float*, confidence
                :ivar age: *int*, age

                Example usage:
                ::

                    l_user=batch_meta.batch_user_meta_list #Retrieve glist of NvDsUserMeta objects from given NvDsBatchMeta object
                    while l_user is not None:
                        try:
                            # Note that l_user.data needs a cast to pyds.NvDsUserMeta
                            # The casting is done by pyds.NvDsUserMeta.cast()
                            # The casting also keeps ownership of the underlying memory
                            # in the C code, so the Python garbage collector will leave
                            # it alone
                            user_meta=pyds.NvDsUserMeta.cast(l_user.data) 
                        except StopIteration:
                            break
                        if(user_meta and user_meta.base_meta.meta_type==pyds.NvDsMetaType.NVDS_TRACKER_PAST_FRAME_META): #Make sure metatype is correct
                            try:
                                # Note that user_meta.user_meta_data needs a cast to pyds.NvDsPastFrameObjBatch
                                # The casting is done by pyds.NvDsPastFrameObjBatch.cast()
                                # The casting also keeps ownership of the underlying memory
                                # in the C code, so the Python garbage collector will leave
                                # it alone
                                pPastFrameObjBatch = pyds.NvDsPastFrameObjBatch.cast(user_meta.user_meta_data) #See NvDsPastFrameObjBatch for details
                            except StopIteration:
                                break
                            for trackobj in pyds.NvDsPastFrameObjBatch.list(pPastFrameObjBatch): #Iterate through list of NvDsPastFrameObjStream objects
                                #Access NvDsPastFrameObjStream attributes
                                print("streamId=",trackobj.streamID)
                                print("surfaceStreamID=",trackobj.surfaceStreamID)
                                for pastframeobj in pyds.NvDsPastFrameObjStream.list(trackobj): #Iterate through list of NvDsFrameObjList objects
                                #Access NvDsPastFrameObjList attributes
                                print("numobj=",pastframeobj.numObj)
                                print("uniqueId=",pastframeobj.uniqueId)
                                print("classId=",pastframeobj.classId)
                                print("objLabel=",pastframeobj.objLabel)
                                for objlist in pyds.NvDsPastFrameObjList.list(pastframeobj): #Iterate through list of NvDsFrameObj objects
                                    #Access NvDsPastFrameObj attributes
                                    print('frameNum:', objlist.frameNum)
                                    print('tBbox.left:', objlist.tBbox.left)
                                    print('tBbox.width:', objlist.tBbox.width)
                                    print('tBbox.top:', objlist.tBbox.top)
                                    print('tBbox.right:', objlist.tBbox.height)
                                    print('confidence:', objlist.confidence)
                                    print('age:', objlist.age)
                        try:
                            l_user=l_user.next
                        except StopIteration:
                            break)pyds";

            constexpr const char* cast=R"pyds(cast given object/data to :class:`NvDsPastFrameObj`, call pyds.NvDsPastFrameObj.cast(data))pyds";
        }

        namespace NvDsPastFrameObjListDoc
        {
            constexpr const char* descr = R"pyds(
                One object in several past frames. See :class:`NvDsPastFrameObj` for example usage.

                :ivar numObj: *int*, Number of frames this object appreared in the past.
                :ivar uniqueId: *int*, Object tracking id.
                :ivar classID: *int*, Object class id.
                :ivar objLabel: An array of the string describing the object class.)pyds";

            constexpr const char* list=R"pyds(Retrieve :class:`NvDsPastFrameObjList` object as list of :class:`NvDsPastFrameObj`. Contains past frame info of this object.)pyds";
            constexpr const char* cast=R"pyds(cast given object/data to :class:`NvDsPastFrameObjList`, call pyds.NvDsPastFrameObjList.cast(data))pyds";
        }

        namespace NvDsPastFrameObjStreamDoc
        {
            constexpr const char* descr = R"pyds(
                List of objects in each stream. See :class:`NvDsPastFrameObj` for example usage.

                :ivar streamID: *int*, Stream id the same as frame_meta->pad_index.
                :ivar surfaceStreamID: *int*, Stream id used inside tracker plugin.
                :ivar numAllocated: *int*, Maximum number of objects allocated.
                :ivar numFilled: *int*, Number of objects in this frame.)pyds";

            constexpr const char* list=R"pyds(Retrieve :class:`NvDsPastFrameObjStream` object as list of :class:`NvDsPastFrameObjList`. Contains objects inside this stream.)pyds";
            constexpr const char* cast=R"pyds(cast given object/data to :class:`NvDsPastFrameObjStream`, call pyds.NvDsPastFrameObjStream.cast(data))pyds";
        }
        
        namespace NvDsPastFrameObjBatchDoc
        {
            constexpr const char* descr = R"pyds(
                Batch of lists of buffered objects. See :class:`NvDsPastFrameObj` for example usage.
                
                :ivar numAllocated: *int*, Number of blocks allocated for the list.
                :ivar numFilled: *int*, Number of filled blocks in the list.
                )pyds";

            constexpr const char* list=R"pyds(Retrieve :class:`NvDsPastFrameObjBatch` object as list of :class:`NvDsPastFrameObjStream`. Contains stream lists.)pyds";
            constexpr const char* cast=R"pyds(cast given object/data to :class:`NvDsPastFrameObjBatch`, call pyds.NvDsPastFrameObjBatch.cast(data))pyds";
        }

    }
}