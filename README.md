# DeepStream Python Apps

This repository contains Python bindings and sample applications for the [DeepStream SDK](https://developer.nvidia.com/deepstream-sdk).  

The bindings and apps are currently in *Alpha* at [v0.5](../..//releases/tag/v0.5-alpha). API changes are expected in future releases.  
SDK version supported: 4.0.1  

Download the latest release package complete with bindings and sample applications from the [release section](../../releases).  

* [Python Bindings](#metadata_bindings)
* [Sample Applications](#sample_applications)

<a name="metadata_bindings"></a>
## Python Bindings

DeepStream pipelines can be constructed using Gst Python, the GStreamer framework's Python bindings. For accessing DeepStream MetaData, 
Python bindings are provided in the form of a compiled module. Download these bindings [here](https://developer.nvidia.com/deepstream-download#python_bindings). This module is generated using [Pybind11](https://github.com/pybind/pybind11).  

<p align="center">
<img src=".python-app-pipeline.png" alt="bindings pipeline" height="400px"/>
</p>

These bindings support a Python interface to the MetaData structures and functions. Usage of this interface is documented in the [HOW-TO Guide](HOWTO.md) and demonstrated in the sample applications.  
The current bindings are limited to the [NvDsBatchMeta](https://docs.nvidia.com/metropolis/deepstream/plugin-manual/index.html#page/DeepStream_Plugin_Manual%2Fdeepstream_plugin_metadata.03.2.html%23) hierarchy. Image data access is currently not included.  

<a name="sample_applications"></a>
## Sample Applications

Sample applications provided here demonstrate how to work with DeepStream pipelines using Python.  
The sample applications require [MetaData Bindings](#metadata_bindings) to work.  

To run the sample applications or write your own, please consult the [HOW-TO Guide](HOWTO.md)  

<p align="center">
<img src=".test3-app.png" alt="deepstream python app screenshot" height="400px"/>
</p>

We currently provide four sample applications:
* [deepstream-test1](apps/deepstream-test1) -- 4-class object detection pipeline
* [deepstream-test2](apps/deepstream-test2) -- 4-class object detection, tracking and attribute classification pipeline
* [deepstream-test3](apps/deepstream-test3) -- multi-stream pipeline performing 4-class object detection
* [deepstream-test4](apps/deepstream-test4) -- msgbroker for sending analytics results to the cloud

These are Python versions of the first four test applications included in the DeepStream SDK.  

Detailed application information is provided in each application's subdirectory under [apps](apps).  


