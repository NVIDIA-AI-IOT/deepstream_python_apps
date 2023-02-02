## Custom NvDsUserMeta Bindings Guide

This guide is useful for advanced use-cases of extending DeepStream's existing python bindings.
Users are expected to get themselves familiar with the basics of DeepStream Python bindings by going through the [BINDINGSGUIDE](BINDINGSGUIDE.md)

This guide mainly focuses on how users can create their own custom data structures in C/C++, add bindings for them and then access the data in the custom data structures at downstream Gst Elements in the pipeline by attaching the data structure as user_meta_data of NvDsUserMeta object. 

- [Custom NvDsUserMeta Bindings Guide](#custom-nvdsusermeta-bindings-guide)
- [How to write custom bindings for custom data structures](#how-to-write-custom-bindings-for-custom-data-structures)
  - [Creating header file for custom structure](#creating-header-file-for-custom-structure)
  - [Creating header file for custom bindings](#creating-header-file-for-custom-bindings)
  - [Creating custom bindings](#creating-custom-bindings)
  - [Adding docstrings for new custom bindings](#adding-docstrings-for-new-custom-bindings)
  - [Adding custom bindings to PyDS compilation](#adding-custom-bindings-to-pyds-compilation)
  - [Testing custom bindings with sample app](#testing-custom-bindings-with-sample-app)

## How to write custom bindings for custom data structures
Now let's look at an example of writing a custom binding for a custom data structure that is not a part of C API header files.

Such custom data structures can be attached to the buffers using NvDsUserMeta and can then be accessed by downstream pipeline elements.

### Creating header file for custom structure
First, we create/add a header file for the structure we want to attach as NvDsUserMetaData.
For this example, we have created a sample header file [custom_data.hpp](src/custom_binding/include/custom_data.hpp) which has the following contents:

```c++
#include <string>

using namespace std;

// Custom Data Structure that we want to attach to buffer metadata
struct CustomDataStruct { 
  int structId; // int ID to as an example of ID field
  char* message; // string message 
  int sampleInt; // int sample data
};
```

### Creating header file for custom bindings
Now we add a corresponding bindings header file. Following the ```bind{header_name}.hpp``` convention, for this example, we create the file [bindcustom.hpp](src/custom_binding/include/bindcustom.hpp) with the following contents:

```c++
#include "pyds.hpp"
#include "custom_data.hpp" // Include the actual C++ header file for CustomDataStruct
// We add bindcustom.cpp related docstring in customdoc.h
// And any functions related to our custom bindings would go in
// functionsdoc.h docstring file
#include "../../../docstrings/customdoc.h"
#include "../../../docstrings/functionsdoc.h"

namespace py = pybind11;

namespace pydeepstream {
    void bindcustom(py::module &m); // Declare the bindings function for this submodule
}
```

### Creating custom bindings
Now we write our [bindcustom.cpp](src/custom_binding/bindcustom.cpp) where we define bindings for CustomDataStruct structure along with related member function to allocate the memory for structure.
The function that will be exposed to Python is:

```
pyds.alloc_custom_struct()
```

It is worth noting that NvDsUserMeta allows users to set function pointers for copy function and release function to copy the data from the custom structure to another custom structure and to release the allocated structure respectively.

Contents of [bindcustom.cpp](src/custom_binding/bindcustom.cpp) are:

```c++
#include "bind_string_property_definitions.h"
#include "include/bindcustom.hpp"

namespace py = pybind11;

namespace pydeepstream {

    // callback function to copy custom struct to another destination custom struct
    void * copy_custom_struct(void* data, void* user_data) {
        NvDsUserMeta * srcMeta = (NvDsUserMeta*) data;
        CustomDataStruct * srcData = (CustomDataStruct *) srcMeta->user_meta_data;
        CustomDataStruct *destData = (CustomDataStruct *) g_malloc0(
                        sizeof(CustomDataStruct));
        destData->structId = srcData->structId;
        destData->sampleInt = srcData->sampleInt;
        if (srcData->message != nullptr) {
            char* srcString = (char *) srcData->message;
            int strSize = strlen(srcString);
            destData->message = (char*)calloc(strSize + 1, sizeof(char));
            strcpy(destData->message, srcData->message);
        }
        return destData;
    }

    // callback function to release allocated memory
    void release_custom_struct(void * data, void * user_data) {
        NvDsUserMeta * srcMeta = (NvDsUserMeta*) data;
        
        if (srcMeta != nullptr) {
            CustomDataStruct * srcData = (CustomDataStruct *) srcMeta->user_meta_data;
            if (srcData != nullptr) {
                auto * message = srcData->message;
                srcData->structId = 0;
                srcData->sampleInt = 0;
                if (srcData->message != nullptr)
                {
                    free(srcData->message);
                }
                g_free(srcData);
            }
        }
    }

    void bindcustom(py::module &m) {
                /* CustomDataStruct bindings to be used with NvDsUserMeta */
                py::class_<CustomDataStruct>(m, "CustomDataStruct",
                                pydsdoc::custom::CustomDataStructDoc::descr)
                .def(py::init<>())
                // binding structId int with CustomDataStruct int
                .def_readwrite("structId", &CustomDataStruct::structId)
                // String property which provides binding for CustomDataStruct string 
                // and frees the existing string if new value is copied
                .def_property("message", STRING_FREE_EXISTING(CustomDataStruct, message))
                // binding sampleInt int with CustomDataStruct int
                .def_readwrite("sampleInt", &CustomDataStruct::sampleInt)

                // binding function to cast user_meta_data to CustomDataStruct
                .def("cast",
                     [](void *data) {
                         return (CustomDataStruct *) data;
                     },
                     py::return_value_policy::reference,
                     pydsdoc::custom::CustomDataStructDoc::cast);

        // binding function used to allocate memory for struct in C
        // Memory ownership is maintained by bindings and only reference is passed to Python
        m.def("alloc_custom_struct",
              [](NvDsUserMeta *meta) {
                  auto *mem = (CustomDataStruct *) g_malloc0(
                          sizeof(CustomDataStruct));
                  meta->base_meta.copy_func = (NvDsMetaCopyFunc) pydeepstream::copy_custom_struct;
                  meta->base_meta.release_func = (NvDsMetaReleaseFunc) pydeepstream::release_custom_struct;
                  return mem;
              },
              py::return_value_policy::reference,
              pydsdoc::methodsDoc::alloc_custom_struct);
    }
}
```
### Adding docstrings for new custom bindings

We now need to make sure that the correct docstrings are added for the bindings we have just created.
These can be divided into two files: 

1. [customdoc.h](docstrings/customdoc.h) for actual bindings' docstrings, which can be seen below

```c++
#pragma once

namespace pydsdoc
{
    namespace custom
    {
        namespace CustomDataStructDoc
        {
            constexpr const char* descr = R"pyds(
                Holds custom struct data.

                :ivar structId: *int*, ID for this struct.
                :ivar message: *str*, Message embedded in this structure.
                :ivar sampleInt: *int*, Sample int data)pyds";

            constexpr const char* cast=R"pyds(cast given object/data to :class:`CustomDataStruct`, call pyds.CustomDataStruct.cast(data))pyds";
        }
    }
}
```

2. [functionsdoc.h](docstrings/functionsdoc.h) for any functions related to the bindings, which can be seen below:

```c++
...
...
    constexpr const char* alloc_custom_struct=R"pyds( 
        Allocate an :class:`CustomDataStruct`. 

        :returns: Allocated :class:`CustomDataStruct`)pyds";
...
...
```

We add relevant docstrings to both of these before proceeding ahead. These docstrings are referred to in the bindings code using namespace ```pydsdoc```.

### Adding custom bindings to PyDS compilation

We need to make sure that the new [bindcustom.cpp](src/custom_binding/bindcustom.cpp) file is added to [CMakeLists.txt](CMakeLists.txt) as follows:

```
add_library(pyds SHARED src/pyds.cpp src/utils.cpp src/bindanalyticsmeta.cpp
            src/bindfunctions.cpp src/bindgstnvdsmeta.cpp
            src/bindmeta360.cpp src/bindnvbufsurface.cpp src/bindnvdsinfer.cpp
            src/bindnvdsmeta.cpp src/bindnvosd.cpp src/bindopticalflow.cpp
            src/bindschema.cpp src/bindtrackermeta.cpp src/custom_binding/bindcustom.cpp)
```

Also, we need to add the newly created ```bindcustom(m)``` submodule to [pyds.cpp](src/pyds.cpp) as follows:

```c++
...
#include "bindschema.hpp"
#include "bindtrackermeta.hpp"
#include "custom_binding/include/bindcustom.hpp"
...
...
        bindnvdsinfer(m);
        bindopticalflowmeta(m);
        bindcustom(m);

    }   // end PYBIND11_MODULE(pyds, m)
}
```


### Testing custom bindings with sample app

Now that we have created our own CustomDataStruct and bindings for it to allocate, copy and release, we are ready to use these and create our sample app to test these out.

For this example, we have created a sample app called [deepstream-custom-binding-test](../apps/deepstream-custom-binding-test/deepstream_custom_binding_test.py), which utilizes two probe functions to achieve this use-case.

The pipeline for this app looks as follows:
```
FileSrc -> H264Parse -> NvV4l2Decoder -> NvStreammux -> Queue -> Queue -> FakeSink
                                                    |                     |
                                                    |                     |
                                                    -probe                -probe
```
This first probe is added at the srcpad of NvStreamMux. This probe function acquires NvDsUserMeta buffer from pool and attaches this CustomDataStruct structure to it as metadata.

A code snippet from the [deepstream-custom-binding-test.py](../apps/deepstream-custom-binding-test/deepstream_custom_binding_test.py) app showing this is attached below:

```python
...
    try:
        frame_meta = pyds.NvDsFrameMeta.cast(l_frame.data)
        frame_number = frame_meta.frame_num
    except StopIteration:
        continue

    user_meta = pyds.nvds_acquire_user_meta_from_pool(batch_meta)

    if user_meta:
        print('adding user meta')
        test_string = 'test message ' + str(frame_number)
        data = pyds.alloc_custom_struct(user_meta)
        data.message = test_string
        data.message = pyds.get_string(data.message)
        data.structId = frame_number
        data.sampleInt = frame_number + 1

        user_meta.user_meta_data = data
        user_meta.base_meta.meta_type = pyds.NvDsMetaType.NVDS_USER_META

        pyds.nvds_add_user_meta_to_frame(frame_meta, user_meta)
    else:
        print('failed to acquire user meta')
...    
```

Second probe function is added at the sinkpad of FakeSink and it reads the values attached as part of this custom structure after the buffer reaches sinkpad of FakeSink. The allocated memory is then freed using pyds.release_custom_struct()

A code snippet from the [deepstream-custom-binding-test.py](../apps/deepstream-custom-binding-test/deepstream_custom_binding_test.py) app showing this is attached below:

```python
...
    try:
        frame_meta = pyds.NvDsFrameMeta.cast(l_frame.data)
    except StopIteration:
        continue

    l_usr = frame_meta.frame_user_meta_list
    while l_usr is not None:
        try:
            user_meta = pyds.NvDsUserMeta.cast(l_usr.data)
        except StopIteration:
            continue

        if user_meta.base_meta.meta_type == pyds.NvDsMetaType.NVDS_USER_META:
            custom_msg_meta = pyds.CustomDataStruct.cast(user_meta.user_meta_data)
            Gst.info(f'event msg meta, otherAttrs = {pyds.get_string(custom_msg_meta.message)}')
            print('custom meta structId:: ', custom_msg_meta.structId)
            print('custom meta msg:: ', pyds.get_string(custom_msg_meta.message))
            print('custom meta sampleInt:: ', custom_msg_meta.sampleInt)
        try:
            l_usr = l_usr.next
        except StopIteration:
            break
...
```

For more details on the implementation, please refer the sample app [deepstream-custom-binding-test.py](../apps/deepstream-custom-binding-test/deepstream_custom_binding_test.py)