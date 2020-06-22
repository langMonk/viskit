#include "embed/cast/ivhd/CasterMomentum.h"

namespace viskit::embed::cast::ivhd
{
	CasterMomentum::CasterMomentum(core::System& system)
		: CasterIVHD(system)
	{
		
	}

	void CasterMomentum::calculatePositions(particles::ParticleSystem& ps)
	{
		auto& awake = ps.calculationData()->m_alive;
		auto& forces = ps.calculationData()->m_force;
		auto& velocities = ps.calculationData()->m_vel;
		auto& positions = ps.calculationData()->m_pos;

		for (size_t i = 0; i < ps.countParticles(); i++)
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
