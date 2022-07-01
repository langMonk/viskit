//
// \author Dawid Dębowski <ddebowsk@student.agh.edu.pl>
// \date 21.05.2022.
//

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include "viskit/python/bindings/PyGraphGeneratorBinding.h"
#include "viskit/core/Core.h"
#include "viskit/facade/FacadeGraphGenerator.h"
#include "viskit/facade/FacadeGraphGeneratorRandom.h"
#include "viskit/facade/FacadeGraphGeneratorBruteForce.h"
#include "viskit/facade/FacadeGraphGeneratorKDTree.h"
#include "viskit/facade/FacadeGraphGeneratorReverse.h"

namespace py = pybind11;
using namespace py::literals;

namespace viskit::python::bindings {

    void PyGraphGeneratorBinding::generate(IParticleSystem& ps, IGraph& graph, size_t k , bool distancesEqualOne) {
        PYBIND11_OVERRIDE_PURE(
                void, /* Return type */
                viskit::IGraphGenerator,      /* Parent class */
                generate,          /* Name of function in C++ (must match Python name) */
                ps, graph, k, distancesEqualOne/* Argument(s) */
        );
    }

    void PyGraphGeneratorBinding::generate(IParticleSystem &ps, IGraph &graph, IGraph &graphHelper) {
        PYBIND11_OVERRIDE_PURE(
                void, /* Return type */
                viskit::IGraphGenerator,      /* Parent class */
                generate,          /* Name of function in C++ (must match Python name) */
                ps, graph, graphHelper/* Argument(s) */
        );
    }

    void PyGraphGeneratorBinding::generate(IParticleSystem &ps, IGraph &graph, IGraph &graphHelper, size_t k, bool distancesEqualOne) {
        PYBIND11_OVERRIDE_PURE(
                void, /* Return type */
                viskit::IGraphGenerator,      /* Parent class */
                generate,          /* Name of function in C++ (must match Python name) */
                ps, graph, graphHelper, k, distancesEqualOne/* Argument(s) */
        );
    }

    void PyGraphGeneratorBinding::bind(pybind11::module &m) {

        py::class_<viskit::IGraphGenerator, std::shared_ptr<viskit::IGraphGenerator>, PyGraphGeneratorBinding>(m, "IGraphGenerator")
                .def(py::init<>())
                .def("generate", static_cast<void (viskit::IGraphGenerator::*)(IParticleSystem& ps, IGraph& graph, size_t k , bool distancesEqualOne)>(&viskit::IGraphGenerator::generate))
                .def("generate", static_cast<void (viskit::IGraphGenerator::*)(IParticleSystem &ps, IGraph &graph, IGraph &graphHelper)>(&viskit::IGraphGenerator::generate))
                .def("generate", static_cast<void (viskit::IGraphGenerator::*)(IParticleSystem &ps, IGraph &graph, IGraph &graphHelper, size_t k, bool distancesEqualOne)>(&viskit::IGraphGenerator::generate));


        py::class_<viskit::facade::FacadeGraphGenerator, std::shared_ptr<viskit::facade::FacadeGraphGenerator>, viskit::IGraphGenerator>(m, "FacadeGraphGenerator")
                .def(py::init<std::shared_ptr<core::Core>>())
                .def("generate", static_cast<void (viskit::facade::FacadeGraphGenerator::*)(IParticleSystem &ps, IGraph &graph, IGraph &graphHelper)>(&viskit::facade::FacadeGraphGenerator::generate))
                .def("generate", static_cast<void (viskit::facade::FacadeGraphGenerator::*)(IParticleSystem& ps, IGraph& graph, size_t k , bool distancesEqualOne)>(&viskit::facade::FacadeGraphGenerator::generate))
                .def("generate", static_cast<void (viskit::facade::FacadeGraphGenerator::*)(IParticleSystem &ps, IGraph &graph, IGraph &graphHelper, size_t k, bool distancesEqualOne)>(&viskit::facade::FacadeGraphGenerator::generate));

        py::class_<viskit::facade::FacadeGraphGeneratorRandom, std::shared_ptr<viskit::facade::FacadeGraphGeneratorRandom>, viskit::facade::FacadeGraphGenerator>(m, "FacadeGraphGeneratorRandom")
                .def(py::init<const std::shared_ptr<core::Core>&>())
                .def("generate", static_cast<void (viskit::facade::FacadeGraphGenerator::*)(IParticleSystem &ps, IGraph &graph, IGraph &graphHelper)>(&viskit::facade::FacadeGraphGenerator::generate))
                .def("generate", static_cast<void (viskit::facade::FacadeGraphGenerator::*)(IParticleSystem& ps, IGraph& graph, size_t k , bool distancesEqualOne)>(&viskit::facade::FacadeGraphGenerator::generate))
                .def("generate", static_cast<void (viskit::facade::FacadeGraphGenerator::*)(IParticleSystem &ps, IGraph &graph, IGraph &graphHelper, size_t k, bool distancesEqualOne)>(&viskit::facade::FacadeGraphGenerator::generate));

        py::class_<viskit::facade::FacadeGraphGeneratorBruteForce, std::shared_ptr<viskit::facade::FacadeGraphGeneratorBruteForce>, viskit::facade::FacadeGraphGenerator>(m, "FacadeGraphGeneratorBruteForce")
                .def(py::init<const std::shared_ptr<core::Core>&>())
                .def("generate", static_cast<void (viskit::facade::FacadeGraphGenerator::*)(IParticleSystem &ps, IGraph &graph, IGraph &graphHelper)>(&viskit::facade::FacadeGraphGenerator::generate))
                .def("generate", static_cast<void (viskit::facade::FacadeGraphGenerator::*)(IParticleSystem& ps, IGraph& graph, size_t k , bool distancesEqualOne)>(&viskit::facade::FacadeGraphGenerator::generate))
                .def("generate", static_cast<void (viskit::facade::FacadeGraphGenerator::*)(IParticleSystem &ps, IGraph &graph, IGraph &graphHelper, size_t k, bool distancesEqualOne)>(&viskit::facade::FacadeGraphGenerator::generate));

        py::class_<viskit::facade::FacadeGraphGeneratorKDTree, std::shared_ptr<viskit::facade::FacadeGraphGeneratorKDTree>, viskit::facade::FacadeGraphGenerator>(m, "FacadeGraphGeneratorKDTree")
                .def(py::init<const std::shared_ptr<core::Core>&>())
                .def("generate", static_cast<void (viskit::facade::FacadeGraphGenerator::*)(IParticleSystem &ps, IGraph &graph, IGraph &graphHelper)>(&viskit::facade::FacadeGraphGenerator::generate))
                .def("generate", static_cast<void (viskit::facade::FacadeGraphGenerator::*)(IParticleSystem& ps, IGraph& graph, size_t k , bool distancesEqualOne)>(&viskit::facade::FacadeGraphGenerator::generate))
                .def("generate", static_cast<void (viskit::facade::FacadeGraphGenerator::*)(IParticleSystem &ps, IGraph &graph, IGraph &graphHelper, size_t k, bool distancesEqualOne)>(&viskit::facade::FacadeGraphGenerator::generate));

        py::class_<viskit::facade::FacadeGraphGeneratorReverse, std::shared_ptr<viskit::facade::FacadeGraphGeneratorReverse>, viskit::facade::FacadeGraphGenerator>(m, "FacadeGraphGeneratorReverse")
                .def(py::init<const std::shared_ptr<core::Core>&>())
                .def("generate", static_cast<void (viskit::facade::FacadeGraphGenerator::*)(IParticleSystem &ps, IGraph &graph, IGraph &graphHelper)>(&viskit::facade::FacadeGraphGenerator::generate))
                .def("generate", static_cast<void (viskit::facade::FacadeGraphGenerator::*)(IParticleSystem& ps, IGraph& graph, size_t k , bool distancesEqualOne)>(&viskit::facade::FacadeGraphGenerator::generate))
                .def("generate", static_cast<void (viskit::facade::FacadeGraphGenerator::*)(IParticleSystem &ps, IGraph &graph, IGraph &graphHelper, size_t k, bool distancesEqualOne)>(&viskit::facade::FacadeGraphGenerator::generate));

    }
}