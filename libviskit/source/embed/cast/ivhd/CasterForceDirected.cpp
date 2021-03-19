#include "embed/cast/ivhd/CasterForceDirected.h"

#include <cmath>

namespace viskit::embed::cast::ivhd
{
	CasterForceDirected::CasterForceDirected(core::System& system)
		: CasterIVHD(system)
	{

	}

	void CasterForceDirected::castParticleSystem(particles::ParticleSystem& ps, Graph& graph)
	{
		auto energy = 1.0e10f;
		calculatePositions(ps);
		calculateForces(energy, ps, graph);

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

    void CasterForceDirected::calculateForces(float& energy, particles::ParticleSystem& ps, Graph& graph)
    {
        auto& pos = ps.calculationData()->m_pos;
        auto& forces = ps.calculationData()->m_force;
        energy = 0;
        auto de = 0.1f;
        ps.resetForces();

        for (size_t index = 0; index < graph.size(); index++)
        {
            if (auto neighbors = graph.getNeighbors(index))
            {
                for (const auto neighbor : *neighbors)
                {
                    const auto pi = neighbor.i;
                    const auto pj = neighbor.j;

                    glm::vec4 posI = pos[pi];
                    glm::vec4 posJ = pos[pj];

                    const auto rv = posJ - posI;
                    const auto r = glm::distance(glm::vec2(pos[pi].x, pos[pi].y), glm::vec2(pos[pj].x, pos[pj].y));

                    auto D = neighbor.r;

                    if (neighbor.type == NeighborsType::Near) { D *= 0; }


                    if (m_sammonK == 1 && m_sammonM == 2 && m_sammonW == 0)
                    {
                        energy = r == 0 ? 0 : (2.0f/r)*(r - D);
                    }
                    else
                    {
                        auto mkDw = m_sammonK*m_sammonM*std::pow(D, -m_sammonW);

                        auto rk2 = std::pow(r, m_sammonK - 2);

                        auto rk = std::pow(r, m_sammonK);
                        auto Dk = std::pow(D, m_sammonK);
                        auto rdm = std::pow(rk - Dk, m_sammonM - 1);

                        if (m_sammonM % 2 && rk < Dk)
                            rdm *= -1;

                        energy = static_cast<float>(mkDw*rk2*rdm);
                    }

                    auto df = glm::vec4{ rv.x * energy, rv.y * energy, 0.0f, 0.0f };

                    switch (neighbor.type)
                    {
                        case NeighborsType::Random: df *= w_random;
                        default:;
                    }

                    energy += de*de;

                    forces[neighbor.i] += df;
                    forces[neighbor.j] -= df;
                }
            }
        }
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
            auto aliveCnt = 0;
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
                    aliveCnt++;
                }
            }
            avgVelocity /= static_cast<float>(aliveCnt - 1);
        }

        avgVelocity = std::sqrt(avgVelocity);
        if (m_currentMaxVelocity < std::sqrt(mv2)) m_currentMaxVelocity = std::sqrt(mv2);

        if (ps.step() > 10)
        {
            v_max = m_currentMaxVelocity;
            for (int i = 1; i < 10; i++)
                v_max += m_currentMaxVelocity;
            v_max /= 10;
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
