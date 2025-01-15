SPDX-FileCopyrightText: Copyright (c) 2018-2021 NVIDIA CORPORATION & AFFILIATES. All rights reserved.
SPDX-License-Identifier: Apache-2.0

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.

# Integration tests

## Purpose
Testing deepstream python bindings working in a pipeline.


## Usage
```
cd tests/integration
pytest test.py
```
### notes
* Since full pipelines are tested, testing takes more time than direct function call
* Video output of pipeline should be set to fakesink to allow efficient automated testing

## Running tests for python specific version
### Prerequisite
Installing:
* python virtual env for the requested python version
* dependencies listed in the `bindings` folder
* pytest
* ReID model for tracker
    ```
    cd /opt/nvidia/deepstream/deepstream/samples/models
    mkdir Tracker && cd Tracker
    wget --content-disposition 'https://api.ngc.nvidia.com/v2/models/org/nvidia/team/tao/reidentificationnet/deployable_v1.2/files?redirect=true&path=resnet50_market1501_aicity156.onnx' -O resnet50_market1501_aicity156.onnx
    export PATH=$PATH:/usr/src/tensorrt/bin
    trtexec --minShapes=input:1x3x256x128 --optShapes=input:8x3x256x128 --maxShapes=input:16x3x256x128  --fp16 --saveEngine=resnet50_market1501_aicity156.onnx_b16_gpu0_fp16.engine --onnx=resnet50_market1501_aicity156.onnx
    ```
### step1

Compile bindings as per [Python Binding instructions](../../bindings)

### step2
#### Python 3.10
```
apt install python3.10-venv
python3.10 -m venv env
```
### step3
```
. env/bin/activate
pip install /opt/nvidia/deepstream/deepstream/sources/deepstream_python_apps/bindings/dist/pyds-1.2.0*.whl
pip install pytest pygobject cuda-python numpy==1.26.0
cd /opt/nvidia/deepstream/deepstream/sources/deepstream_python_apps/tests/integration
pytest test.py
```

## Adding more tests

In order to add more test let's have a quick overview of the architecture

### Pipeline
* Generic pipeline
This abstract class handles the common pipeline behavior required to process
 pipeline elements.
* Simple pipeline no output
This pipeline processes 1 video stream and 1 probe and its output is hidden.
It is derived from Generic Pipeline, so that only the pipeline element
creation and linking is performed


From the above derived pipelines you can make your own by modifying and
linking the new elements.

### Writing a new test

You can copy an existing test from `tests/bindings/test.py` and modify it.
Tests are written in 3 parts:
* Data initialization
* Executing behavior
* Checking results
