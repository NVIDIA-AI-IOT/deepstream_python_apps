################################################################################
# SPDX-FileCopyrightText: Copyright (c) 2020-2021 NVIDIA CORPORATION & AFFILIATES. All rights reserved.
# SPDX-License-Identifier: Apache-2.0
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
# http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
################################################################################

This guide shows how to use custom deep learning models and parse their inference output in a Python application. Custom model support is provided by the Triton Inference Server plugin included in the DeepStream SDK. The raw inference output can be parsed in a Python application via access to the NvDsInferTensorMeta structure. Sample code is provided in the deepstream-ssd-parser Python application.

**1 - Inference via Triton**

To perform inference using Triton and access the raw output, the general steps are:

1. Include Triton plugin in the pipeline. The deepstream-ssd-parser app shows how to construct a pipeline with Triton as the primary detector.

2. Configure the Triton plugin to attach raw output tensors to the metadata, and allow for custom post-processing. See details below.

3. Add a probe function to intercept output tensors for parsing. See the deepstream-ssd-parser app for example.

<b>Configuring Triton for custom parsing</b>:

1. Select custom post-processing:

   In ds_test_ssd_no_postprocess.txt, edit the `infer_config -> postprocess` section 
   to specify "other" as the parsing function and point to the custom labels file used for parsing:

   ```

   postprocess {

      Labelfile_path: "../../../../samples/trtis_model_repo/ssd_inception_v2_coco_2018_01_28/labels.txt"

      other {}

    }

   ```

2. Enable attachment of inference output tensors to metadata:

   Add the following text to the config file:

   ```

   output_control {

      output_tensor_meta: true

   }

   ```

**2 - How to intercept tensor meta in a Python application**

This is done in `pgie_src_pad_buffer_probe`.

This is done in several steps:

1. Get the buffer of info argument. 

   ```gst_buffer = info.get_buffer()```

2. Retrieve the gst buffer from batch meta

   ```batch_meta = pyds.gst_buffer_get_nvds_batch_meta(hash(gst_buffer))```

3. Retrieve the first frame

   ```l_frame = batch_meta.frame_meta_list```

4. Retrieve the metadata for the first frame

   ```frame_meta = pyds.NvDsFrameMeta.cast(l_frame.data)```

5. Retrieve the frame meta user list and verify it is not None

   ```l_user = frame_meta.frame_user_meta_list```

6. Retrieve the user metadata

   ```user_meta = pyds.NvDsUserMeta.cast(l_user.data)```

7. Retrieve the tensor meta

   ```tensor_meta = pyds.NvDsInferTensorMeta.cast(user_meta.user_meta_data)```

The function ```pgie_src_pad_buffer_probe``` is given as a probe in the pipeline created in main function.

Sample code is available for SSD parser neural network. 

**3 - Tensor meta structure and bindings API**

* pyds.NvDsInferTensorMeta.cast(data): This function casts the data into the pyds.NvDsInferTensorMeta object, this metadata is added as NvDsUserMeta to the frame_user_meta_list of the corresponding frame_meta or object_user_meta_list of the corresponding object with the meta_type set to NVDSINFER_TENSOR_OUTPUT_META.

This object has the following methods and members:

* gpu_id: GPU device ID on which the device buffers have been allocated.

* num_output_layers: Number of output layers.

* out_buf_ptrs_dev: Array of objects to the output device buffers for the frame / object.

* out_buf_ptrs_host: Array of objects to the output host buffers for the frame / object.

* output_layers_info:

				arg0: object of type pyds.NvDsInferTensorMeta

				arg1: integer ‘i’

				Output: returns ith layer in the array.

* priv_data: Private data used for the meta producer’s internal memory management.

* unique_id: Unique ID of the gst-nvinfer instance which attached this meta.

* pyds.NvDsInferObjectDetectionInfo: Holds information about one parsed object from detector’s output.

  This object has the following methods and members:

* classId: ID of the class to which the object belongs.

* detectionConfidence: Object detection confidence. Should be a float value in the range [0,1].

* height: Height of the bounding box shape for the object.

* left: Horizontal offset of the bounding box shape for the object.

* top: Vertical offset of the bounding box shape for the object.

* width: Width of the bounding box shape for the object.

**  **

**4 - SSD parser example**

Below is a general explanation of the deepstream-ssd-parser sample application. See comments in the code for additional details.

**4.1 - deepstream_ssd_parser.py**

**4.1.1 - main**

* This function takes a path to a file media or uri.

* Gstreamer initialization is performed.

* Several  elements a created in order to make a pipeline.

* These elements are added to the pipeline and linked together.

* Probe functions are linked to the pipeline in order to interact with the data:

    * **pgie_src_pad_buffer_probe**

    * **osd_sink_pad_buffer_probe**

* The pipeline is set to its PLAYING mode.

* The main loop is run.

* The pipeline is set to its NULL mode.

**4.1.2 - pgie_src_pad_buffer_probe**

* Initialize an empty dictionary with the class id as key and the number of occurrences as value.

* For each element in the image, the number of occurrences of the element class is incremented.

* A string containing the number of cars and persons is formatted.

* Some display style is added to this string before displaying.

* The string is added on the frame.

**4.1.3 - osd_sink_pad_buffer_probe**

* The gst buffer is retrieved from the info argument.

* The batch meta is retrieved from the gst buffer.

* A detection param is created. It contains the number of class and their accuracy threshold.

* A box size param is created, it contains the image dimension and the minimum dimension of a bounding box. This will be used to remove bounding boxes that are too small. This neural network works only with floating-point coordinates between 0 and 1. Since the minimum dimension is given in pixels, the image dimension is needed to scale up the floating-point coordinates. And then compare them to the minimum dimension.

* A nms (Non-maximal suppression) param is created. This param contains:

  top_k: the maximum number of boxes to keep.

  iou_threshold: intersection over union threshold used to discard bounding boxes that are too similar.

* The labels are retrieved from a file in the same directory called labels.txt, this path can be specified in the config file. The labels must be one per line, and the ordering corresponds to class ID ordering.

* frame_meta, l_user, user_meta and tensor_meta are retrieved.

* tensor meta is then used to retrieve layer information and store them in a list (layers_info).

* Then a frame_object_list is obtained by calling  **nvds_infer_parse_custom_tf_ssd** with:

    * layers_info

    * detection_param

    * box_size_param

    * nms_param

* Each obj_meta of this frame_object_list is then added to the current frame with the function **add_obj_meta_to_frame**.

**4.1.4 - add_obj_meta_to_frame**

* An obj_meta is created and filled with:

    * dimension and position information.

    * detection confidence.

    * label name.

    * class id.

    * text to be displayed on the box around the object.

* This obj_meta is added to the frame.

**4.2 - ssd_parser.py**

**4.2.1 - nvds_infer_parse_custom_tf_ssd**

* The information of 4 layers is retrieved output_layer_info.

* A list of objects is made by calling several times **make_nodi**.

* This object list is cleaned with nms by calling **cluster_and_fill_detection_output_nms**.

* The list of objects is returned.

**4.2.2 - make_nodi**

* An object res is created with pyds.NvDsInferObjectDetectionInfo() .

* The detection confidence and class id, and dimensions are stored in it.

* The box dimensions are clipped between 0 and 1.

* A test to see the box dimension is superior to what has been given in box_size_param is performed. Is so, res is returned, otherwise, None is returned.

**4.3 - nms.py**

**4.3.1 - cluster_and_fill_detection_output_nms**

* An empty list clustered_b_boxes is created.

* A dictionary per_class_object_list with the class id as key and a list as value is created. Then all the elements of object_list are stored in this dictionary sorted by class.

* Each list in per_class_object_list, is sorted by confidence.

* Then non_maximum_suppression is applied to keep only selected indices.

* The objects related to these indices are stored in clustered_b_boxes.

* If the number of objects stored in clustered_b_boxes  is superior to top_k, then clustered_b_boxes is sorted according to the confidence and the first top_k objects are returned.

**4.3.2 - non_maximum_suppression**

* An empty list indices is created.

* For all the boxes if 2 of them overlap of nms_threshold, the box with the lowest confidence is removed. This overlap is computed with **compute_iou**.

**4.3.3 - compute_iou**

* The 1-dimension overlap for x and y axis are computed.

* The 2 boxes area are computed.

* The intersection and the union of the 2 boxes are computed.

* The intersection divided by the union is returned.

