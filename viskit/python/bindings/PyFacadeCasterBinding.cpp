//
// \author Dawid Dębowski <ddebowsk@student.agh.edu.pl>
// \date 22.05.2022.
//

#include <pybind11/pybind11.h>

#include "viskit/facade/FacadeCasterAdadelta.h"
#include "viskit/facade/FacadeCasterAdam.h"
#include "viskit/facade/FacadeCasterForceDirected.h"
#include "viskit/facade/FacadeCasterLargeVis.h"
#include "viskit/facade/FacadeCasterMomentum.h"
#include "viskit/facade/FacadeCasterNesterov.h"
#include "viskit/facade/FacadeCasterRandom.h"
#include "viskit/facade/FacadeCasterSGD.h"
#include "viskit/facade/FacadeCasterTSNE.h"
#include "viskit/python/bindings/PyFacadeCasterBinding.h"
#include "viskit/viskit/IParser.h"
#include "viskit/viskit/IParticleSystem.h"

namespace py = pybind11;
using namespace py::literals;

namespace viskit::python::bindings {
void PyFacadeCasterBinding::calculatePositions(viskit::IParticleSystem& ps)
{
    PYBIND11_OVERRIDE_PURE(
        void, /* Return type */
        viskit::facade::FacadeCaster, /* Parent class */
        calculatePositions, /* Name of function in C++ (must match Python name) */
        ps /* Argument(s) */
    );
}

void PyFacadeCasterBinding::calculateForces(viskit::IParticleSystem& ps, viskit::IGraph& graph)
{
    PYBIND11_OVERRIDE_PURE(
        void, /* Return type */
        viskit::facade::FacadeCaster, /* Parent class */
        calculateForces, /* Name of function in C++ (must match Python name) */
        ps, graph /* Argument(s) */
    );
}

viskit::CasterType PyFacadeCasterBinding::type()
{
    PYBIND11_OVERRIDE_PURE(
        viskit::CasterType, /* Return type */
        viskit::facade::FacadeCaster, /* Parent class */
        type, /* Name of function in C++ (must match Python name) */
        /* Argument(s) */
    );
}

viskit::OptimizerType PyFacadeCasterBinding::optimizerType()
{
    PYBIND11_OVERRIDE_PURE(
        viskit::OptimizerType, /* Return type */
        viskit::facade::FacadeCaster, /* Parent class */
        optimizerType, /* Name of function in C++ (must match Python name) */
        /* Argument(s) */
    );
}

// functions from parent class needs to be overriden too: https://pybind11.readthedocs.io/en/stable/advanced/classes.html#virtual-and-inheritance
void PyFacadeCasterBinding::initialize(viskit::IParticleSystem& ps, viskit::IGraph& graph)
{
    PYBIND11_OVERRIDE_PURE(
        void, /* Return type */
        viskit::facade::FacadeCaster, /* Parent class */
        initialize, /* Name of function in C++ (must match Python name) */
        ps, graph /* Argument(s) */
    );
}

void PyFacadeCasterBinding::finalize()
{
    PYBIND11_OVERRIDE_PURE(
        void, /* Return type */
        viskit::facade::FacadeCaster, /* Parent class */
        finalize, /* Name of function in C++ (must match Python name) */
        /* Argument(s) */
    );
}

void PyFacadeCasterBinding::step(viskit::IParticleSystem& ps, viskit::IGraph& graph)
{
    PYBIND11_OVERRIDE_PURE(
        void, /* Return type */
        viskit::facade::FacadeCaster, /* Parent class */
        step, /* Name of function in C++ (must match Python name) */
        ps, graph /* Argument(s) */
    );
}

void PyFacadeCasterBinding::bind(pybind11::module& m)
{
    py::class_<viskit::facade::FacadeCaster, std::shared_ptr<viskit::facade::FacadeCaster>, python::bindings::PyFacadeCasterBinding, viskit::ICaster>(m, "FacadeCaster")
        .def(py::init<std::shared_ptr<core::Core>>())
        .def("step", &viskit::facade::FacadeCaster::step)
        .def("initialize", &viskit::facade::FacadeCaster::initialize)
        .def("finalize", &viskit::facade::FacadeCaster::finalize);

    py::class_<viskit::facade::FacadeCasterRandom, std::shared_ptr<viskit::facade::FacadeCasterRandom>, viskit::facade::FacadeCaster>(m, "FacadeCasterRandom")
        .def(py::init<const std::shared_ptr<core::Core>&>())
        .def("calculatePositions", &viskit::facade::FacadeCasterRandom::calculatePositions)
        .def("calculateForces", &viskit::facade::FacadeCasterRandom::calculateForces)
        .def("type", &viskit::facade::FacadeCasterRandom::type)
        .def("optimizerType", &viskit::facade::FacadeCasterRandom::optimizerType)
        .def("step", &viskit::facade::FacadeCasterRandom::step)
        .def("initialize", &viskit::facade::FacadeCasterRandom::initialize)
        .def("finalize", &viskit::facade::FacadeCasterRandom::finalize);

    py::class_<viskit::facade::FacadeCasterAdadelta, std::shared_ptr<viskit::facade::FacadeCasterAdadelta>, viskit::facade::FacadeCaster>(m, "FacadeCasterAdadelta")
        .def(py::init<const std::shared_ptr<core::Core>&>())
        .def("calculatePositions", &viskit::facade::FacadeCasterAdadelta::calculatePositions)
        .def("calculateForces", &viskit::facade::FacadeCasterAdadelta::calculateForces)
        .def("type", &viskit::facade::FacadeCasterAdadelta::type)
        .def("optimizerType", &viskit::facade::FacadeCasterAdadelta::optimizerType)
        .def("step", &viskit::facade::FacadeCasterAdadelta::step)
        .def("initialize", &viskit::facade::FacadeCasterAdadelta::initialize)
        .def("finalize", &viskit::facade::FacadeCasterAdadelta::finalize);

    py::class_<viskit::facade::FacadeCasterAdam, std::shared_ptr<viskit::facade::FacadeCasterAdam>, viskit::facade::FacadeCaster>(m, "FacadeCasterAdam")
        .def(py::init<const std::shared_ptr<core::Core>&>())
        .def("calculatePositions", &viskit::facade::FacadeCasterAdam::calculatePositions)
        .def("calculateForces", &viskit::facade::FacadeCasterAdam::calculateForces)
        .def("type", &viskit::facade::FacadeCasterAdam::type)
        .def("optimizerType", &viskit::facade::FacadeCasterAdam::optimizerType)
        .def("step", &viskit::facade::FacadeCasterAdam::step)
        .def("initialize", &viskit::facade::FacadeCasterAdam::initialize)
        .def("finalize", &viskit::facade::FacadeCasterAdam::finalize);

    py::class_<viskit::facade::FacadeCasterForceDirected, std::shared_ptr<viskit::facade::FacadeCasterForceDirected>, viskit::facade::FacadeCaster>(m, "FacadeCasterForceDirected")
        .def(py::init<const std::shared_ptr<core::Core>&>())
        .def("calculatePositions", &viskit::facade::FacadeCasterForceDirected::calculatePositions)
        .def("calculateForces", &viskit::facade::FacadeCasterForceDirected::calculateForces)
        .def("type", &viskit::facade::FacadeCasterForceDirected::type)
        .def("optimizerType", &viskit::facade::FacadeCasterForceDirected::optimizerType)
        .def("step", &viskit::facade::FacadeCasterForceDirected::step)
        .def("initialize", &viskit::facade::FacadeCasterForceDirected::initialize)
        .def("finalize", &viskit::facade::FacadeCasterForceDirected::finalize);

    py::class_<viskit::facade::FacadeCasterLargeVis, std::shared_ptr<viskit::facade::FacadeCasterLargeVis>, viskit::facade::FacadeCaster>(m, "FacadeCasterLargeVis")
        .def(py::init<const std::shared_ptr<core::Core>&>())
        .def("calculatePositions", &viskit::facade::FacadeCasterLargeVis::calculatePositions)
        .def("calculateForces", &viskit::facade::FacadeCasterLargeVis::calculateForces)
        .def("type", &viskit::facade::FacadeCasterLargeVis::type)
        .def("optimizerType", &viskit::facade::FacadeCasterLargeVis::optimizerType)
        .def("step", &viskit::facade::FacadeCasterLargeVis::step)
        .def("initialize", &viskit::facade::FacadeCasterLargeVis::initialize)
        .def("finalize", &viskit::facade::FacadeCasterLargeVis::finalize);

    py::class_<viskit::facade::FacadeCasterMomentum, std::shared_ptr<viskit::facade::FacadeCasterMomentum>, viskit::facade::FacadeCaster>(m, "FacadeCasterMomentum")
        .def(py::init<const std::shared_ptr<core::Core>&>())
        .def("calculatePositions", &viskit::facade::FacadeCasterMomentum::calculatePositions)
        .def("calculateForces", &viskit::facade::FacadeCasterMomentum::calculateForces)
        .def("type", &viskit::facade::FacadeCasterMomentum::type)
        .def("optimizerType", &viskit::facade::FacadeCasterMomentum::optimizerType)
        .def("step", &viskit::facade::FacadeCasterMomentum::step)
        .def("initialize", &viskit::facade::FacadeCasterMomentum::initialize)
        .def("finalize", &viskit::facade::FacadeCasterMomentum::finalize);

    py::class_<viskit::facade::FacadeCasterNesterov, std::shared_ptr<viskit::facade::FacadeCasterNesterov>, viskit::facade::FacadeCaster>(m, "FacadeCasterNesterov")
        .def(py::init<const std::shared_ptr<core::Core>&>())
        .def("calculatePositions", &viskit::facade::FacadeCasterNesterov::calculatePositions)
        .def("calculateForces", &viskit::facade::FacadeCasterNesterov::calculateForces)
        .def("type", &viskit::facade::FacadeCasterNesterov::type)
        .def("optimizerType", &viskit::facade::FacadeCasterNesterov::optimizerType)
        .def("step", &viskit::facade::FacadeCasterNesterov::step)
        .def("initialize", &viskit::facade::FacadeCasterNesterov::initialize)
        .def("finalize", &viskit::facade::FacadeCasterNesterov::finalize);

    py::class_<viskit::facade::FacadeCasterSGD, std::shared_ptr<viskit::facade::FacadeCasterSGD>, viskit::facade::FacadeCaster>(m, "FacadeCasterSGD")
        .def(py::init<const std::shared_ptr<core::Core>&>())
        .def("calculatePositions", &viskit::facade::FacadeCasterSGD::calculatePositions)
        .def("calculateForces", &viskit::facade::FacadeCasterSGD::calculateForces)
        .def("type", &viskit::facade::FacadeCasterSGD::type)
        .def("optimizerType", &viskit::facade::FacadeCasterSGD::optimizerType)
        .def("step", &viskit::facade::FacadeCasterSGD::step)
        .def("initialize", &viskit::facade::FacadeCasterSGD::initialize)
        .def("finalize", &viskit::facade::FacadeCasterSGD::finalize);

    py::class_<viskit::facade::FacadeCasterTSNE, std::shared_ptr<viskit::facade::FacadeCasterTSNE>, viskit::facade::FacadeCaster>(m, "FacadeCasterTSNE")
        .def(py::init<const std::shared_ptr<core::Core>&>())
        .def("calculatePositions", &viskit::facade::FacadeCasterTSNE::calculatePositions)
        .def("calculateForces", &viskit::facade::FacadeCasterTSNE::calculateForces)
        .def("type", &viskit::facade::FacadeCasterTSNE::type)
        .def("optimizerType", &viskit::facade::FacadeCasterTSNE::optimizerType)
        .def("step", &viskit::facade::FacadeCasterTSNE::step)
        .def("initialize", &viskit::facade::FacadeCasterTSNE::initialize)
        .def("finalize", &viskit::facade::FacadeCasterTSNE::finalize);
}

}