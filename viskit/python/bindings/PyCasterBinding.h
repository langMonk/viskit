//
// Created by Bartosz Minch on 02/05/2022.
//

#pragma once

#include "viskit/viskit/ICaster.h"

namespace viskit::python::bindings {
class PyCasterBinding : public ICaster {
public:
    using ICaster::ICaster;

    void calculatePositions(viskit::IParticleSystem& ps) override;

    void calculateForces(viskit::IParticleSystem& ps, viskit::IGraph& graph) override;

    viskit::CasterType type() override;

    viskit::OptimizerType optimizerType() override;

    void initialize(viskit::IParticleSystem& ps, viskit::IGraph& graph) override;

    void finalize() override;

    void step(viskit::IParticleSystem& ps, viskit::IGraph& graph) override;

    void static bind(pybind11::module& m);
};
}