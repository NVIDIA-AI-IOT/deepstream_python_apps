#include "pyds.hpp" // Include this "base" header file for all other dependencies
#include "../docstrings/nvdspreprocessmetadoc.h" // include the header file for the docstrings of this submodule

namespace py = pybind11;

namespace pydeepstream {
    void bindnvdspreprocess_meta(py::module &m); // Declare the bindings function for this submodule
}
