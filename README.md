# DeepStream Python Apps

This repository contains Python bindings and sample applications for the [DeepStream SDK](https://developer.nvidia.com/deepstream-sdk).  

SDK version supported: 7.0

<b>This release only supports Ubuntu 22.04 for DeepStreamSDK 7.0 with Python 3.10 and [gst-python](3rdparty/gst-python/) 1.20.3! Ubuntu 20.04 for DeepStreamSDK 6.3 with Python 3.8 support is NOW DEPRECATED</b>

The bindings sources along with build instructions are available under [bindings](bindings)! We include one [guide](bindings/BINDINGSGUIDE.md) for contributing to bindings and another [guide](bindings/CUSTOMUSERMETAGUIDE.md) for advanced use-cases such as writing bindings for custom data structures. 

Please report any issues or bugs on the [DeepStream SDK Forums](https://devtalk.nvidia.com/default/board/209). This enables the DeepStream community to find help at a central location.

- [DeepStream Python Apps](#deepstream-python-apps)
  - [Setup](#setup)
  - [Python Bindings](#python-bindings)
    - [Python Bindings Breaking API Change](#python-bindings-breaking-api-change)
  - [Sample Applications](#sample-applications)

## Setup
Once you have DeepStreamSDK pre-requisites and DeepStreamSDK installed on the system, navigate to <DS_ROOT>/sources/ dir which is /opt/nvidia/deepstream/deepstream/sources/ and git clone deepstream_python_apps repo here.

The latest bindings can be installed from [release section](../../releases).
You can also build the bindings from source using the instructions in the [bindings readme](bindings/README.md) if needed.

<a name="metadata_bindings"></a>
## Python Bindings

DeepStream pipelines can be constructed using Gst Python, the GStreamer framework's Python bindings. For accessing DeepStream MetaData, 
Python [bindings](bindings) are provided as part of this repository. This module is generated using [Pybind11](https://github.com/pybind/pybind11).

<p align="center">
<img src=".python-app-pipeline.png" alt="bindings pipeline" height="600px"/>
</p>

These bindings support a Python interface to the MetaData structures and functions. Usage of this interface is documented in the [HOW-TO Guide](HOWTO.md) and demonstrated in the sample applications.  

### Python Bindings Breaking API Change
The binding for function alloc_nvds_event_msg_meta() now expects a NvDsUserMeta pointer which the NvDsEventMsgMeta is associated with. Please refer to [deepstream-test4](apps/deepstream-test4) and [bindschema.cpp](bindings/src/bindschema.cpp) for reference.

<a name="sample_applications"></a>
## Sample Applications

Sample applications provided here demonstrate how to work with DeepStream pipelines using Python.  
The sample applications require [MetaData Bindings](#metadata_bindings) to work.  

To run the sample applications or write your own, please consult the [HOW-TO Guide](HOWTO.md)  

<p align="center">
<img src=".test3-app.png" alt="deepstream python app screenshot" height="400px"/>
</p>

We currently provide the following sample applications:
* [deepstream-test1](apps/deepstream-test1) -- 4-class object detection pipeline, also demonstrates support for new nvstreammux
* [deepstream-test2](apps/deepstream-test2) -- 4-class object detection, tracking and attribute classification pipeline
* [deepstream-test3](apps/deepstream-test3) -- multi-stream pipeline performing 4-class object detection, also supports triton inference server, no-display mode, file-loop and silent mode
* [deepstream-test4](apps/deepstream-test4) -- msgbroker for sending analytics results to the cloud
* [deepstream-imagedata-multistream](apps/deepstream-imagedata-multistream) -- multi-stream pipeline with access to image buffers
* [deepstream-ssd-parser](apps/deepstream-ssd-parser) -- SSD model inference via Triton server with output parsing in Python
* [deepstream-test1-usbcam](apps/deepstream-test1-usbcam) -- deepstream-test1 pipeline with USB camera input
* [deepstream-test1-rtsp-out](apps/deepstream-test1-rtsp-out) -- deepstream-test1 pipeline with RTSP output, demonstrates adding software encoder option to support Jetson Orin Nano
* [deepstream-opticalflow](apps/deepstream-opticalflow) -- optical flow and visualization pipeline with flow vectors returned in NumPy array
* [deepstream-segmentation](apps/deepstream-segmentation) -- segmentation and visualization pipeline with segmentation mask returned in NumPy array
* [deepstream-nvdsanalytics](apps/deepstream-nvdsanalytics) -- multistream pipeline with analytics plugin
* [runtime_source_add_delete](apps/runtime_source_add_delete) -- add/delete source streams at runtime
* [deepstream-imagedata-multistream-redaction](apps/deepstream-imagedata-multistream-redaction) -- multi-stream pipeline with face detection and redaction
* [deepstream-rtsp-in-rtsp-out](apps/deepstream-rtsp-in-rtsp-out) -- multi-stream pipeline with RTSP input/output - has command line option "--rtsp-ts" for configuring the RTSP source to attach the timestamp rather than the streammux
* [deepstream-preprocess-test](apps/deepstream-preprocess-test) -- multi-stream pipeline using nvdspreprocess plugin with custom ROIs
* [deepstream-demux-multi-in-multi-out](apps/deepstream-demux-multi-in-multi-out) -- multi-stream pipeline using nvstreamdemux plugin to generated separate buffer outputs
* [deepstream-imagedata-multistream-cupy](apps/deepstream-imagedata-multistream-cupy) -- access imagedata buffer from GPU in a multistream source as CuPy array - x86 only
* [deepstream-segmask](apps/deepstream-segmask) -- access and interpret segmentation mask information from NvOSD_MaskParams
* [deepstream-custom-binding-test](apps/deepstream-custom-binding-test) -- demonstrate usage of NvDsUserMeta for attaching custom data structure - see also the [Custom User Meta Guide](bindings/CUSTOMUSERMETAGUIDE.md)


Detailed application information is provided in each application's subdirectory under [apps](apps).  


