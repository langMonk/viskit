///
/// \author Bartosz Minch <minch@agh.edu.pl>
/// \date 19.02.2020
///

#include <chrono>
#include <cmath>
#include <viskit/embed/cast/ivhd/CasterIVHD.h>

namespace viskit::embed::cast {
CasterIVHD::CasterIVHD(const core::System& system)
    : Caster(system)
{
}

void CasterIVHD::castParticleSystem(particles::ParticleSystem& ps, Graph& graph)
{
    auto energy = 0.1f;
    size_t interactions = 0;
    calculateForces(energy, ps, graph, interactions);
    calculatePositions(ps);
}

void CasterIVHD::calculateForces(float& energy, particles::ParticleSystem& ps, Graph& graph, size_t& interactions)
{
    auto& pos = ps.calculationData()->m_pos;
    auto& forces = ps.calculationData()->m_force;

    ps.resetForces();

    for (size_t index = 0; index < graph.size(); index++) {
        if (auto neighbors = graph.getNeighbors(index)) {
            for (const auto neighbor : *neighbors) {
                const auto pi = neighbor.i;
                const auto pj = neighbor.j;

                glm::vec4 posI = pos[pi];
                glm::vec4 posJ = pos[pj];

                const auto rv = posI - posJ;
                const auto r = glm::distance(glm::vec2(pos[pi].x, pos[pi].y), glm::vec2(pos[pj].x, pos[pj].y)) + 0.00001f;

                auto D = neighbor.r;

                if (neighbor.type == NeighborsType::Near) {
                    D *= 0;
                }

                if (m_finalizing) {
                    energy = -0.005f / r;
                } else {
                    energy = (D - r) / r;
                }

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
}
