#include "embed/cast/ivhd/CasterForceDirected.h"

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
	}

	void CasterForceDirected::calculatePositions(particles::ParticleSystem& ps)
	{
		auto& awake = ps.calculationData()->m_alive;
		auto& forces = ps.calculationData()->m_force;
		auto& velocities = ps.calculationData()->m_vel;
		auto& positions = ps.calculationData()->m_pos;

		if (ps.step() == 0)
		{
			for (auto i = 0; i < ps.countParticles(); i++)
			{
				velocities[i] = glm::vec4{ 0.0f };
			}
		}
		else
		{ 
			for (size_t i = 0; i < ps.countParticles(); i++)
			{
				if (awake[i])
				{
					velocities[i] = a_factor * velocities[i] + b_factor * forces[i];
					positions[i] += velocities[i] * m_speedFactor;
				}
			}
		}
		
		ps.increaseStep();
	}
}
