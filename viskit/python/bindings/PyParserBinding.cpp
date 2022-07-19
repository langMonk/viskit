//
// \author Radosław Szuma <szuma@student.agh.edu.pl>
// \date 17.05.2022
//

#include <pybind11/pybind11.h>

#include "viskit/core/Core.h"
#include "viskit/facade/FacadeParserCSV.h"
#include "viskit/python/bindings/PyParserBinding.h"
#include "viskit/viskit/IParser.h"
#include "viskit/viskit/IParticleSystem.h"

namespace py = pybind11;
using namespace py::literals;

namespace viskit::python::bindings {

/* Trampoline (need one for each virtual function) */
void PyParserBinding::loadFile(std::string datasetFilePath, std::string labelsFilePath, viskit::IParticleSystem& ps)
{
    PYBIND11_OVERRIDE_PURE(
        void, /* Return type */
        viskit::IParser, /* Parent class */
        loadFile, /* Name of function in C++ (must match Python name) */
        datasetFilePath, labelsFilePath, ps /* Argument(s) */
    );
}

void PyParserBinding::bind(pybind11::module& m)
{
    py::class_<viskit::IParser, std::shared_ptr<viskit::IParser>, python::bindings::PyParserBinding>(m, "IParser")
        .def(py::init<>())
        .def("loadFile", &viskit::IParser::loadFile);

    py::class_<viskit::facade::FacadeParserCSV, std::shared_ptr<viskit::facade::FacadeParserCSV>, viskit::IParser>(m, "FacadeParserCSV")
        .def(py::init<const std::shared_ptr<core::Core>&>())
        .def("loadFile", &viskit::facade::FacadeParserCSV::loadFile);
}

}