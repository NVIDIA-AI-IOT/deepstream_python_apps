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
### step1
```
mkdir -p bindings/build
cd bindings/build
```
### step2
#### Python 3.6
```
cmake ..  -DPYTHON_MINOR_VERSION=6
make
python3.6 -m venv env
```
#### Python 3.8
```
cmake ..  -DPYTHON_MINOR_VERSION=8
make
python3.8 -m venv env
```
### step3
```
. env/bin/activate
pip install pyds-1.1.4-py3-none-*.whl
pip install pytest
cd ../../tests/integration
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
