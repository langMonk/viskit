#include "embed/cast/ivhd/CasterForceDirected.h"

namespace ivhd::embed::cast::ivhd
{
	CasterForceDirected::CasterForceDirected(core::System& system, particles::ParticleSystem& ps)
		: CasterIVHD(system, ps, ps.neighbourhoodGraph())
	{
		
	}

	void CasterForceDirected::calculatePositions()
	{
		auto& awake = m_ext_particleSystem.calculationData()->m_alive;
		auto& forces = m_ext_particleSystem.calculationData()->m_force;
		auto& velocities = m_ext_particleSystem.calculationData()->m_vel;
		auto& positions = m_ext_particleSystem.calculationData()->m_pos;

		for (auto i = 0; i < m_ext_particleSystem.countParticles(); i++)
		{
			if (awake[i])
			{
				velocities[i] = velocities[i] * a_factor + forces[i] * b_factor;
				positions[i] += velocities[i];
			}
		}

		m_ext_particleSystem.increaseStep();
	}
}
