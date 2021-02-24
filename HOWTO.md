# How To --
## Run the Sample Applications 
## Write a DeepStream Application in Python

This guide provides resources for DeepStream application development in Python.

* [Prerequisites](#prereqs)
* [Running Sample Applications](#run_samples)
* [Pipeline Construction](#pipeline_construction)
* [MetaData Access](#metadata_access)
* [Image Data Access](#imagedata_access)
* [Custom Inference Output Parsing](apps/deepstream-ssd-parser/custom_parser_guide.md)
* [FAQ and Troubleshooting](FAQ.md)

<a name="prereqs"></a>
## Prerequisites

* Ubuntu 18.04
* [DeepStream SDK 5.1](https://developer.nvidia.com/deepstream-download) or later
* Python 3.6
* [Gst Python](https://gstreamer.freedesktop.org/modules/gst-python.html) v1.14.5

Gst python should be already installed on Jetson.  
If missing, install with the following steps:
```
   $ sudo apt-get install python-gi-dev
   $ export GST_LIBS="-lgstreamer-1.0 -lgobject-2.0 -lglib-2.0"
   $ export GST_CFLAGS="-pthread -I/usr/include/gstreamer-1.0 -I/usr/include/glib-2.0 -I/usr/lib/x86_64-linux-gnu/glib-2.0/include"
   $ git clone https://github.com/GStreamer/gst-python.git
   $ cd gst-python
   $ git checkout 1a8f48a
   $ ./autogen.sh PYTHON=python3
   $ ./configure PYTHON=python3
   $ make
   $ sudo make install
```

<a name="run_samples"></a>
## Running Sample Applications

Clone the deepstream_python_apps repo under <DeepStream 5.1 ROOT>/sources:
git clone https://github.com/NVIDIA-AI-IOT/deepstream_python_apps

This will create the following directory:  
```<DeepStream 5.1 ROOT>/sources/deepstream_python_apps```  

The Python apps are under the "apps" directory.  
Go into each app directory and follow instructions in the README.  

NOTE: The app configuration files contain relative paths for models.  

<a name="pipeline_construction"></a>
## Pipeline Construction

DeepStream pipelines can be constructed using Gst Python, the GStreamer framework's Python bindings.  
See [sample applications](apps/) main functions for pipeline construction examples.  

<a name="metadata_access"></a>
## MetaData Access

DeepStream MetaData contains inference results and other information used in analytics. The MetaData is attached to the Gst Buffer received by each pipeline component. The metadata format is described in detail in the [SDK MetaData documentation](https://docs.nvidia.com/metropolis/deepstream/plugin-manual/index.html#page/DeepStream_Plugin_Manual%2Fdeepstream_plugin_metadata.03.1.html) and [API Guide](https://docs.nvidia.com/metropolis/deepstream/python-api/index.html).  

The SDK MetaData library is developed in C/C++. Python bindings provide access to the MetaData from Python applications. The bindings are provided in a compiled module, available for x86_64 and Jetson platforms. This module, pyds.so, is available as part of the DeepStream SDK installation under <DeepStream Root>/lib directory.  

The sample applications gets the import path for this module through common/utils.py. A setup.py is also included for installing the module into standard path:  
cd /opt/nvidia/deepstream/deepstream/lib  
python3 setup.py install  

This is currently not automatically done through the SDK installer because python usage is optional.  

The bindings generally follow the same API as the underlying C/C++ library, with a few exceptions detailed in sections below.  

#### Memory Management

Memory for MetaData is shared by the Python and C/C++ code paths. For example, a MetaData item may be added by a probe function written in Python, and needs to be accessed by a downstream plugin written in C/C++. The deepstream-test4 app contains such usage. The Python garbage collector does not have visibility into memory references in C/C++, and therefore cannot safely manage the lifetime of such shared memory. Because of this complication, Python access to MetaData memory is typically achieved via references without claiming ownership.

#### Allocations

When MetaData objects are allocated in Python, an allocation function is provided by the bindings to ensure proper memory ownership of the object. If the constructor is used, the the object will be claimed by the garbage collector when its Python references terminate. However, the object will still need to be accessed by C/C++ code downstream, and therefore must persist beyond those Python references.  

Example:
To allocate an NvDsEventMsgMeta instance, use this:  
```python
msg_meta = pyds.alloc_nvds_event_msg_meta() # get reference to allocated instance without claiming memory ownership  
```
NOT this:  
```python
msg_meta = NvDsEventMsgMeta() # memory will be freed by the garbage collector when msg_meta goes out of scope in Python  
```

Allocators are available for the following structs:  
```python
NvDsVehicleObject: alloc_nvds_vehicle_object()  
NvDsPersonObject:  alloc_nvds_person_object()  
NvDsFaceObject:    alloc_nvds_face_object()  
NvDsEventMsgMeta:  alloc_nvds_event_msg_meta()  
NvDsEvent:         alloc_nvds_event()  
NvDsPayload:       alloc_nvds_payload()  
Generic buffer:    alloc_buffer(size)  
```

#### String Access

Some MetaData structures contain string fields. These are accessable in the following manner:  

##### Setting String Fields
Setting a string field results in the allocation of a string buffer in the underlying C++ code.  
```obj.type = "Type"```  
This will cause a memory buffer to be allocated, and the string "TYPE" will be copied into it.  
This memory is owned by the C code and will be freed later. To free the buffer in Python code, use:  
```pyds.free_buffer(obj.type)```  

NOTE: NvOSD_TextParams.display_text string now gets freed automatically when a new string is assigned.

##### Reading String Fields
Directly reading a string field returns C address of the field in the form of an int, e.g.:  
```python
obj = pyds.NvDsVehicleObject.cast(data);
print(obj.type)
```
This will print an int representing the address of obj.type in C (which is a char*).  

To retrieve the string value of this field, use ```pyds.get_string()```, e.g.:  
```python
print(pyds.get_string(obj.type))
```

#### Casting

Some MetaData instances are stored in GList form. To access the data in a GList node, the data field needs to be cast to the appropriate structure. This casting is done via cast() member function for the target type:
```python
NvDsBatchMeta.cast
NvDsFrameMeta.cast
NvDsObjectMeta.cast
NvDsUserMeta.cast
NvDsClassifierMeta.cast
NvDsDisplayMeta.cast
NvDsLabelInfo.cast
NvDsEventMsgMeta.cast
NvDsVehicleObject.cast
NvDsPersonObject.cast
```

In version v0.5, standalone cast functions were provided. Those are now deprecated and superseded by the cast() functions above:
```python
glist_get_nvds_batch_meta
glist_get_nvds_frame_meta
glist_get_nvds_object_meta
glist_get_nvds_user_meta
glist_get_nvds_classifier_meta
glist_get_nvds_display_meta
glist_get_nvds_label_info
glist_get_nvds_event_msg_meta
glist_get_nvds_vehicle_object
glist_get_nvds_person_object
```

Example:
```python
l_frame = batch_meta.frame_meta_list
frame_meta = pyds.NvDsFrameMeta.cast(l_frame.data)
```

#### Callback Function Registration

Custom MetaData added to NvDsUserMeta require custom copy and release functions. The MetaData library relies on these custom functions to perform deep-copy of the custom structure, and free allocated resources. These functions are registered as callback function pointers in the NvDsUserMeta structure.

Callback functions are registered using these functions:  
```python
pyds.set_user_copyfunc(NvDsUserMeta_instance, copy_function)
pyds.set_user_releasefunc(NvDsUserMeta_instance, free_func)
```

*NOTE*: Callbacks need to be unregistered with the bindings library before the application exits. The bindings library currently keeps global references to the registered functions, and these cannot last beyond bindings library unload which happens at application exit. Use the following function to unregister all callbacks:
```pyds.unset_callback_funcs()```  

See the deepstream-test4 sample application for an example of callback registration and unregistration.  

Limitation: the bindings library currently only supports a single set of callback functions for each application. The last registered function will be used.  

#### Optimizations and Utilities

Python interpretation is generally slower than running compiled C/C++ code. To provide better performance, some operations are implemented in C and exposed via the bindings interface. This is currently experimental and will expand over time.

The following optimized functions are available:

##### pyds.NvOSD_ColorParams.set(double red, double green, double blue, double alpha)

This is a simple function that performs the same operations as the following:  
```python
txt_params.text_bg_clr.red = red
txt_params.text_bg_clr.green = green
txt_params.text_bg_clr.blue = blue
txt_params.text_bg_clr.alpha = alpha
```

These are performend on each object in deepstream_test_4.py, causing the aggregate processing time to slow down the pipeline. Pushing this function into the C layer helps to increase performance.

##### generate_ts_rfc3339 (buffer, buffer_size)

This function populates the input buffer with a timestamp generated according to RFC3339:  
```%Y-%m-%dT%H:%M:%S.nnnZ\0```

<a name="imagedata_access"></a>
## Image Data Access

Decoded images are accessible as NumPy arrays via the `get_nvds_buf_surface` function. This function is documented in the [API Guide](https://docs.nvidia.com/metropolis/deepstream/5.1/python-api/index.html).
Please see the [deepstream-imagedata-multistream](apps/deepstream-imagedata-multistream) sample application for an example of image data usage.
