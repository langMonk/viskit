///
/// \author Bartosz Minch <minch@agh.edu.pl>
/// \date 19.02.2020
///

#include <viskit/embed/cast/ivhd/CasterSGD.h>
#include <viskit/utils/Math.h>

namespace viskit::embed::cast::ivhd {
    CasterSGD::CasterSGD(const core::System &system)
            : CasterIVHD(system) {
    }

    void CasterSGD::castParticleSystem(particles::ParticleSystem &ps, Graph &graph) {
        std::vector<size_t> ids(graph.size());
        std::iota(ids.begin(), ids.end(), 1);
        std::shuffle(ids.begin(), ids.end(), rng);
        while (ids.size() > n) {
            subset.clear();
            subset = std::vector(ids.begin(), ids.begin() + n);
            ids.erase(ids.begin(), ids.begin() + n);

            auto energy = 0.1f;
            size_t interactions = 0;
            calculateForces(energy, ps, graph, interactions);
            calculatePositions(ps);
        }
    }

    void CasterSGD::calculatePositions(particles::ParticleSystem &ps) {
        auto &forces = ps.calculationData()->m_force;
        auto &positions = ps.calculationData()->m_pos;

        for (size_t i = 0; i < ps.countParticles(); i++) {
            positions[i] += forces[i] * a_factor;
        }

        ps.increaseStep();
    }

    void CasterSGD::calculateForces(float &energy, particles::ParticleSystem &ps, Graph &graph, size_t &interactions) {
        auto &pos = ps.calculationData()->m_pos;
        auto &forces = ps.calculationData()->m_force;
        ps.resetForces();
        for (size_t index: subset) {
            if (auto neighbors = graph.getNeighbors(index)) {
                for (const auto neighbor: *neighbors) {
                    const auto pi = neighbor.i;
                    const auto pj = neighbor.j;

                    glm::vec4 posI = pos[pi];
                    glm::vec4 posJ = pos[pj];

                    const auto rv = posI - posJ;
                    const auto r =
                            glm::distance(glm::vec2(pos[pi].x, pos[pi].y), glm::vec2(pos[pj].x, pos[pj].y)) + 0.00001f;

                    auto D = neighbor.r;

                    if (neighbor.type == NeighborsType::Near) {
                        D *= 0;
                    }

                    if (m_finalizing) {
                        energy = -0.005f / r;
                    } else {
                        energy = (D - r) / r;
                    }

                    if (neighbor.type != NeighborsType::Near) {
                        energy *= w_random;
                    }
                    auto df = glm::vec4{rv.x * energy, rv.y * energy, 0.0f, 0.0f};

                    forces[neighbor.i] += df;
                    forces[neighbor.j] -= df;
                }
            }
        }
    }
}
