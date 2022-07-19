///
/// \author Bartosz Minch <minch@agh.edu.pl>
/// \date 18.03.2020
///

#pragma once

#include <viskit/embed/cast/ivhd/CasterIVHD.h>
#include <viskit/particles/ParticleSystem.h>

const int MAX_VELOCITY_BUFFER_LEN = 10;

namespace viskit::embed::cast::ivhd {
class CasterForceDirected final : public CasterIVHD {
    // public construction and destruction methods
public:
    explicit CasterForceDirected(const core::System& system);

    // public methods
public:
    void castParticleSystem(particles::ParticleSystem& ps, Graph& graph) override;

    void calculatePositions(particles::ParticleSystem& ps) override;

    void calculateForces(float& energy, particles::ParticleSystem& ps, Graph& graph, size_t& interactions) override;

private:
    glm::vec4 force_2D(particles::ParticleSystem& ps, Neighbors neighbor, float& energy);

private:
    float m_currentMaxVelocity[MAX_VELOCITY_BUFFER_LEN] {};

    float m_speedFactor { 100.0f };

    float m_dtFactor { 1.0f };

    float m_maxVelocity { 1.0f };

    float m_velDump { 0.95f };

    int m_currentMaxVelocity_ptr { 0 };

    bool m_autoAdaptStep { false };

    int m_sammonK { 1 };

    int m_sammonM { 2 };

    int m_sammonW { 0 };

    float v_max {};
};
}
