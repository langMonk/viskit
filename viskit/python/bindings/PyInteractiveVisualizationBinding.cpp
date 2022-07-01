//
// \author Dawid Dębowski <ddebowsk@student.agh.edu.pl>
// \date 02.05.2022.
//

#include <pybind11/pybind11.h>
#include <pybind11/functional.h>

#include "viskit/python/bindings/PyInteractiveVisualizationBinding.h"
#include "viskit/viskit/IInteractiveVisualization.h"
#include "viskit/viskit/InteractiveVisualizationBuilder.h"
#include "viskit/viskit/IResourceFactory.h"
#include "viskit/viskit/IGraph.h"
#include "viskit/viskit/ICaster.h"
#include "viskit/viskit/IParticleSystem.h"
#include "viskit/facade/FacadeInteractiveVisualization.h"

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
                .def("resourceFactory", &viskit::IInteractiveVisualization::resourceFactory,py::return_value_policy::reference)
                .def("computeCastingStep", &viskit::IInteractiveVisualization::computeCastingStep)
                .def("calculateBoundingBox", &viskit::IInteractiveVisualization::calculateBoundingBox)
                .def("subscribeOnCastingStepFinish", &viskit::IInteractiveVisualization::subscribeOnCastingStepFinish);

        py::class_<viskit::facade::FacadeInteractiveVisualization, std::unique_ptr<viskit::facade::FacadeInteractiveVisualization, py::nodelete>, viskit::IInteractiveVisualization>(m, "FacadeInteractiveVisualization")
                .def(py::init<const viskit::LogHandler&>())
                .def("resourceFactory", &viskit::facade::FacadeInteractiveVisualization::resourceFactory, py::return_value_policy::reference)
                .def("computeCastingStep", [](viskit::facade::FacadeInteractiveVisualization& self, viskit::IParticleSystem& ps, viskit::IGraph& graph, viskit::ICaster& caster) -> void {
                    self.computeCastingStep(ps, graph, caster);
                })
                .def("calculateBoundingBox", &viskit::facade::FacadeInteractiveVisualization::calculateBoundingBox)
                .def("subscribeOnCastingStepFinish", &viskit::facade::FacadeInteractiveVisualization::subscribeOnCastingStepFinish);

        m.def("create_viskit", &viskit::createViskit, py::arg("logHandler") = viskit::LogHandler{});
    }



}
