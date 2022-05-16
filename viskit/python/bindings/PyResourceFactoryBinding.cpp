//
// Created by Dawid on 02.05.2022.
//

#include <pybind11/pybind11.h>

#include "viskit/python/bindings/PyResourceFactoryBinding.h"

namespace py = pybind11;
using namespace py::literals;

namespace viskit::python::bindings
{
    std::shared_ptr<viskit::IParser> PyResourceFactoryBinding::createParser(viskit::ParserType type) {
        PYBIND11_OVERRIDE_PURE(
                std::shared_ptr<viskit::IParser>, /* Return type */
                viskit::IResourceFactory,      /* Parent class */
                createParser,          /* Name of function in C++ (must match Python name) */
                type      /* Argument(s) */
        );
    }

    std::shared_ptr<viskit::IGraphGenerator> PyResourceFactoryBinding::createGraphGenerator(viskit::GraphGeneratorType type) {
        PYBIND11_OVERRIDE_PURE(
                std::shared_ptr<viskit::IGraphGenerator>, /* Return type */
                viskit::IResourceFactory,      /* Parent class */
                createParser,          /* Name of function in C++ (must match Python name) */
                type      /* Argument(s) */
        );
    }

    std::shared_ptr<viskit::ICaster> PyResourceFactoryBinding::createCaster(viskit::CasterType type, viskit::OptimizerType optimizer) {
        PYBIND11_OVERRIDE_PURE(
                std::shared_ptr<viskit::ICaster>, /* Return type */
                viskit::IResourceFactory,      /* Parent class */
                createCaster,          /* Name of function in C++ (must match Python name) */
                type, optimizer      /* Argument(s) */
        );
    }

    std::shared_ptr<viskit::IParticleSystem> PyResourceFactoryBinding::createParticleSystem() {
        PYBIND11_OVERRIDE_PURE(
                std::shared_ptr<viskit::IParticleSystem>, /* Return type */
                viskit::IResourceFactory,      /* Parent class */
                createParticleSystem,          /* Name of function in C++ (must match Python name) */
                      /* Argument(s) */
        );
    }

    std::shared_ptr<viskit::IGraph> PyResourceFactoryBinding::createGraph() {
        PYBIND11_OVERRIDE_PURE(
                std::shared_ptr<viskit::IGraph>, /* Return type */
                viskit::IResourceFactory,      /* Parent class */
                createGraph,          /* Name of function in C++ (must match Python name) */
                /* Argument(s) */
        );
    }

    std::shared_ptr<viskit::IMetric> PyResourceFactoryBinding::createMetricCalculator() {
        PYBIND11_OVERRIDE_PURE(
                std::shared_ptr<viskit::IMetric>, /* Return type */
                viskit::IResourceFactory,      /* Parent class */
                createMetricCalculator,          /* Name of function in C++ (must match Python name) */
                /* Argument(s) */
        );
    }

    void PyResourceFactoryBinding::bind(pybind11::module &m) {

        py::class_<viskit::IResourceFactory, std::unique_ptr<viskit::IResourceFactory, py::nodelete>, PyResourceFactoryBinding>(m, "IResourceFactory")
                .def(py::init<>())
                .def("createParser", &viskit::IResourceFactory::createParser)
                .def("createGraphGenerator", &viskit::IResourceFactory::createGraphGenerator)
                .def("createCaster", &viskit::IResourceFactory::createCaster)
                .def("createParticleSystem", &viskit::IResourceFactory::createParticleSystem)
                .def("createGraph", &viskit::IResourceFactory::createGraph)
                .def("createMetricCalculator", &viskit::IResourceFactory::createMetricCalculator);

        py::class_<viskit::facade::FacadeResourceFactory, viskit::IResourceFactory>(m, "FacadeResourceFactory")
                .def(py::init<viskit::facade::FacadeInteractiveVisualization&>());
    }
};

