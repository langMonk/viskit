///
/// \author Bartosz Minch <minch@agh.edu.pl>
/// \date 19.02.2020
///

#pragma once

#include <viskit/embed/cast/ivhd/CasterIVHD.h>
#include <viskit/particles/ParticleSystem.h>

namespace viskit::embed::cast::ivhd {
class CasterSGD final : public CasterIVHD {
    // public construction and destruction methods
public:
    explicit CasterSGD(const core::System& system);

    void castParticleSystem(particles::ParticleSystem& ps, Graph& graph) override;

    void calculatePositions(particles::ParticleSystem& ps) override;

    void calculateForces(float& energy, particles::ParticleSystem& ps, graph::Graph& graph,
        size_t& interactions) override;

    float a_factor { 0.07f };
    size_t n { 70 };

protected:
    float w_random { 0.001 };
    std::random_device rd = std::random_device {};
    std::default_random_engine rng = std::default_random_engine { rd() };
    std::vector<size_t> subset;
};
}
