//
// \author Dawid Dębowski <ddebowsk@student.agh.edu.pl>
// \date 02.05.2022.
//

#include <pybind11/pybind11.h>

#include "viskit/python/bindings/PyTransformerBinding.h"

namespace py = pybind11;
using namespace py::literals;

namespace viskit::python::bindings
{
    void PyTransformerBinding::initialize(viskit::IParticleSystem& ps, viskit::IGraph& graph) {
        PYBIND11_OVERRIDE_PURE(
                void, /* Return type */
                viskit::ITransformer,      /* Parent class */
                initialize,          /* Name of function in C++ (must match Python name) */
                ps, graph      /* Argument(s) */
        );
    }

    void PyTransformerBinding::finalize() {
        PYBIND11_OVERRIDE_PURE(
                void, /* Return type */
                viskit::ITransformer,      /* Parent class */
                finalize,          /* Name of function in C++ (must match Python name) */
                /* Argument(s) */
        );
    }

    void PyTransformerBinding::step(viskit::IParticleSystem& ps, viskit::IGraph& graph) {
        PYBIND11_OVERRIDE_PURE(
                void, /* Return type */
                viskit::ITransformer,      /* Parent class */
                step,          /* Name of function in C++ (must match Python name) */
                ps, graph      /* Argument(s) */
        );
    }

    void PyTransformerBinding::bind(pybind11::module &m) {

        py::class_<viskit::ITransformer, std::shared_ptr<viskit::ITransformer>, PyTransformerBinding>(m, "ITransformer")
                // according to documentation, fully virtual classes should also have constructors. It's possible to use them in python
                // but then method invocations ends with errors. Without them however we cannot extend them in pure python classes.
                .def(py::init<>())
                .def("initialize", &viskit::ITransformer::initialize)
                .def("finalize", &viskit::ITransformer::finalize)
                .def("step", &viskit::ITransformer::step);
    }
};
