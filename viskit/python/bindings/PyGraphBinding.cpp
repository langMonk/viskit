//
// \author Dawid Dębowski <ddebowsk@student.agh.edu.pl>
// \date 21.05.2022.
//

#include <pybind11/pybind11.h>

#include "viskit/core/Core.h"
#include "viskit/facade/FacadeGraph.h"
#include "viskit/python/bindings/PyGraphBinding.h"

namespace py = pybind11;
using namespace py::literals;

namespace viskit::python::bindings {

void PyGraphBinding::initialize(size_t size)
{
    PYBIND11_OVERRIDE_PURE(
        void, /* Return type */
        viskit::IGraph, /* Parent class */
        initialize, /* Name of function in C++ (must match Python name) */
        size /* Argument(s) */
    );
}

std::vector<Neighbors> PyGraphBinding::getNeighbors(size_t index)
{
    PYBIND11_OVERRIDE_PURE(
        std::vector<Neighbors>, /* Return type */
        viskit::IGraph, /* Parent class */
        getNeighbors, /* Name of function in C++ (must match Python name) */
        index /* Argument(s) */
    );
}

void PyGraphBinding::addNeighbors(std::vector<Neighbors> neighbors)
{
    PYBIND11_OVERRIDE_PURE(
        void, /* Return type */
        viskit::IGraph, /* Parent class */
        addNeighbors, /* Name of function in C++ (must match Python name) */
        neighbors /* Argument(s) */
    );
}

void PyGraphBinding::addNeighbors(Neighbors neighbors)
{
    PYBIND11_OVERRIDE_PURE(
        void, /* Return type */
        viskit::IGraph, /* Parent class */
        addNeighbors, /* Name of function in C++ (must match Python name) */
        neighbors /* Argument(s) */
    );
}

viskit::NeighborsCounter PyGraphBinding::neighborsCounter()
{
    PYBIND11_OVERRIDE_PURE(
        viskit::NeighborsCounter, /* Return type */
        viskit::IGraph, /* Parent class */
        neighborsCounter, /* Name of function in C++ (must match Python name) */
        /* Argument(s) */
    );
}

size_t PyGraphBinding::overallNeighborsCount()
{
    PYBIND11_OVERRIDE_PURE(
        size_t, /* Return type */
        viskit::IGraph, /* Parent class */
        overallNeighborsCount, /* Name of function in C++ (must match Python name) */
        /* Argument(s) */
    );
}

size_t PyGraphBinding::size()
{
    PYBIND11_OVERRIDE_PURE(
        size_t, /* Return type */
        viskit::IGraph, /* Parent class */
        size, /* Name of function in C++ (must match Python name) */
        /* Argument(s) */
    );
}

void PyGraphBinding::sort()
{
    PYBIND11_OVERRIDE_PURE(
        void, /* Return type */
        viskit::IGraph, /* Parent class */
        sort, /* Name of function in C++ (must match Python name) */
        /* Argument(s) */
    );
}

bool PyGraphBinding::saveNearestNeighborsToCache(const std::string& fileName)
{
    PYBIND11_OVERRIDE_PURE(
        bool, /* Return type */
        viskit::IGraph, /* Parent class */
        saveNearestNeighborsToCache, /* Name of function in C++ (must match Python name) */
        fileName /* Argument(s) */
    );
}

void PyGraphBinding::removeRandomNeighbors()
{
    PYBIND11_OVERRIDE_PURE(
        void, /* Return type */
        viskit::IGraph, /* Parent class */
        removeRandomNeighbors, /* Name of function in C++ (must match Python name) */
        /* Argument(s) */
    );
}

bool PyGraphBinding::loadNearestNeighborsFromCache(const std::string& fileName, size_t nearestNeighborsCountToRead,
    bool binaryDistances)
{
    PYBIND11_OVERRIDE_PURE(
        bool, /* Return type */
        viskit::IGraph, /* Parent class */
        loadNearestNeighborsFromCache, /* Name of function in C++ (must match Python name) */
        fileName, nearestNeighborsCountToRead, binaryDistances /* Argument(s) */
    );
}

void PyGraphBinding::dump(std::string filePath, std::string fileName)
{
    PYBIND11_OVERRIDE_PURE(
        void, /* Return type */
        viskit::IGraph, /* Parent class */
        dump, /* Name of function in C++ (must match Python name) */
        filePath, fileName /* Argument(s) */
    );
}

void PyGraphBinding::bind(pybind11::module& m)
{

    py::class_<viskit::IGraph, std::shared_ptr<viskit::IGraph>, PyGraphBinding>(m, "IGraph")
        .def(py::init<>())
        .def("initialize", &viskit::IGraph::initialize)
        .def("getNeighbors", &viskit::IGraph::getNeighbors)
        .def("addNeighbors", static_cast<void (viskit::IGraph::*)(std::vector<Neighbors> neighbors)>(&viskit::IGraph::addNeighbors))
        .def("addNeighbors", static_cast<void (viskit::IGraph::*)(Neighbors neighbors)>(&viskit::IGraph::addNeighbors))
        .def("neighborsCounter", &viskit::IGraph::neighborsCounter)
        .def("overallNeighborsCount", &viskit::IGraph::overallNeighborsCount)
        .def("size", &viskit::IGraph::size)
        .def("sort", &viskit::IGraph::sort)
        .def("saveNearestNeighborsToCache", &viskit::IGraph::saveNearestNeighborsToCache)
        .def("removeRandomNeighbors", &viskit::IGraph::removeRandomNeighbors)
        .def("loadNearestNeighborsFromCache", &viskit::IGraph::loadNearestNeighborsFromCache)
        .def("dump", &viskit::IGraph::dump);

    py::class_<viskit::facade::FacadeGraph, std::shared_ptr<viskit::facade::FacadeGraph>, IGraph>(m, "FacadeGraph")
        .def(py::init<const std::shared_ptr<core::Core>&>())
        .def("initialize", &viskit::facade::FacadeGraph::initialize)
        .def("getNeighbors", &viskit::facade::FacadeGraph::getNeighbors)
        .def("addNeighbors", static_cast<void (viskit::facade::FacadeGraph::*)(std::vector<Neighbors> neighbors)>(&viskit::facade::FacadeGraph::addNeighbors))
        .def("addNeighbors", static_cast<void (viskit::facade::FacadeGraph::*)(Neighbors neighbors)>(&viskit::facade::FacadeGraph::addNeighbors))
        .def("neighborsCounter", &viskit::facade::FacadeGraph::neighborsCounter)
        .def("overallNeighborsCount", &viskit::facade::FacadeGraph::overallNeighborsCount)
        .def("size", &viskit::facade::FacadeGraph::size)
        .def("sort", &viskit::facade::FacadeGraph::sort)
        .def("saveNearestNeighborsToCache", &viskit::facade::FacadeGraph::saveNearestNeighborsToCache)
        .def("removeRandomNeighbors", &viskit::facade::FacadeGraph::removeRandomNeighbors)
        .def("loadNearestNeighborsFromCache", &viskit::facade::FacadeGraph::loadNearestNeighborsFromCache)
        .def("dump", &viskit::facade::FacadeGraph::dump);
}

}