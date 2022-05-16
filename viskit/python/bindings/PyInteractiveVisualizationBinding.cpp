//
// Created by Dawid on 02.05.2022.
//

#include <pybind11/pybind11.h>

#include "viskit/python/bindings/PyInteractiveVisualizationBinding.h"
#include "viskit/viskit/IInteractiveVisualization.h"
#include "viskit/viskit/IResourceFactory.h"
#include "viskit/viskit/IGraph.h"
#include "viskit/viskit/ICaster.h"
#include "viskit/viskit/IParticleSystem.h"

namespace py = pybind11;
using namespace py::literals;

namespace viskit::python::bindings
{
    viskit::IResourceFactory& PyInteractiveVisualizationBinding::resourceFactory() {
        PYBIND11_OVERRIDE_PURE(
                viskit::IResourceFactory&, /* Return type */
                viskit::IInteractiveVisualization,      /* Parent class */
                resourceFactory,          /* Name of function in C++ (must match Python name) */
                     /* Argument(s) */
        );
    }

    void PyInteractiveVisualizationBinding::computeCastingStep(viskit::IParticleSystem& ps, viskit::IGraph& graph, viskit::ICaster& caster) {
        PYBIND11_OVERRIDE_PURE(
                void, /* Return type */
                viskit::IInteractiveVisualization,      /* Parent class */
                computeCastingStep,          /* Name of function in C++ (must match Python name) */
                ps, graph, caster /* Argument(s) */
        );
    }

    typedef std::vector<std::pair<float, float>> vector_of_pairs;

    std::vector<std::pair<float, float>> PyInteractiveVisualizationBinding::calculateBoundingBox() {
        PYBIND11_OVERRIDE_PURE(
                vector_of_pairs, /* Return type */
                viskit::IInteractiveVisualization,      /* Parent class */
                calculateBoundingBox,          /* Name of function in C++ (must match Python name) */
                 /* Argument(s) */
        );
    }

    void PyInteractiveVisualizationBinding::subscribeOnCastingStepFinish(viskit::IInteractiveVisualization::CasterEventHandler handler) {
        PYBIND11_OVERRIDE_PURE(
                void, /* Return type */
                viskit::IInteractiveVisualization,      /* Parent class */
                subscribeOnCastingStepFinish,          /* Name of function in C++ (must match Python name) */
                handler /* Argument(s) */
        );
    }

    void PyInteractiveVisualizationBinding::bind(pybind11::module& m) {

        py::class_<viskit::IInteractiveVisualization, std::unique_ptr<viskit::IInteractiveVisualization, py::nodelete>, PyInteractiveVisualizationBinding>(m, "IInteractiveVisualization")
                .def(py::init<>())
                .def("resourceFactory", &viskit::IInteractiveVisualization::resourceFactory)
                .def("computeCastingStep", &viskit::IInteractiveVisualization::computeCastingStep)
                .def("calculateBoundingBox", &viskit::IInteractiveVisualization::calculateBoundingBox)
                .def("subscribeOnCastingStepFinish", &viskit::IInteractiveVisualization::subscribeOnCastingStepFinish);

//        py::class_<viskit::facade::FacadeInteractiveVisualization, viskit::IInteractiveVisualization>(m, "FacadeInteractiveVisualization")
//                .def(py::init<viskit::LogHandler>());
    }
}
