//
// \author Dawid Dębowski <ddebowsk@student.agh.edu.pl>
// \date 21.05.2022.
//

#pragma once

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include "viskit/viskit/IGraph.h"
#include "viskit/viskit/IGraphGenerator.h"
#include "viskit/viskit/Structures.h"

namespace viskit::python::bindings {
class PyGraphGeneratorBinding : public IGraphGenerator {
public:
    void generate(IParticleSystem& ps, IGraph& graph, size_t k, bool distancesEqualOne) override;
    void generate(IParticleSystem& ps, IGraph& graph, IGraph& graphHelper, size_t k, bool distancesEqualOne) override;
    void generate(IParticleSystem& ps, IGraph& graph, IGraph& graphHelper) override;
    static void bind(pybind11::module& m);
};
}