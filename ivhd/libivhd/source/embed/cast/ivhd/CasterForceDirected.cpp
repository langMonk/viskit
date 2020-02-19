#include "embed/cast/ivhd/CasterForceDirected.h"

namespace ivhd::embed::cast::ivhd
{
	CasterForceDirected::CasterForceDirected(core::System& system, particles::ParticleSystem& ps)
		: CasterIVHD(system, ps, ps.neighbourhoodGraph())
	{
		
	}

	void CasterForceDirected::castParticle(size_t index)
	{
	}

	void CasterForceDirected::castParticleSystem()
	{
		m_ext_system.logger().logInfo("[Caster IVHD ForceDirected] Casting particle system...");

		auto& awake = m_ext_particleSystem.calculationData()->m_alive;
		auto& forces = m_ext_particleSystem.calculationData()->m_force;
		auto& velocities = m_ext_particleSystem.calculationData()->m_vel;
		auto& positions = m_ext_particleSystem.calculationData()->m_pos;

		m_ext_particleSystem.resetForces();

		float de;
		for (auto index = 0; index < m_ext_graph.size(); index++)
		{
			if (auto neighbors = m_ext_graph.getNeighbors(index))
			{
				for (const auto neighbor : *neighbors)
				{
					auto df = calculateForces(neighbor, de);

					switch (neighbor.type)
					{
						case NeighborsType::Random: df *= w_random;
						default:;
					}

					forces[neighbor.i] += df;
					forces[neighbor.j] -= df;
				}
			}
		}

		for (auto i = 0; i < m_ext_particleSystem.countParticles(); i++)
		{
			if (awake[i])
			{
				velocities[i] = velocities[i] * a_factor + forces[i] * b_factor;
				positions[i] += velocities[i];
			}
		}

		m_ext_particleSystem.increaseStep();
		m_ext_system.logger().logInfo("[Caster IVHD ForceDirected] Finished.");
	}
}
