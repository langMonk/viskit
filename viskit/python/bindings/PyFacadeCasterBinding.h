//
// \author Dawid Dębowski <ddebowsk@student.agh.edu.pl>
// \date 22.05.2022.
//

#pragma once

#include "viskit/facade/FacadeCaster.h"
#include <pybind11/pybind11.h>

namespace viskit::python::bindings
{
    class PyFacadeCasterBinding : public viskit::facade::FacadeCaster {
    public:
        using FacadeCaster::FacadeCaster;

        void calculatePositions(viskit::IParticleSystem &ps) override;

        void calculateForces(viskit::IParticleSystem &ps, viskit::IGraph &graph) override;

        viskit::CasterType type() override;

        viskit::OptimizerType optimizerType() override;

        void initialize(viskit::IParticleSystem &ps, viskit::IGraph &graph) override;

        void finalize() override;

        void step(viskit::IParticleSystem &ps, viskit::IGraph &graph) override;

        void static bind(pybind11::module &m);
    };
}