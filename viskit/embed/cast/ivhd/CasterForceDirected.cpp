///
/// \author Bartosz Minch <minch@agh.edu.pl>
/// \date 18.03.2020
///

#include <viskit/embed/cast/ivhd/CasterForceDirected.h>
#include <cmath>

namespace viskit::embed::cast::ivhd
{
	CasterForceDirected::CasterForceDirected(const core::System& system)
		: CasterIVHD(system)
	{

	}

	void CasterForceDirected::castParticleSystem(particles::ParticleSystem& ps, Graph& graph)
	{
		auto energy = 1.0e10f;
        size_t interactions = 0;

        if (m_finalizing) {m_maxVelocity = 1000.0f;}

        calculatePositions(ps);
		calculateForces(energy, ps, graph, interactions);

        auto& forces = ps.calculationData()->m_force;
        auto& velocities = ps.calculationData()->m_vel;
        auto& awake = ps.calculationData()->m_alive;

        auto dt = 1e-3f * m_speedFactor * m_dtFactor;
        auto dt_half = dt * 0.5f;

        for (int i = 0; i < ps.countParticles(); i++)
        {
            if (awake[i])
            {
                velocities[i] += forces[i] * dt_half;
                velocities[i] *= m_velDump;
            }
        }

        ps.increaseStep();
	}

    glm::vec4 CasterForceDirected::force_2D(particles::ParticleSystem& ps, Neighbors neighbor, float &energy)
    {
        auto& pos = ps.calculationData()->m_pos;

        const auto pi = neighbor.i;
        const auto pj = neighbor.j;

        glm::vec4 posI = pos[pi];
        glm::vec4 posJ = pos[pj];

        const auto rv = posJ - posI;
        const auto r = glm::distance(glm::vec2(pos[pi].x, pos[pi].y), glm::vec2(pos[pj].x, pos[pj].y));

        auto D = neighbor.r;

        if (neighbor.type == NeighborsType::Near) { D *= 0; }

        energy = r == 0 ? 0 : (2.0f / r) * (r - D);

        return glm::vec4{ rv.x * energy, rv.y * energy, 0.0f, 0.0f };
    }

    void CasterForceDirected::calculateForces(float& energy, particles::ParticleSystem& ps, Graph& graph, size_t& interactions)
    {
        ps.resetForces();

        energy = 0;
        auto de = 0.1f;
        interactions = 0;

        auto& forces = ps.calculationData()->m_force;

        for (size_t index = 0; index < graph.size(); index++)
        {
            if (auto neighbors = graph.getNeighbors(index))
            {
                for (const auto neighbor : *neighbors)
                {
                    interactions++;
                    auto df = force_2D(ps, neighbor, de);

                    switch (neighbor.type)
                    {
                        case NeighborsType::Random: df *= w_random;
                        case NeighborsType::Near: df *= w_near;
                        default:;
                    }

                    energy += de*de;

                    forces[neighbor.i] += df;
                    forces[neighbor.j] -= df;
                }
            }
        }

        if (interactions)
            energy /= interactions;
    }

	void CasterForceDirected::calculatePositions(particles::ParticleSystem& ps)
	{
        auto& awake = ps.calculationData()->m_alive;
        auto& forces = ps.calculationData()->m_force;
        auto& velocities = ps.calculationData()->m_vel;
        auto& positions = ps.calculationData()->m_pos;

        float vl;
        auto dt = 1e-3f * m_speedFactor * m_dtFactor;
        auto dt_half = dt * 0.5f;
        auto avgVelocity = 0.0f;
        auto mv2 = 0.0f;

        if (ps.step() > 0)
        {
            for (size_t i = 0; i < ps.countParticles(); i++)
            {
                if (awake[i])
                {
                    velocities[i] += forces[i] * dt_half;
                    vl = velocities[i].x * velocities[i].x + velocities[i].y * velocities[i].y;

                    if (vl > mv2) mv2 = vl;

                    if (vl > m_maxVelocity*m_maxVelocity)
                    {
                        velocities[i] *= m_maxVelocity/std::sqrt(vl);
                        vl = m_maxVelocity*m_maxVelocity;
                    }

                    avgVelocity += vl;
                    positions[i] += velocities[i] * dt;
                }
            }
            avgVelocity /= static_cast<float>(ps.countAwakeParticles() - 1);
        }

        avgVelocity = std::sqrt(avgVelocity);
        m_currentMaxVelocity[m_currentMaxVelocity_ptr] = sqrt(mv2);
        m_currentMaxVelocity_ptr = (m_currentMaxVelocity_ptr + 1) % MAX_VELOCITY_BUFFER_LEN;

        if (ps.step()  > MAX_VELOCITY_BUFFER_LEN)
        {
            v_max = m_currentMaxVelocity[0];
            for (int i = 1; i < MAX_VELOCITY_BUFFER_LEN; i++)
                v_max += m_currentMaxVelocity[i];
            v_max /= MAX_VELOCITY_BUFFER_LEN;
        }
        else
            v_max = 0;

        if (m_autoAdaptStep)
        {
            if (v_max > 10 * avgVelocity)
            {
                m_dtFactor /= 1.01f;
            }
            else if (v_max < 10 * avgVelocity)
            {
                m_dtFactor *= 1.01f;
            }
            if (m_dtFactor < 0.1f)
            {
                m_dtFactor = 0.1f;
            }
        }
	}
}
