///
/// \author Bartosz Minch <minch@agh.edu.pl> 
/// \date 17.06.2020
///

#pragma once

#include <memory>
#include <viskit/viskit/IMetric.h>
#include <viskit/core/Core.h>
#include <viskit/graph/Graph.h>
#include <viskit/particles/ParticleSystem.h>

namespace viskit::facade::metrics
{
    class FacadeKnnMetric : public IMetric
    {
    public:
        explicit FacadeKnnMetric(std::shared_ptr<core::Core>  core);

        float calculate(viskit::IParticleSystem& ps, int k) override;

    private:
        graph::Graph buildInternalGraph(viskit::particles::ParticleSystem& ps, int k);

    private:
        std::shared_ptr<core::Core> m_ext_core;
    };
}