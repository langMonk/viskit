///
/// \author Bartosz Minch <minch@agh.edu.pl> 
/// \date 17.06.2020
///

#pragma once

#include <memory>

#include "viskit/IMetric.h"
#include "core/Core.h"
#include "graph/Graph.h"
#include "particles/ParticleSystem.h"

namespace viskit::facade::metrics
{
    class FacadeKnnMetric : public IMetric
    {
    public:
        explicit FacadeKnnMetric(const std::shared_ptr<core::Core>& core);

        float calculate(viskit::IParticleSystem& ps) override;

    private:
        graph::Graph buildInternalGraph(viskit::particles::ParticleSystem& ps);

    private:
        std::shared_ptr<core::Core> m_ext_core;
    };
}