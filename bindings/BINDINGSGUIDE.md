## Python binding tutorial
This document is a guide for how to write Python bindings for the DeepStream Python API. For advanced use-cases such as writing bindings for your own custom data-structures to be attached to NvDsUserMeta as meta_data with a sample test app, please refer to [CUSTOMUSERMETAGUIDE](CUSTOMUSERMETAGUIDE.md) Python bindings are written using the [pybind11](https://github.com/pybind/pybind11) header library. Please review their documentation [here](https://pybind11.readthedocs.io/en/stable/basics.html). See below the table of contents for this guide:
- [Python binding tutorial](#python-binding-tutorial)
  - [Setup](#setup)
  - [Directory structure](#directory-structure)
  - [Brief overview of the typical procedure](#brief-overview-of-the-typical-procedure)
  - [How to write bindings](#how-to-write-bindings)
    - [Binding a struct](#binding-a-struct)
      - [Binding Plain Old Data (POD) Types](#binding-plain-old-data-pod-types)
      - [Binding a C-style string](#binding-a-c-style-string)
      - [Adding a member function](#adding-a-member-function)
    - [Binding an enumerator](#binding-an-enumerator)
    - [Binding a function](#binding-a-function)
      - [Binding an existing function](#binding-an-existing-function)
      - [Adding a new function](#adding-a-new-function)
        - [Note on arrays](#note-on-arrays)
    - [Note on strings](#note-on-strings)
  - [How to write docstrings](#how-to-write-docstrings)
    - [Docstring for a struct](#docstring-for-a-struct)
    - [Docstring for an enumerator](#docstring-for-an-enumerator)
    - [Docstring for a function](#docstring-for-a-function)
  - [How to send a custom event from Python to downstream elements?](#how-to-send-a-custom-event-from-python-to-downstream-elements)
### Setup
Follow the instructions in [README.md](README.md) to install prerequisites and learn how to compile the bindings.
### Directory structure
First, we present the directory stucture. Relevant subdirectories for writing bindings code are in bold. 
<pre>
.
├── <b>docstrings</b>
├── <b>include</b>
│   ├── <b>bind</b>
│   └── nvds
├── packaging
├── qemu_docker
└── <b>src</b>
</pre>
* ```docstrings``` - Docstrings are declared and defined in header files in this folder
<pre>
.
├── <b>docstrings</b>
    ├── analyticsmetadoc.h
    ├── customdoc.h
    ├── functionsdoc.h
    ├── gstnvdsmetadoc.h
    ├── meta360doc.h
    ├── nvbufsurfacedoc.h
    ├── nvdsinferdoc.h
    ├── nvdsmetadoc.h
    ├── nvosddoc.h
    ├── opticalflowdoc.h
    ├── schemadoc.h
    └── trackermetadoc.h
</pre>
* ```include``` - Bindings functions are declared in header files in this folder, separated by corresponding C API header files in ```<DEEPSTREAM ROOT>/sources/includes/```
<pre>
.
├── <b>include</b>
    ├── <b>bind</b>
    │   ├── bindanalyticsmeta.hpp
    │   ├── bindfunctions.hpp
    │   ├── bindgstnvdsmeta.hpp
    │   ├── bindmeta360.hpp
    │   ├── bindnvbufsurface.hpp
    │   ├── bindnvdsinfer.hpp
    │   ├── bindnvdsmeta.hpp
    │   ├── bindnvosd.hpp
    │   ├── bindopticalflow.hpp
    │   ├── bindschema.hpp
    │   ├── bind_string_property_definitions.h
    │   └── bindtrackermeta.hpp
    └── nvds
    │   └── nvds_360d_meta.h
    ├── pyds.hpp
    └── utils.hpp
</pre>
* ```src``` - Bindings functions are defined in cpp source files in this folder, along with utilities and the definition of the pybind11 module.
<pre>
.
└── <b>src</b>
    └── custom_binding
    │   ├── bindcustom.cpp
    │   └── include
    │       ├── bindcustom.hpp
    │       └── custom_data.hpp
    ├── bindanalyticsmeta.cpp
    ├── bindfunctions.cpp
    ├── bindgstnvdsmeta.cpp
    ├── bindmeta360.cpp
    ├── bindnvbufsurface.cpp
    ├── bindnvdsinfer.cpp
    ├── bindnvdsmeta.cpp
    ├── bindnvosd.cpp
    ├── bindopticalflow.cpp
    ├── bindschema.cpp
    ├── bindtrackermeta.cpp
    ├── pyds.cpp
    └── utils.cpp
</pre>


### Brief overview of the typical procedure
If adding missing bindings for an existing C API header file in PyDS bindings:

1. Find the source file under ```src``` corresponding to the header of interest.
2. Add bindings code to file inside the existing function definition.
3. Add docstrings to corresponding header file in ```docstrings```, creating any new namespaces following the convention.

If adding bindings for an unbound C API header file which is not a part of PyDS bindings:
1. Create a new header file under ```include/bind/``` following the ```bind{header_name}.hpp``` file name convention.
2. Declare the bindings function in the header file following the ```bind{header_name}``` function name convention under the ```pydeepstream``` namespace.
3. Create a new source file under ```src```, following the ```bind{header_name}.cpp``` file name convention. 
4. Define the function previously declared in the new header file under the ```pydeepstream``` namespace.
5. Add a call to the function in ```src/pyds.cpp```.
5. Create new header file for docstrings under ```docstrings``` following the ```{header_name}docs.h``` convention.
6. Add docstrings to corresponding header file in ```docstrings```, creating any new namespaces following the convention.
7. Add new bindings source file name to ```../docs/bindings_file_list.txt```, run ```../docs/parse_bindings.py```, and update ```../docs/index.rst``` with the newly generated toctree rst name accordingly.

For functions, add changes to [```../docs/PYTHON_API/Methods/methodsdoc.rst```](../docs/PYTHON_API/Methods/methodsdoc.rst) as needed.

### How to write bindings
#### Binding a struct
Suppose that the bindings for the ```NvDsObjectMeta``` data structure were not yet written, along with the associated bindings header [```include/bind/bindnvdsmeta.hpp```](include/bind/bindnvdsmeta.hpp), source file [```src/bindnvdsmeta.cpp```](src/bindnvdsmeta.cpp), and docstrings. 

First, we search the [C API documentation](https://docs.nvidia.com/metropolis/deepstream/sdk-api/index.html) for ```NvDsObjectMeta``` and find the header file to which it belongs: ```nvdsmeta.h```. Following the ```bind{header_name}.hpp``` convention, we create the file [```include/bind/bindnvdsmeta.hpp```](include/bind/bindnvdsmeta.hpp) with the following contents:

```c++
#include "pyds.hpp" // Include this "base" header file for all other dependencies
#include "../docstrings/pydocumentation.h" // Include the header file for the docstrings of this submodule

namespace py = pybind11;

namespace pydeepstream {
    void bindnvdsmeta(py::module &m); // Declare the bindings function for this submodule
}
```
Then, we create the corresponding source file [```src/bindnvdsmeta.cpp```](src/bindnvdsmeta.cpp):
```c++
#include "bind_string_property_definitions.h"
#include "bindnvdsmeta.hpp" // Include the corresponding header file

namespace py = pybind11;

namespace pydeepstream {

    void bindnvdsmeta(py::module &m) {} // Define the bindings function declared in the header file
}
```

We would put all bindings code for the C API declared in ```<DEEPSTREAM ROOT>/sources/includes/nvdsmeta.h``` into this function. 

Let's write our first binding! To bind a C-style struct, we make a call to pybind11's ```class_```. We pass in the module, the name of the struct, and the docstring for the struct:

```c++
void bindnvdsmeta(py::module &m) {
    py::class_<NvDsObjectMeta>(m, "NvDsObjectMeta",
                                pydsdoc::nvmeta::ObjectMetaDoc::descr)
        .def(py::init<>()); // Constructor wrapper, empty for struct
}
```

With the above code, the ```NvDsObjectMeta``` struct is now exposed to the Python API, but none of its data members are. To start, we may look directly in the header file for our struct, or, for more human readable information, we can look at the C API documentation for [```NvDsObjectMeta```](https://docs.nvidia.com/metropolis/deepstream/sdk-api/struct__NvDsObjectMeta.html):
<pre>
<b>Data Fields</b>
<b>NvDsBaseMeta 	base_meta</b>
 
<b>struct _NvDsObjectMeta * 	parent</b>
 	Holds a pointer to the parent NvDsObjectMeta.
 
<b>gint 	unique_component_id</b>
 	Holds a unique component ID that identifies the metadata in this structure.
 
<b>gint 	class_id</b>
 	Holds the index of the object class inferred by the primary detector/classifier.
 
<b>guint64 	  object_id</b>
 	Holds a unique ID for tracking the object.
 
<b>NvDsComp_BboxInfo 	detector_bbox_info</b>
 	Holds a structure containing bounding box parameters of the object when detected by detector.
 
<b>NvDsComp_BboxInfo 	tracker_bbox_info</b>
 	Holds a structure containing bounding box coordinates of the object when processed by tracker.
 
<b>gfloat 	confidence</b>
 	Holds a confidence value for the object, set by the inference component.
 
<b>gfloat 	tracker_confidence</b>
 	Holds a confidence value for the object set by nvdcf_tracker.
 
<b>NvOSD_RectParams 	rect_params</b>
 	Holds a structure containing positional parameters of the object processed by the last component that updates it in the pipeline. 

<b>NvOSD_MaskParams 	mask_params</b>
 	Holds mask parameters for the object. 
 
<b>NvOSD_TextParams 	text_params</b>
 	Holds text describing the object. 
 
<b>gchar 	obj_label [MAX_LABEL_SIZE]</b>
 	Holds a string describing the class of the detected object. 
 
<b>NvDsClassifierMetaList * 	classifier_meta_list</b>
 	Holds a pointer to a list of pointers of type NvDsClassifierMeta. 
 
<b>NvDsUserMetaList * 	obj_user_meta_list</b>
 	Holds a pointer to a list of pointers of type NvDsUserMeta. 
 
<b>gint64 	misc_obj_info [MAX_USER_FIELDS]</b>
 	Holds additional user-defined object information. 
 
<b>gint64 	reserved [MAX_RESERVED_FIELDS]</b>
 	For internal use. 
</pre>

##### Binding Plain Old Data (POD) Types
We can directly expose a POD data member using the ```class_::def_readwrite()``` method. For example, to bind the first member **base_meta**, we pass in the name of the member along with a referennce to the member:
```c++
void bindnvdsmeta(py::module &m) {
    py::class_<NvDsObjectMeta>(m, "NvDsObjectMeta",
                                pydsdoc::nvmeta::ObjectMetaDoc::descr)
        .def(py::init<>()); // Constructor wrapper, empty for struct
        .def_readwrite("base_meta", &NvDsObjectMeta::base_meta);
}
```
Note that ```NvDsBaseMeta``` does not need to be bound for this binding to work. However, we will be unable to access any of **base_meta**'s data members as an ```NvDsBaseMeta``` instance until the ```NvDsBaseMeta``` data structure is also bound.

We can similarly bind the **unique_component_id**, **class_id**, **object_id**, **detector_bbox_info**, **tracker_bbox_info**, **confidence**, **tracker_confidence**, **rect_params**, **mask_params**, and **text_params** data members.

```c++
void bindnvdsmeta(py::module &m) {
    py::class_<NvDsObjectMeta>(m, "NvDsObjectMeta",
                                pydsdoc::nvmeta::ObjectMetaDoc::descr)
        .def(py::init<>()); // Constructor wrapper, empty for struct
        .def_readwrite("base_meta", &NvDsObjectMeta::base_meta);
        .def_readwrite("unique_component_id",
                    &NvDsObjectMeta::unique_component_id)
        .def_readwrite("class_id", &NvDsObjectMeta::class_id)
        .def_readwrite("object_id", &NvDsObjectMeta::object_id)
        .def_readwrite("detector_bbox_info",
                        &NvDsObjectMeta::detector_bbox_info)
        .def_readwrite("tracker_bbox_info",
                        &NvDsObjectMeta::tracker_bbox_info)
        .def_readwrite("confidence", &NvDsObjectMeta::confidence)
        .def_readwrite("tracker_confidence",
                        &NvDsObjectMeta::tracker_confidence)
        .def_readwrite("rect_params", &NvDsObjectMeta::rect_params)
        .def_readwrite("mask_params", &NvDsObjectMeta::mask_params)
        .def_readwrite("text_params", &NvDsObjectMeta::text_params);
}
```
##### Binding a C-style string
The **obj_label** data member is a C-style string, i.e. an array of ```char```, and thus needs extra steps to be properly bound. Instead of using the ```class_::def_readwrite()``` method, we make a call to ```class_::def_property()```, which allows us to define setter and getter functions for the data member.
```c++
void bindnvdsmeta(py::module &m) {
    py::class_<NvDsObjectMeta>(m, "NvDsObjectMeta",
                                pydsdoc::nvmeta::ObjectMetaDoc::descr)
        ...
        .def_property("obj_label",
                    [](const NvDsObjectMeta &self)->std::string { // Getter function
                        return std::string(self.obj_label); // Return the char array as a std::string
                    },
                    [](TYPE &self, std::string str) { // Setter function
                        int strSize = str.size();
                        str.copy(self.obj_label, strSize); // Copy the string into the original array
                    },
                    py::return_value_policy::reference); // Set return value policy to "reference" so ownership remains in C++
}
```
Note that a _return value policy_ must be set. In this case, we want to prevent the Python side from taking ownership, so use ```py::return_value_policy::reference```.  Please see pybind11's documentation on [return value policies](https://pybind11.readthedocs.io/en/stable/advanced/functions.html#return-value-policies) for more details. See also the [Note on strings](#note-on-strings).

The [```include/bind/bind_string_property_definitions.h```](include/bind/bind_string_property_definitions.h) header file includes this macro definition:
```c++
#define STRING_CHAR_ARRAY(TYPE, FIELD)                             \
        [](const TYPE &self)->std::string {                        \
            return std::string(self.FIELD);                        \
        },                                                         \
        [](TYPE &self, std::string str) {                          \
            int strSize = str.size();                              \
            str.copy(self.FIELD, strSize);                         \
        },                                                         \
        py::return_value_policy::reference

```
So, the bindings code may be re-written as:

```c++
void bindnvdsmeta(py::module &m) {
    py::class_<NvDsObjectMeta>(m, "NvDsObjectMeta",
                                pydsdoc::nvmeta::ObjectMetaDoc::descr)
        ...
        .def_property("obj_label",
                    STRING_CHAR_ARRAY(NvDsObjectMeta, obj_label));
}
```

Next, consider the **classifier_meta_list** and **obj_user_meta_list** data members, of types ```NvDsClassifierMetaList*``` and ```NvDsUserMetaList*```, respectively. By examining the ```nvdsmeta.h``` header file, we see that ```NvDsClassifierMetaList``` and ```NvDsUserMetaList``` are typedefs for ```GList```. [```src/pyds.cpp```](src/pyds.cpp) contains bindings code for the ```GList``` class:

```c++
py::class_<GList>(m, "GList")
    .def(py::init<>())
    .def_readwrite("data", &GList::data)
    .def_readwrite("next", &GList::next)
    .def_readwrite("prev", &GList::prev);
```
So, we may directly bind the two data members using the ```class_::def_readwrite()``` method:
```c++
void bindnvdsmeta(py::module &m) {
    py::class_<NvDsObjectMeta>(m, "NvDsObjectMeta",
                                pydsdoc::nvmeta::ObjectMetaDoc::descr)
        ...
        .def_readwrite("classifier_meta_list", 
                        &NvDsObjectMeta::classifier_meta_list)
        .def_readwrite("obj_user_meta_list",
                        &NvDsObjectMeta::obj_user_meta_list);
}
```
Note that while in C, **classifier_meta_list** and **obj_user_meta_list** are pointers to ```Glist``` objects, through the bindings, they are exposed to the Python API as the ```Glist``` objects themselves and can be treated as such when retrieved. Please see any of the sample applications provided in this repo for example usage, such as [deepstream-test1](../apps/deepstream-test1/).

##### Adding a member function
The C API binding for ```NvDsObjectMeta``` is now completed, but we require an additional member function for practical usage. In DeepStream applications, ```NvDsObjectMeta``` objects are retrieved from a ```GList``` from an ```NvDsFrameMeta``` object. We may access the ```data``` in the ```GList``` in the Python API due to our binding, but ```data``` is an object of type ```capsule``` in Python, which corresponds to ```void*``` in C. So, after we retrieve the ```data```, we must be able to cast it to an ```NvDsObjectMeta``` to use it. We enable this functionality by adding the following member function binding:
```c++
void bindnvdsmeta(py::module &m) {
    py::class_<NvDsObjectMeta>(m, "NvDsObjectMeta",
                            pydsdoc::nvmeta::ObjectMetaDoc::descr)
    ...

        .def("cast",
            [](void *data) { // Function definition
                return (NvDsObjectMeta *) data; // Cast void* to NvDsObjectMeta*
            },
            py::return_value_policy::reference, // Ownership of return object must remain with C++
            pydsdoc::nvmeta::ObjectMetaDoc::cast); // Docstring
}
```
Note again that though we return a pointer to an ```NvDsObjectMeta```, it will be exposed to the Python API as the ```NvDsObjectMeta``` object itself. For example usage, see this snippet from [deepstream-test1](https://github.com/NVIDIA-AI-IOT/deepstream_python_apps/blob/master/apps/deepstream-test1/deepstream_test_1.py#L76):
```python
...
batch_meta = pyds.gst_buffer_get_nvds_batch_meta(hash(gst_buffer))
    l_frame = batch_meta.frame_meta_list
    while l_frame is not None:
        try:
            # Note that l_frame.data needs a cast to pyds.NvDsFrameMeta
            # The casting is done by pyds.glist_get_nvds_frame_meta()
            # The casting also keeps ownership of the underlying memory
            # in the C code, so the Python garbage collector will leave
            # it alone.
            #frame_meta = pyds.glist_get_nvds_frame_meta(l_frame.data)
            frame_meta = pyds.NvDsFrameMeta.cast(l_frame.data)
        except StopIteration:
            break

        frame_number=frame_meta.frame_num
        num_rects = frame_meta.num_obj_meta
        l_obj=frame_meta.obj_meta_list
        while l_obj is not None:
            try:
                # Casting l_obj.data to pyds.NvDsObjectMeta
                #obj_meta=pyds.glist_get_nvds_object_meta(l_obj.data)
                obj_meta=pyds.NvDsObjectMeta.cast(l_obj.data)
            except StopIteration:
                break
            obj_counter[obj_meta.class_id] += 1
            obj_meta.rect_params.border_color.set(0.0, 0.0, 1.0, 0.0)
            try: 
                l_obj=l_obj.next
            except StopIteration:
                break
        ...
```
Note also the ```GList``` usage in the above snippet.

So, the final code for the binding of ```NvDsObjectMeta``` looks like this:
```c++
void bindnvdsmeta(py::module &m) {
    py::class_<NvDsObjectMeta>(m, "NvDsObjectMeta",
                            pydsdoc::nvmeta::ObjectMetaDoc::descr)
        .def(py::init<>()); // Constructor wrapper, empty for struct
        .def_readwrite("base_meta", &NvDsObjectMeta::base_meta);
        .def_readwrite("unique_component_id",
                        &NvDsObjectMeta::unique_component_id)
        .def_readwrite("class_id", &NvDsObjectMeta::class_id)
        .def_readwrite("object_id", &NvDsObjectMeta::object_id)
        .def_readwrite("detector_bbox_info",
                        &NvDsObjectMeta::detector_bbox_info)
        .def_readwrite("tracker_bbox_info",
                        &NvDsObjectMeta::tracker_bbox_info)
        .def_readwrite("confidence", &NvDsObjectMeta::confidence)
        .def_readwrite("tracker_confidence",
                        &NvDsObjectMeta::tracker_confidence)
        .def_readwrite("rect_params", &NvDsObjectMeta::rect_params)
        .def_readwrite("mask_params", &NvDsObjectMeta::mask_params)
        .def_readwrite("text_params", &NvDsObjectMeta::text_params)
        .def_property("obj_label",
                    STRING_CHAR_ARRAY(NvDsObjectMeta, obj_label));
        .def_readwrite("classifier_meta_list", 
                        &NvDsObjectMeta::classifier_meta_list)
        .def_readwrite("obj_user_meta_list",
                        &NvDsObjectMeta::obj_user_meta_list);
        .def("cast",
            [](void *data) {
                return (NvDsObjectMeta *) data;
            },
            py::return_value_policy::reference,
            pydsdoc::nvmeta::ObjectMetaDoc::cast);
}
```

#### Binding an enumerator
Enumerators can be simply bound by following the example in the pybind11 [documentation](https://pybind11.readthedocs.io/en/stable/classes.html#enumerations-and-internal-types). For example, to bind [```NvDsInferDataType```](https://docs.nvidia.com/metropolis/deepstream/sdk-api/group__ee__nvinf.html#ga6a35747b3bb45d13db9be3a2aa981e49) in [```src/bindnvdsinfer.cpp```](src/bindnvdsinfer.cpp):
```c++
py::enum_<NvDsInferDataType>(m, "NvDsInferDataType",
                            pydsdoc::NvInferDoc::NvDsInferDataTypeDoc::descr)
    .value("FLOAT", FLOAT,
            pydsdoc::NvInferDoc::NvDsInferDataTypeDoc::FLOAT)
    .value("HALF", HALF,
            pydsdoc::NvInferDoc::NvDsInferDataTypeDoc::HALF)
    .value("INT8", INT8,
            pydsdoc::NvInferDoc::NvDsInferDataTypeDoc::INT8)
    .value("INT32", INT32,
            pydsdoc::NvInferDoc::NvDsInferDataTypeDoc::INT32)
    .export_values();
```

#### Binding a function
There are three cases to consider for binding a function:
1. Binding an already existing function in the C API
2. Adding a new function to the PyDS module, not defined in the C API
3. Adding a member function to a data struct (demonstrated in [Adding a member function](#adding-a-member-function))

For the first two cases, the code should be added to the ```bindfunctions()``` function defined in [```src/bindfunctions.cpp```](src/bindfunctions.cpp). Member functions should be defined in the bindings for their class.

##### Binding an existing function
Consider the [```nvds_add_user_meta_to_obj```](https://docs.nvidia.com/metropolis/deepstream/sdk-api/group__metadata__structures.html#ga781f7f6da75486b480de3b11864b5cf5) function defined in the C API:
<pre>
<b>void nvds_add_user_meta_to_frame	(NvDsFrameMeta *frame_meta, NvDsUserMeta *user_meta )</b>		

Add a user meta user to a frame meta.

<b>Parameters</b>
[in]	frame_meta	A pointer to the frame meta to which <i>user_meta</i> is to be added.
[in]	user_meta	A pointer to the user meta to be added to <i>frame_meta</i>.
</pre>

This can be simply bound with the following code using the ```module_::def()``` function: 
```c++
void bindfunctions(py::module &m) {
    ...
    m.def("nvds_add_user_meta_to_frame", // Name of function in PyDS module
            &nvds_add_user_meta_to_frame, // Function in C API to be bound
            "frame_meta"_a,  // Expose "frame_meta" as keyword argument
            "user_meta"_a, // Expose "user_meta" as keyword argument
            pydsdoc::methodsDoc::nvds_add_user_meta_to_frame) // Docstring
    ...          
}
```

Note that since ```nvds_add_user_meta_to_obj``` is of return type ```void```, no return value policy needs to be set, as nothing 
is returned from the function. Keyword argument names are exposed to the module using the ```_a``` operator, which is shorthand for the ```py::arg```
special tag. See the [keyword arguments](https://pybind11.readthedocs.io/en/stable/basics.html#keyword-arguments) pybind11 documentation for more details.

##### Adding a new function
To add a new function to the module, we also call ```module_::def()```, but instead of referencing an existing function in the C API, we may define a lambda function in the call. The arguments are exposed in the same manner. For example, the ```get_segmentation_masks``` function:
```c++
void bindfunctions(py::module &m) {
    ...
    m.def("get_segmentation_masks",
            [](void *data) { // Start of lambda function definition
                auto *META = (NvDsInferSegmentationMeta *) data; // Cast void* to NvDsInferSegmentationMeta*
                int width = META->width; // Get width of mask array
                int height = META->height; // Get height of mask array
                auto dtype = py::dtype(py::format_descriptor<int>::format()); // int datatype
                return py::array(dtype, {height, width}, // datatype, shape of array
                                {sizeof(int) * width, sizeof(int)}, // strides (in bytes) in each dimension
                                META->class_map); // pointer to buffer
            },
            "data"_a, // Expose "data" as keyword argument
            pydsdoc::methodsDoc::get_segmentation_masks); // Docstring

    ...          
}
```
###### Note on arrays
This function also serves as a demonstration for exposing a C buffer to the Python API as a NumPy array. This is accomplished be writing a function which
returns a ```py::array``` type constructed from the ```datatype``` of the buffer, the shape of the buffer, the strides in bytes in each index, and the pointer to the buffer. Please see the [deepstream-segmentation](https://github.com/NVIDIA-AI-IOT/deepstream_python_apps/blob/master/apps/deepstream-segmentation/deepstream_segmentation.py#L110) app for example usage of the function and the returned array:
```python
# Retrieve mask data in the numpy format from segmeta
# Note that pyds.get_segmentation_masks() expects object of
# type NvDsInferSegmentationMeta
masks = pyds.get_segmentation_masks(segmeta)
masks = np.array(masks, copy=True, order='C') # Copy mask to another np.array
# map the obtained masks to colors of 2 classes.
frame_image = map_mask_as_display_bgr(masks)
cv2.imwrite(folder_name + "/" + str(frame_number) + ".jpg", frame_image) # Write array to image
```

#### Note on strings
There are some cases for which we may want to access the string in Python as the C address of the character array, from which we may perform memory operations. For example, in [deepstream-test4](../apps/deepstream-test4), we define a function for deep-copying an ```NvDsEventMsgMeta``` struct. In
such a case, to deep copy a string field such as the ```sensorStr``` data member, we must allocate new memory for a character array and copy in the string contents. The following macro for getter and setter functions is defined in [```include/bind/bind_string_property_definitions.h```](include/bind/bind_string_property_definitions.h):
```c++
#define STRING_PROPERTY(TYPE, FIELD)                               \
        [](const TYPE &self)->size_t {                             \
            return (size_t)self.FIELD;                             \ // Return C address of string field
        },                                                         \
        [](TYPE &self, std::string str) {                          \
            int strSize = str.size();                              \
            self.FIELD = (char*)calloc(strSize + 1, sizeof(char)); \ // Alloc memory for C string
            str.copy(self.FIELD, strSize);                         \ // Copy contents into array
        },                                                         \
        py::return_value_policy::reference // 
```
We define also the ```get_string``` method in ```bindings/src/bindfunctions.cpp```:
```c++
m.def("get_string",
        [](size_t ptr) {
            return (char *) ptr; // Return reference to string from address
        },
        "ptr"_a,
        py::return_value_policy::reference, // Owned by C side
        pydsdoc::methodsDoc::get_string);
```
So, we bind the ```sensorStr``` data member as follows:
```
py::class_<NvDsEventMsgMeta>(m, "NvDsEventMsgMeta",
                                pydsdoc::metaschema::EventmsgDoc::descr)
    ...
    .def_property("sensorStr",
                    STRING_PROPERTY(NvDsEventMsgMeta, sensorStr))
    ...
```
Then, in the [deep copy function](https://github.com/NVIDIA-AI-IOT/deepstream_python_apps/blob/master/apps/deepstream-test4/deepstream_test_4.py#L83)
where ```dstmeta``` is the newly allocated ```NvDsEventMsgMeta``` object, and ```srcmeta``` is the ```NvDsEventMsgMeta``` object to be copied:
```
dstmeta.sensorStr = pyds.get_string(srcmeta.sensorStr)
```
```srcmeta.sensorStr``` calls the getter function defined in the string property, which returns the C address of the string, which is then passed into the ```get_string``` method. The assignment operator passes the resulting string reference into the setter function for ```dstmeta.sensorStr```, which allocates memory for the C string and copies in the content of the string.

### How to write docstrings
Docstrings should be declared and defined as a ```constexpr const char*``` in a header file under [```docstrings/```](docstrings/) corresponding to the header to which the binding belongs. All docstrings belong under the ```pydsdoc::{header_name}doc``` namespace. The final documentation is generated with [Sphinx](https://www.sphinx-doc.org/en/master/index.html), so docstrings must follow .rst format and use Sphinx [directives](https://www.sphinx-doc.org/en/master/usage/restructuredtext/directives.html).

#### Docstring for a struct
Using ```NvDsObjectMeta``` as an example again, we would create the file [```docstrings/nvdsmetadoc.h```](docstrings/nvdsmetadoc.h). Under the namespace ```pydsdoc```, we create the namespace ```nvdsmetadoc``` following the convention ```{header name}doc```. Under the ```nvdsmetadoc``` namespace, we then create a namespace for each struct following the ```{struct name}Doc``` convention: ```NvDsObjectMetaDoc```. Note: the current docstrings do not all follow this convention, but will be fixed for consistency in the future. For structs, we define one string ```descr``` to describe the struct and all of its datamembers, along with any example usage. For each data member, follow the ```:ivar {data member name}: *data type*, [description]``` format. Put example usage in a code block using the ```::``` directive:
```c++
#pragma once // Ensure header file is included only once

namespace pydsdoc
{
    namespace nvdsmetadoc
    {
        namespace NvDsObjectMetaDoc
        {
            constexpr const char* descr = R"pyds(
                Holds information of object metadata in the frame.

                :ivar base_meta: :class:`NvDsBaseMeta`, base_meta
                :ivar parent: the parent :class:`NvDsObjectMeta` object. Set to None if parent is not present
                :ivar unique_component_id: *int*, unique component id that attaches NvDsObjectMeta metadata
                :ivar class_id: *int*, Index of the object class infered by the primary detector/classifier
                :ivar object_id: *int*, Unique ID for tracking the object. @ref UNTRACKED_OBJECT_ID indicates the object has not been tracked
                :ivar confidence: *float*, Holds a confidence value for the object, set by the inference component. 
                    Confidence will be set to -0.1, if "Group Rectangles" mode of clustering is chosen since the algorithm does not preserve confidence values.
                    Also, for objects found by tracker and not inference component, confidence will be set to -0.1
                :ivar detector_bbox_info: :class:`NvDsComp_BboxInfo`, Holds a structure containing bounding box parameters of the object when detected by detector
                :ivar tracker_bbox_info: :class:`NvDsComp_BboxInfo`, Holds a structure containing bounding box coordinates of the object when processed by tracker
                :ivar tracker_confidence: *float*, Holds a confidence value for the object set by nvdcf_tracker. tracker_confidence will be set to -0.1 for KLT and IOU tracker
                :ivar rect_params: :class:`NvOSD_RectParams`, Structure containing the positional parameters of the object in the frame.
                    e.g. If the tracker component is after the detector component in the pipeline, then positional parameters are from tracker component.
                    Can also be used to overlay borders / semi-transparent boxes on top of objects. See :class:`NvOSD_RectParams`
                :ivar mask_params: :class:`NvOSD_MaskParams`, Holds mask parameters for the object. This mask is overlaid on object See :class:`NvOSD_MaskParams`
                :ivar text_params: :class:`NvOSD_TextParams`, Text describing the object can be overlayed using this structure. See :class:`NvOSD_TextParams`
                :ivar obj_label: An array to store the string describing the class of the detected object
                :ivar classifier_meta_list: list of objects of type :class:`NvDsClassifierMeta`
                :ivar obj_user_meta_list: list of objects of type :class:`NvDsUserMeta`
                :ivar misc_obj_info: *list of int*, For additional user specific batch info
                :ivar reserved: *int*, Reserved for internal use.

                Example usage:
                ::

                    #Initialize dict to keep count of objects of each type
                    obj_counter = {
                            PGIE_CLASS_ID_VEHICLE:0,
                            PGIE_CLASS_ID_PERSON:0,
                            PGIE_CLASS_ID_BICYCLE:0,
                            PGIE_CLASS_ID_ROADSIGN:0
                        }

                    l_obj=frame_meta.obj_meta_list #Retrieve list of NvDsObjectMeta objects in frame from an NvDsFrameMeta object. See NvDsFrameMeta documentation for more details.
                    while l_obj is not None:
                        try:
                            # Casting l_obj.data to pyds.NvDsObjectMeta
                            obj_meta=pyds.NvDsObjectMeta.cast(l_obj.data)
                            except StopIteration:
                                break
                            obj_counter[obj_meta.class_id] += 1 #Retrieve class_id from NvDsObjectMeta (i.e. PGIE_CLASS_ID_VEHICLE, PGIE_CLASS_ID_PERSON, etc.) to update count
                            obj_meta.rect_params.border_color.set(0.0, 0.0, 1.0, 0.0) #Set border color of NvDsObjectMeta object's rect_params
                            try: 
                                l_obj=l_obj.next
                            except StopIteration:
                                break)pyds";
        }
    }
}
```
Note that the tag ```:class:`{class name}` ``` will generate a link in the documentation to that class. See the Python API documentation for [```NvDsObjectMeta```](https://docs.nvidia.com/metropolis/deepstream/python-api/PYTHON_API/NvDsMeta/NvDsObjectMeta.html) to see the resulting doc. 

We also declare a docstring ```{function name}``` for every member function, under the same namespace:
```c++
#pragma once // Ensure header file is included only once

namespace pydsdoc
{
    namespace nvdsmetadoc
    {
        namespace NvDsObjectMetaDoc
        {
            ...

            constexpr const char* cast=R"pyds(cast given object/data to :class:`NvDsObjectMeta`, call pyds.NvDsObjectMeta.cast(data))pyds";
        }
    }
}
```

Any new bindings source file created must be added to [```../docs/bindings_file_list.txt```](../docs/bindings_file_list.txt). After running [```../docs/parse_bindings.py```](../docs/parse_bindings.py) on the updated list, check [```../docs/PYTHON_API```](../docs/PYTHON_API) to find the new toctree rst file. Add the file name to [```../docs/index.rst```](../docs/index.rst). In our case, we added ```bindnvdsmeta.cpp``` to the file list, which generated the file [```../docs/PYTHON_API/NvDsMeta/NvDsMeta_toc.rst```](../docs/PYTHON_API/NvDsMeta/NvDsMeta_toc.rst). So, in ```index.rst```:
```
...
.. toctree::
    :maxdepth: 7
    :caption: DeepStream Python API Reference
    :name: DeepStream Python API Reference

    PYTHON_API/NvDsMeta/NvDsMeta_toc
...

```
#### Docstring for an enumerator
Consider the ```NvDsInferDataType``` enumerator, declared under ```<DeepStream Root>/include/nvdsinfer.h```. Similarly to the last example, we create the file [```docstrings/nvdsinferdoc.h```](docstrings/nvdsinferdoc.h). Under the namespace ```pydsdoc::nvdsinferdoc::NvDsInferDataTypeDoc```, we write a docstring ```descr``` for the description of the enumerator, and a string ```{value name}``` for the description for each value of the enum:
```c++
#pragma once

namespace pydsdoc
{    
    namespace nvdsinferdoc
    {
        namespace  NvDsInferDataTypeDoc
        {
            constexpr const char* descr = R"pyds(*Enumerator*, Specifies the data type of a layer.)pyds";
            constexpr const char* FLOAT =R"pyds(FP32 format.)pyds";
            constexpr const char* HALF=R"pyds(FP16 format.)pyds";
            constexpr const char* INT8 =R"pyds(INT8 format.)pyds";
            constexpr const char* INT32 =R"pyds(INT32 format.)pyds";
        }
    }
}
```

#### Docstring for a function
Docstrings for functions should be written in the [```docstrings/functionsdoc.h```](docstrings/functionsdoc.h) header file, under the ```pydsdoc::functionsdoc``` namespace (again, note that the current status of the docstrings does not reflect the desired convention). A separate docstring for each function should be written in the following format:
```c++
constexpr const char* {function name}=R"pyds(
    {function description}

    :arg {argument 1 name}: {argument 1 description}
    ...
    :arg {argument n name}: {argument n description}
    
    :returns: {return value description})pyds";
```
For example, for the ```get_segmentation_masks``` function discussed earlier:
```c++
#pragma once

namespace pydsdoc
{
    namespace functionsDoc
	{
        constexpr const char* get_segmentation_masks=R"pyds(
            This function returns the inferred masks in Numpy format in the height X width shape, these height and width are obtained from the :class:`NvDsInferSegmentationMeta`.

            :arg data: An object of type :class:`NvDsInferSegmentationMeta`
            
            :returns: A NumPy array of shape (height, width) containing the inferred masks)pyds";
    }
}

```

Additionally, the function must be added to [```../docs/PYTHON_API/Methods/methodsdoc.rst```](../docs/PYTHON_API/Methods/methodsdoc.rst):
```
...
======================
get_segmentation_masks
======================

.. autofunction:: pyds.get_segmentation_masks
...
```



### How to send a custom event from Python to downstream elements?

It can be tricky to type cast some Gst-Python data types in Python.

This was recently discovered during an implementation of a binding that needed to send a custom event from Python.

We will use ```gst_nvevent_new_stream_reset(source_id)``` event as an example of this. This api creates a custom reset event for the specified source.

We can find it defined in ```<DS_ROOT>/sources/includes/gst-nvevent.h```.

The issue at hand is that this api returns a ```GstEvent *``` pointer, which cannot be type cast to any existing data type in GstPython.

To circumvent this limitation, we alternatively implement a binding in PyDS which takes a GstElement, for which the custom reset event needs to be generated, and call the api above directly from the bindings as follows:

```c++
m.def("gst_element_send_nvevent_new_stream_reset",
        [](size_t gst_element, int source_id) {
            auto *element = reinterpret_cast<GstElement *>(gst_element);
            return gst_element_send_event(element, gst_nvevent_new_stream_reset(source_id));
        },
        pydsdoc::methodsDoc::gst_element_send_nvevent_new_stream_reset);

```

So now, we can return the status of whether the event was handled properly, which is provided by ```gst_element_send_event()``` back to Python app as a boolean.