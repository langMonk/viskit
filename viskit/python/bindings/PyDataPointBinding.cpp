//
// \author Dawid Dębowski <ddebowsk@student.agh.edu.pl>
// \date 21.05.2022.
//

#include <pybind11/operators.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include "viskit/python/bindings/PyDataPointBinding.h"

namespace py = pybind11;
using namespace py::literals;

namespace viskit {
size_t DataPoint::m_currentId;
}

namespace viskit::python::bindings {
void PyDataPointBinding::bind(pybind11::module& m)
{
    py::class_<viskit::DataPoint>(m, "DataPoint")
        .def(py::init<size_t>())
        .def(py::init<std::vector<float>>())
        .def(py::init<std::vector<float>, int>())
        .def("size", &viskit::DataPoint::size)
        .def("getId", static_cast<size_t (DataPoint::*)()>(&viskit::DataPoint::getId))
        .def_property_readonly_static("m_currentId", []() { return DataPoint::m_currentId; });
}
}