///
/// \author Bartosz Minch <minch@agh.edu.pl>
/// \date 18.03.2020
///

#pragma once

#include <viskit/embed/cast/ivhd/CasterForceDirected.h>
#include <viskit/facade/FacadeCaster.h>

namespace viskit::facade {
/// <summary>
/// Implementation of ICaster interface.
/// </summary>
class FacadeCasterForceDirected : public FacadeCaster {
    // public construction and destruction methods
public:
    explicit FacadeCasterForceDirected(const std::shared_ptr<core::Core>& core);
    ~FacadeCasterForceDirected() override = default;

    FacadeCasterForceDirected(const FacadeCasterForceDirected&) = delete;
    FacadeCasterForceDirected(FacadeCasterForceDirected&&) = delete;

    FacadeCasterForceDirected& operator=(const FacadeCasterForceDirected&) = delete;
    FacadeCasterForceDirected& operator=(FacadeCasterForceDirected&&) = delete;

    // public methods
public:
    void calculatePositions(IParticleSystem& ps) override;

    void calculateForces(IParticleSystem& ps, IGraph& graph) override;

    void finalize() override;

    CasterType type() override { return CasterType::IVHD; }

    OptimizerType optimizerType() override { return OptimizerType::ForceDirected; }
};
}