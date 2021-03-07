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
		auto energy = 0.1f;
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
        auto mv2 = 0.0f;

        if (ps.step() > 0)
        {
            for (size_t i = 0; i < ps.countParticles(); i++)
            {
                if (awake[i])
                {
                    velocities[i] = forces[i] * dt_half;
                    vl = velocities[i].x * velocities[i].x + velocities[i].y * velocities[i].y ;

                    if (vl > mv2) mv2 = vl;

                    if (vl > m_maxVelocity*m_maxVelocity)
                    {
                        velocities[i] *= m_maxVelocity/std::sqrt(vl);
                    }

                    positions[i].x += velocities[i].x * dt;
                    positions[i].y += velocities[i].y * dt;
                }
            }
        }

        if (m_autoAdaptStep)
        {
//            if (v_max > 10 * avg_velocity)
//            {
//                m_dtFactor /= 1.01f;
//            }
//            else if (v_max < 10*avg_velocity)
//            {
//                m_dtFactor *= 1.01f;
//            }
//            if (m_dtFactor < 0.1f)
//            {
//                m_dtFactor = 0.1f;
//            }
        }
		ps.increaseStep();
	}
}
