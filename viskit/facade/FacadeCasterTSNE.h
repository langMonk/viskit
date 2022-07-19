
#pragma once

#include <viskit/embed/cast/CasterTSNE.h>
#include <viskit/facade/FacadeCaster.h>
#include <viskit/viskit/IParticleSystem.h>

namespace viskit::facade {
/// <summary>
/// Implementation of ICaster interface.
/// </summary>
class FacadeCasterTSNE : public FacadeCaster {
    // public construction and destruction methods
public:
    explicit FacadeCasterTSNE(const std::shared_ptr<core::Core>& core);

    ~FacadeCasterTSNE() = default;

    FacadeCasterTSNE(const FacadeCasterTSNE&) = delete;

    FacadeCasterTSNE(FacadeCasterTSNE&&) = delete;

    FacadeCasterTSNE& operator=(const FacadeCasterTSNE&) = delete;

    FacadeCasterTSNE& operator=(FacadeCasterTSNE&&) = delete;

    // public methods
public:
    void calculatePositions(IParticleSystem& ps) override;

    void calculateForces(IParticleSystem& ps, IGraph& graph) override {};

    void initialize(viskit::IParticleSystem& ps, viskit::IGraph& graph) override;

    CasterType type() override { return CasterType::tSNE; }

    OptimizerType optimizerType() override { return OptimizerType::None; }
};
}