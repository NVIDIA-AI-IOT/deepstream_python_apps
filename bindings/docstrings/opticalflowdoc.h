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
    namespace nvoptical
	{
		namespace  NvOFFlowVector
		{
            constexpr const char* descr = R"pyds(
                Holds motion vector information about an element.

                :ivar flowx: *int*, x component of motion vector
                :ivar flowy: *int*, y component of motion vector)pyds";

            constexpr const char* cast=R"pyds(casts to :class:`NvOFFlowVector`, call pyds.NvOFFlowVector(data))pyds";
		}

		namespace NvDsOpticalFlowMeta
		{
			constexpr const char* descr = R"pyds(
                Holds optical flow metadata about a frame.

                :ivar rows: *int*, Number of rows present in the frame for given block size
                    e.g. if block size is 4 and frame height is 720, then
                    number of rows = (720 / 4) = 180
                :ivar cols: *int*, Number of columns present in the frame for given block size
                    e.g. if block size is 4 and frame width is 1280, then
                    number of columns = (1280 / 4) = 320
                :ivar mv_size: *int*, Size of motion vector. Refer :class:`NvOFFlowVector`.
                :ivar frame_num: *int*, Current frame number of the source.
                :ivar data: Holds the motion vector.
                :ivar priv: Reserved field, for internal purpose only.
                :ivar reserved: Reserved field, for internal purpose only.

                Example usage:
                ::

                    def visualize_optical_flowvectors(flow):
                        """
                        Converts the flow u, v vectors into visualization by mapping them into
                        grey color space
                        :param flow: flow vectors
                        :return: bgr image
                        """
                        shape_visual = (flow.shape[0], flow.shape[1], 3)
                        mag, ang = cv2.cartToPolar(flow[..., 0], flow[..., 1])
                        hsv = np.full(shape_visual, 255, dtype=np.uint8)
                        hsv[..., 1] = 255
                        hsv[..., 0] = ang * 180 / np.pi / 2
                        hsv[..., 2] = cv2.normalize(mag, None, 0, 255, cv2.NORM_MINMAX)
                        bgr = cv2.cvtColor(hsv, cv2.COLOR_HSV2BGR)
                        bgr = 255 - bgr
                        return bgr

                    ...

                    l_user = frame_meta.frame_user_meta_list #Retrieve glist containing NvDsUserMeta objects from given NvDsFrameMeta object
                    while l_user is not None:
                        try:
                            # Casting l_user.data to pyds.NvDsUserMeta
                            of_user_meta = pyds.NvDsUserMeta.cast(l_user.data)
                            except StopIteration:
                                break
                            try:
                                # Casting of_user_meta.user_meta_data to pyds.NvDsOpticalFlowMeta
                                of_meta = pyds.NvDsOpticalFlowMeta.cast(of_user_meta.user_meta_data)
                                # Get Flow vectors as np array
                                flow_vectors = pyds.get_optical_flow_vectors(of_meta)
                                # Reshape the obtained flow vectors into proper shape
                                flow_vectors = flow_vectors.reshape(of_meta.rows, of_meta.cols, 2)
                                # map the flow vectors in HSV color space for visualization
                                flow_visual = visualize_optical_flowvectors(flow_vectors)
                                got_visual = True
                            except StopIteration:
                                break
                            try:
                                l_user = l_user.next
                            except StopIteration:
                                break)pyds";

            constexpr const char* cast=R"pyds(casts to :class:`NvDsOpticalFlowMeta`, call pyds.NvDsOpticalFlowMeta(data))pyds"; 
		}
	}
}