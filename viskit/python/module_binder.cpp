//
// \author Dawid Dębowski <ddebowsk@student.agh.edu.pl>
// \date 24.04.2022.
//

#include <pybind11/pybind11.h>

#include "viskit/python/bindings/PyCasterBinding.h"
#include "viskit/python/bindings/PyInteractiveVisualizationBinding.h"
#include "viskit/python/bindings/PyTransformerBinding.h"
#include "viskit/python/bindings/PyResourceFactoryBinding.h"
#include "viskit/python/bindings/PyStructuresBinding.h"
#include "viskit/python/bindings/PyParserBinding.h"
#include "viskit/python/bindings/PyDataPointBinding.h"
#include "viskit/python/bindings/PyParticleSystemBinding.h"
#include "viskit/python/bindings/PyGraphBinding.h"
#include "viskit/python/bindings/PyGraphGeneratorBinding.h"
#include "viskit/python/bindings/PyFacadeCasterBinding.h"

#define STRINGIFY(x) #x
#define MACRO_STRINGIFY(x) STRINGIFY(x)

namespace py = pybind11;
using namespace py::literals;

PYBIND11_MODULE(pyviskit_bindings, m) {
    viskit::python::bindings::PyTransformerBinding::bind(m);
    viskit::python::bindings::PyCasterBinding::bind(m);
    viskit::python::bindings::PyResourceFactoryBinding::bind(m);
    viskit::python::bindings::PyStructuresBinding::bind(m);
    viskit::python::bindings::PyInteractiveVisualizationBinding::bind(m);
    viskit::python::bindings::PyParserBinding::bind(m);
    viskit::python::bindings::PyDataPointBinding::bind(m);
    viskit::python::bindings::PyParticleSystemBinding::bind(m);
    viskit::python::bindings::PyGraphBinding::bind(m);
    viskit::python::bindings::PyGraphGeneratorBinding::bind(m);
    viskit::python::bindings::PyFacadeCasterBinding::bind(m);

#ifdef VERSION_INFO
    m.attr("__version__") = MACRO_STRINGIFY(VERSION_INFO);
#else
    m.attr("__version__") = "dev";
#endif
}
