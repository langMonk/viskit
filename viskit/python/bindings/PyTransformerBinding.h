//
// Created by Bartosz Minch on 02/05/2022.
//

#pragma once

#include <pybind11/pybind11.h>

#include "viskit/viskit/IGraph.h"
#include "viskit/viskit/IParticleSystem.h"
#include "viskit/viskit/ITransformer.h"

namespace viskit::python::bindings {
class PyTransformerBinding : public ITransformer {
public:
    using ITransformer::ITransformer;

    void initialize(viskit::IParticleSystem& ps, viskit::IGraph& graph) override;

    void finalize() override;

    void step(viskit::IParticleSystem& ps, viskit::IGraph& graph) override;

    void static bind(pybind11::module& m);
};
}