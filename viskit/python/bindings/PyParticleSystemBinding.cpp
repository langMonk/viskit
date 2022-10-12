//
// \author Dawid Dębowski <ddebowsk@student.agh.edu.pl>
// \date 21.05.2022.
//

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include "viskit/core/Core.h"
#include "viskit/python/bindings/PyParticleSystemBinding.h"

namespace py = pybind11;
using namespace py::literals;

namespace viskit::python::bindings {
DatasetInfo PyParticleSystemBinding::datasetInfo()
{
    PYBIND11_OVERRIDE_PURE(
        DatasetInfo, /* Return type */
        viskit::IParticleSystem, /* Parent class */
        datasetInfo, /* Name of function in C++ (must match Python name) */
        /* Argument(s) */
    );
}

typedef std::vector<std::pair<DataPoint, size_t>> vector_of_datapoint_and_size_t;

std::vector<std::pair<DataPoint, size_t>> PyParticleSystemBinding::originalCoordinates()
{
    PYBIND11_OVERRIDE_PURE(
        vector_of_datapoint_and_size_t, /* Return type */
        viskit::IParticleSystem, /* Parent class */
        originalCoordinates, /* Name of function in C++ (must match Python name) */
        /* Argument(s) */
    );
}

std::vector<size_t> PyParticleSystemBinding::labels()
{
    PYBIND11_OVERRIDE_PURE(
        std::vector<size_t>, /* Return type */
        viskit::IParticleSystem, /* Parent class */
        labels, /* Name of function in C++ (must match Python name) */
        /* Argument(s) */
    );
}

std::vector<viskit::vec4> PyParticleSystemBinding::forces()
{
    PYBIND11_OVERRIDE_PURE(
        std::vector<viskit::vec4>, /* Return type */
        viskit::IParticleSystem, /* Parent class */
        forces, /* Name of function in C++ (must match Python name) */
        /* Argument(s) */
    );
}

std::vector<viskit::vec4> PyParticleSystemBinding::positions()
{
    PYBIND11_OVERRIDE_PURE(
        std::vector<viskit::vec4>, /* Return type */
        viskit::IParticleSystem, /* Parent class */
        positions, /* Name of function in C++ (must match Python name) */
        /* Argument(s) */
    );
}

std::vector<viskit::vec4> PyParticleSystemBinding::velocities()
{
    PYBIND11_OVERRIDE_PURE(
        std::vector<viskit::vec4>, /* Return type */
        viskit::IParticleSystem, /* Parent class */
        velocities, /* Name of function in C++ (must match Python name) */
        /* Argument(s) */
    );
}

std::vector<viskit::vec4> PyParticleSystemBinding::colors()
{
    PYBIND11_OVERRIDE_PURE(
        std::vector<viskit::vec4>, /* Return type */
        viskit::IParticleSystem, /* Parent class */
        colors, /* Name of function in C++ (must match Python name) */
        /* Argument(s) */
    );
}

void PyParticleSystemBinding::setPosition(size_t index, float x, float y)
{
    PYBIND11_OVERRIDE_PURE(
        void, /* Return type */
        viskit::IParticleSystem, /* Parent class */
        setPosition, /* Name of function in C++ (must match Python name) */
        index, x, y /* Argument(s) */
    );
}

size_t PyParticleSystemBinding::countAlive()
{
    PYBIND11_OVERRIDE_PURE(
        size_t, /* Return type */
        viskit::IParticleSystem, /* Parent class */
        countAlive, /* Name of function in C++ (must match Python name) */
        /* Argument(s) */
    );
}

size_t PyParticleSystemBinding::countParticles()
{
    PYBIND11_OVERRIDE_PURE(
        size_t, /* Return type */
        viskit::IParticleSystem, /* Parent class */
        countParticles, /* Name of function in C++ (must match Python name) */
        /* Argument(s) */
    );
}

void PyParticleSystemBinding::clear()
{
    PYBIND11_OVERRIDE_PURE(
        void, /* Return type */
        viskit::IParticleSystem, /* Parent class */
        clear, /* Name of function in C++ (must match Python name) */
        /* Argument(s) */
    );
}

bool PyParticleSystemBinding::empty()
{
    PYBIND11_OVERRIDE_PURE(
        bool, /* Return type */
        viskit::IParticleSystem, /* Parent class */
        empty, /* Name of function in C++ (must match Python name) */
        /* Argument(s) */
    );
}

bool PyParticleSystemBinding::saveToFile(const std::string& fileName)
{
    PYBIND11_OVERRIDE_PURE(
        bool, /* Return type */
        viskit::IParticleSystem, /* Parent class */
        saveToFile, /* Name of function in C++ (must match Python name) */
        fileName /* Argument(s) */
    );
}

bool PyParticleSystemBinding::saveToFile(const std::string& fileName, IGraph& graph)
{
    PYBIND11_OVERRIDE_PURE(
        bool, /* Return type */
        viskit::IParticleSystem, /* Parent class */
        saveToFileWithGraph, /* Name of function in C++ (must match Python name) */
        fileName, graph /* Argument(s) */
    );
}

void PyParticleSystemBinding::bind(pybind11::module& m)
{

    py::class_<viskit::IParticleSystem, std::shared_ptr<viskit::IParticleSystem>, PyParticleSystemBinding>(m, "IParticleSystem")
        .def(py::init<>())
        .def("dataset", &viskit::IParticleSystem::datasetInfo)
        .def("originalCoordinates", &viskit::IParticleSystem::originalCoordinates)
        .def("labels", &viskit::IParticleSystem::labels)
        .def("positions", &viskit::IParticleSystem::positions)
        .def("forces", &viskit::IParticleSystem::forces)
        .def("velocities", &viskit::IParticleSystem::velocities)
        .def("colors", &viskit::IParticleSystem::colors)
        .def("setPosition", &viskit::IParticleSystem::setPosition)
        .def("countAlive", &viskit::IParticleSystem::countAlive)
        .def("countParticles", &viskit::IParticleSystem::countParticles)
        .def("clear", &viskit::IParticleSystem::clear)
        .def("empty", &viskit::IParticleSystem::empty)
        .def("saveToFile", static_cast<bool (viskit::IParticleSystem::*)(const std::string&)>(&viskit::IParticleSystem::saveToFile))
        .def("saveToFile", static_cast<bool (viskit::IParticleSystem::*)(const std::string&, IGraph&)>(&viskit::IParticleSystem::saveToFile))
        .def("loadParticlesPositions", &viskit::IParticleSystem::loadParticlesPositions);

    py::class_<viskit::facade::FacadeParticleSystem, std::shared_ptr<viskit::facade::FacadeParticleSystem>, viskit::IParticleSystem>(m, "FacadeParticleSystem")
        .def(py::init<const std::shared_ptr<core::Core>&>())
        .def("dataset", &viskit::facade::FacadeParticleSystem::datasetInfo)
        .def("originalCoordinates", &viskit::facade::FacadeParticleSystem::originalCoordinates)
        .def("labels", &viskit::facade::FacadeParticleSystem::labels)
        .def("positions", &viskit::facade::FacadeParticleSystem::positions)
        .def("forces", &viskit::facade::FacadeParticleSystem::forces)
        .def("velocities", &viskit::facade::FacadeParticleSystem::velocities)
        .def("colors", &viskit::facade::FacadeParticleSystem::colors)
        .def("setPosition", &viskit::facade::FacadeParticleSystem::setPosition)
        .def("countAlive", &viskit::facade::FacadeParticleSystem::countAlive)
        .def("countParticles", &viskit::facade::FacadeParticleSystem::countParticles)
        .def("clear", &viskit::facade::FacadeParticleSystem::clear)
        .def("empty", &viskit::facade::FacadeParticleSystem::empty)
        .def("saveToFile", static_cast<bool (viskit::facade::FacadeParticleSystem::*)(const std::string&)>(&viskit::facade::FacadeParticleSystem::saveToFile))
        .def("saveToFile", static_cast<bool (viskit::facade::FacadeParticleSystem::*)(const std::string&, IGraph&)>(&viskit::facade::FacadeParticleSystem::saveToFile))
        .def("loadParticlesPositions", &viskit::facade::FacadeParticleSystem::loadParticlesPositions);
}
}