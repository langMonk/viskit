///
/// \author tomsia
/// \date 27.05.2021
///


#pragma once

#include <viskit/facade/FacadeCaster.h>
#include <viskit/embed/cast/CasterLargeVis.h>

namespace viskit::facade
{
    /// <summary>
    /// Implementation of ICaster interface.
    /// </summary>
    class FacadeCasterLargeVis: public FacadeCaster
    {
        // public construction and destruction methods
    public:

        explicit FacadeCasterLargeVis(const std::shared_ptr<core::Core>& core);
        ~FacadeCasterLargeVis() = default;

        FacadeCasterLargeVis(const FacadeCasterLargeVis&) = delete;
        FacadeCasterLargeVis(FacadeCasterLargeVis&&) = delete;

        FacadeCasterLargeVis& operator=(const FacadeCasterLargeVis&) = delete;
        FacadeCasterLargeVis& operator=(FacadeCasterLargeVis&&) = delete;

        // public methods
    public:
        void calculatePositions(IParticleSystem& ps) override;

        void calculateForces(IParticleSystem& ps, IGraph& graph) {};

        void initialize(viskit::IParticleSystem& ps, viskit::IGraph& graph) override;

        CasterType type() override { return CasterType::LargeVis; }

        OptimizerType optimizerType() override { return OptimizerType::None; }
    };
}
