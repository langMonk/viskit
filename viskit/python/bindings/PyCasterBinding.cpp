//
// Created by Dawid on 02.05.2022.
//

#include <pybind11/pybind11.h>

#include "viskit/python/bindings/PyCasterBinding.h"
#include "viskit/viskit/ICaster.h"
#include "viskit/viskit/IParticleSystem.h"
#include "viskit/viskit/IGraph.h"

namespace py = pybind11;
using namespace py::literals;

namespace viskit::python::bindings{

    /* Trampoline (need one for each virtual function) */
    void PyCasterBinding::calculatePositions(viskit::IParticleSystem& ps) {
        PYBIND11_OVERRIDE_PURE(
                void, /* Return type */
                viskit::ICaster,      /* Parent class */
                calculatePositions,          /* Name of function in C++ (must match Python name) */
                ps      /* Argument(s) */
        );
    }

    void PyCasterBinding::calculateForces(viskit::IParticleSystem& ps, viskit::IGraph& graph) {
        PYBIND11_OVERRIDE_PURE(
                void, /* Return type */
                viskit::ICaster,      /* Parent class */
                calculateForces,          /* Name of function in C++ (must match Python name) */
                ps, graph      /* Argument(s) */
        );
    }

    viskit::CasterType PyCasterBinding::type() {
        PYBIND11_OVERRIDE_PURE(
                viskit::CasterType, /* Return type */
                viskit::ICaster,      /* Parent class */
                type,         /* Name of function in C++ (must match Python name) */
                /* Argument(s) */
        );
    }

    viskit::OptimizerType PyCasterBinding::optimizerType() {
        PYBIND11_OVERRIDE_PURE(
                viskit::OptimizerType, /* Return type */
                viskit::ICaster,      /* Parent class */
                optimizerType,         /* Name of function in C++ (must match Python name) */
                /* Argument(s) */
        );
    }

    //functions from parent class needs to be overriden too: https://pybind11.readthedocs.io/en/stable/advanced/classes.html#virtual-and-inheritance
    void PyCasterBinding::initialize(viskit::IParticleSystem& ps, viskit::IGraph& graph) {
        PYBIND11_OVERRIDE_PURE(
                void, /* Return type */
                viskit::ICaster,      /* Parent class */
                initialize,          /* Name of function in C++ (must match Python name) */
                ps, graph      /* Argument(s) */
        );
    }

    void PyCasterBinding::finalize() {
        PYBIND11_OVERRIDE_PURE(
                void, /* Return type */
                viskit::ICaster,      /* Parent class */
                finalize,          /* Name of function in C++ (must match Python name) */
                /* Argument(s) */
        );
    }

    void PyCasterBinding::step(viskit::IParticleSystem& ps, viskit::IGraph& graph) {
        PYBIND11_OVERRIDE_PURE(
                void, /* Return type */
                viskit::ICaster,      /* Parent class */
                step,          /* Name of function in C++ (must match Python name) */
                ps, graph      /* Argument(s) */
        );
    }


    void PyCasterBinding::bind(pybind11::module &m) {
        py::class_<viskit::ICaster, viskit::ITransformer, python::bindings::PyCasterBinding>(m, "ICaster")
                .def(py::init<>())
                .def("calculatePositions", &viskit::ICaster::calculatePositions)
                .def("calculateForces", &viskit::ICaster::calculateForces)
                .def("type", &viskit::ICaster::type)
                .def("optimizerType", &viskit::ICaster::optimizerType);
    }
}