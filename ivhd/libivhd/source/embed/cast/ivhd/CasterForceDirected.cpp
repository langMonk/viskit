#include "embed/cast/ivhd/CasterForceDirected.h"

namespace ivhd::embed::cast::ivhd
{
	CasterForceDirected::CasterForceDirected(core::System& system)
		: CasterIVHD(system)
	{
		
	}

	void CasterForceDirected::calculatePositions(particles::ParticleSystem& ps)
	{
		auto& awake = ps.calculationData()->m_alive;
		auto& forces = ps.calculationData()->m_force;
		auto& velocities = ps.calculationData()->m_vel;
		auto& positions = ps.calculationData()->m_pos;

		for (auto i = 0; i < ps.countParticles(); i++)
		{
			if (awake[i])
			{
				velocities[i] = velocities[i] * a_factor + forces[i] * b_factor;
				positions[i] += velocities[i];
			}
		}

		ps.increaseStep();
	}
}
