///
/// \author Bartosz Minch <minch@agh.edu.pl>
/// \date 19.02.2020
///

#include <viskit/embed/cast/ivhd/CasterNesterov.h>

namespace viskit::embed::cast::ivhd {
CasterNesterov::CasterNesterov(const core::System& system)
    : CasterIVHD(system)
{
}

void CasterNesterov::calculateForces(float& energy, particles::ParticleSystem& ps, graph::Graph& graph, size_t& interactions)
{
    auto& pos = ps.calculationData()->m_pos;
    auto& forces = ps.calculationData()->m_force;
    auto& velocities = ps.calculationData()->m_vel;

    ps.resetForces();

    for (size_t index = 0; index < graph.size(); index++) {
        if (auto neighbors = graph.getNeighbors(index)) {
            for (const auto neighbor : *neighbors) {
                interactions++;

                const auto pi = neighbor.i;
                const auto pj = neighbor.j;

                glm::vec4 posI = pos[pi];
                glm::vec4 posJ = pos[pj];

                // estimate next positions with previous velocity
                posI.x += velocities[pi].x;
                posI.y += velocities[pi].y;
                posJ.x += velocities[pj].x;
                posJ.y += velocities[pj].y;

                const auto rv = posI - posJ;
                const auto r = glm::distance(glm::vec2(posI.x, posI.y), glm::vec2(posJ.x, posJ.y)) + 0.00001f;

                auto D = neighbor.r;

                if (neighbor.type == NeighborsType::Near)
                    D *= 0;

                energy = (D - r) / r;

                auto df = glm::vec4 { rv.x * energy, rv.y * energy, 0.0f, 0.0f };
                switch (neighbor.type) {
                case NeighborsType::Random:
                    df *= w_random;
                default:;
                }

                forces[neighbor.i] += df;
                forces[neighbor.j] -= df;
            }
        }
    }
}

void CasterNesterov::calculatePositions(particles::ParticleSystem& ps)
{
    auto& awake = ps.calculationData()->m_alive;
    auto& forces = ps.calculationData()->m_force;
    auto& velocities = ps.calculationData()->m_vel;
    auto& positions = ps.calculationData()->m_pos;

    for (size_t i = 0; i < ps.countParticles(); i++) {
        if (awake[i]) {
            velocities[i] = velocities[i] * a_factor + forces[i] * b_factor;
            positions[i] += velocities[i];
        }
    }

    ps.increaseStep();
}
}
