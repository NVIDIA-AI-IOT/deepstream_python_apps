# DeepStream Python Apps

This repository contains Python bindings and sample applications for the [DeepStream SDK](https://developer.nvidia.com/deepstream-sdk).  

SDK version supported: 5.1  

Download the latest release package complete with bindings and sample applications from the [release section](../../releases).  

Please report any issues or bugs on the [Deepstream SDK Forums](https://devtalk.nvidia.com/default/board/209).  

* [Python Bindings](#metadata_bindings)
* [Sample Applications](#sample_applications)

<a name="metadata_bindings"></a>
## Python Bindings

DeepStream pipelines can be constructed using Gst Python, the GStreamer framework's Python bindings. For accessing DeepStream MetaData, 
Python bindings are provided in the form of a compiled module which is included in the DeepStream SDK. This module is generated using [Pybind11](https://github.com/pybind/pybind11).  

<p align="center">
<img src=".python-app-pipeline.png" alt="bindings pipeline" height="600px"/>
</p>

These bindings support a Python interface to the MetaData structures and functions. Usage of this interface is documented in the [HOW-TO Guide](HOWTO.md) and demonstrated in the sample applications.  
This release adds bindings for decoded image buffers (NvBufSurface) as well as inference output tensors (NvDsInferTensorMeta).

<a name="sample_applications"></a>
## Sample Applications

Sample applications provided here demonstrate how to work with DeepStream pipelines using Python.  
The sample applications require [MetaData Bindings](#metadata_bindings) to work.  

To run the sample applications or write your own, please consult the [HOW-TO Guide](HOWTO.md)  

<p align="center">
<img src=".test3-app.png" alt="deepstream python app screenshot" height="400px"/>
</p>

We currently provide the following sample applications:
* [deepstream-test1](apps/deepstream-test1) -- 4-class object detection pipeline
* [deepstream-test2](apps/deepstream-test2) -- 4-class object detection, tracking and attribute classification pipeline
* [deepstream-test3](apps/deepstream-test3) -- multi-stream pipeline performing 4-class object detection
* [deepstream-test4](apps/deepstream-test4) -- msgbroker for sending analytics results to the cloud
* [deepstream-imagedata-multistream](apps/deepstream-imagedata-multistream) -- multi-stream pipeline with access to image buffers
* [deepstream-ssd-parser](apps/deepstream-ssd-parser) -- SSD model inference via Triton server with output parsing in Python
* [deepstream-test1-usbcam](apps/deepstream-test1-usbcam) -- deepstream-test1 pipeline with USB camera input
* [deepstream-test1-rtsp-out](apps/deepstream-test1-rtsp-out) -- deepstream-test1 pipeline with RTSP output
* [deepstream-opticalflow](apps/deepstream-opticalflow) -- optical flow and visualization pipeline with flow vectors returned in NumPy array
* [deepstream-segmentation](apps/deepstream-segmentation) -- segmentation and visualization pipeline with segmentation mask returned in NumPy array  
* [deepstream-nvdsanalytics](apps/deepstream-nvdsanalytics) -- multistream pipeline with analytics plugin  

Of these applications, the following have been updated or added in this release:
* deepstream-test2: added option to enable output of past frame tracking data
* deepstream-test4: callback functions are registered only once to avoid race condition
* deepstream-imagedata-multistream: the probe function now modifies images in-place in addition to saving copies of them  
* deepstream-opticalflow: new sample application to demonstrate optical flow functionality
* deepstream-segmentation: new sample application to demonstrate segmentation functionality
* deepstream-nvdsnalaytics: new sample application to demonstrate analytics functionality

Detailed application information is provided in each application's subdirectory under [apps](apps).  


