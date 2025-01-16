// GstNvDsPreProcessBatchMeta

#include "bind_string_property_definitions.h"
#include "bindnvdspreprocess_meta.hpp"
#include "nvdspreprocess_meta.h"
#include "nvds_roi_meta.h"

namespace py = pybind11;

namespace pydeepstream {

    void bindnvdspreprocess_meta(py::module &m) {
        // Bind the NvDsPreProcessTensorMeta structure
        py::class_<NvDsPreProcessTensorMeta>(m, "NvDsPreProcessTensorMeta",
                                            pydsdoc::nvdspreprocessmetadoc::NvDsPreProcessTensorMetaDoc::descr)
            .def(py::init<>()) // Constructor
            .def_readwrite("raw_tensor_buffer", &NvDsPreProcessTensorMeta::raw_tensor_buffer)
            .def_readwrite("buffer_size", &NvDsPreProcessTensorMeta::buffer_size)
            .def_readwrite("tensor_shape", &NvDsPreProcessTensorMeta::tensor_shape)
            .def_readwrite("data_type", &NvDsPreProcessTensorMeta::data_type)
            .def_readwrite("tensor_name", &NvDsPreProcessTensorMeta::tensor_name)
            .def_readwrite("gpu_id", &NvDsPreProcessTensorMeta::gpu_id)
            .def_readwrite("private_data", &NvDsPreProcessTensorMeta::private_data)
            .def_readwrite("meta_id", &NvDsPreProcessTensorMeta::meta_id)
            .def_readwrite("maintain_aspect_ratio", &NvDsPreProcessTensorMeta::maintain_aspect_ratio)
            .def("cast",
                [](void *data) {
                    return (NvDsPreProcessTensorMeta *) data;
                },
                py::return_value_policy::reference,
                pydsdoc::nvdspreprocessmetadoc::NvDsPreProcessTensorMetaDoc::cast);

        // Bind the GstNvDsPreProcessBatchMeta structure
        py::class_<GstNvDsPreProcessBatchMeta>(m, "GstNvDsPreProcessBatchMeta",
                                              pydsdoc::nvdspreprocessmetadoc::GstNvDsPreProcessBatchMetaDoc::descr)
            .def(py::init<>()) // Constructor
            .def_readwrite("target_unique_ids", &GstNvDsPreProcessBatchMeta::target_unique_ids)
            .def_readwrite("tensor_meta", &GstNvDsPreProcessBatchMeta::tensor_meta)
            .def_readwrite("roi_vector", &GstNvDsPreProcessBatchMeta::roi_vector)
            .def_readwrite("private_data", &GstNvDsPreProcessBatchMeta::private_data)
            .def("cast",
                [](void *data) {
                    return (GstNvDsPreProcessBatchMeta *) data;
                },
                py::return_value_policy::reference,
                pydsdoc::nvdspreprocessmetadoc::GstNvDsPreProcessBatchMetaDoc::cast);
    }

}