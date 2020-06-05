#include "embed/cast/ivhd/CasterForceDirected.h"

namespace ivhd::embed::cast::ivhd
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
		const auto dt = 1e-3f * m_speedFactor * m_dtFactor;
		const auto dt_half = dt * 0.5f;

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
					velocities[i] = forces[i] * dt_half;
					positions[i] += velocities[i] * dt;
				}
			}
		}
		
		ps.increaseStep();
	}
}
