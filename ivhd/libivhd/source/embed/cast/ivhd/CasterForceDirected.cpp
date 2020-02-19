#include "embed/cast/ivhd/CasterForceDirected.h"

namespace ivhd::embed::cast::ivhd
{
	CasterAB::CasterAB(core::System& system, particles::ParticleSystem& ps)
		: Caster(system, ps)
		, m_ext_graph(ps.neighbourhoodGraph())
	{
		
	}

	void CasterAB::castParticle(size_t index)
	{
	}

	void CasterAB::castParticleSystem()
	{
		m_ext_system.logger().logInfo("[Caster AB] Casting particle system...");

		auto& awake = m_ext_particleSystem.calculationData()->m_alive;
		auto& forces = m_ext_particleSystem.calculationData()->m_force;
		auto& velocities = m_ext_particleSystem.calculationData()->m_vel;
		auto& positions = m_ext_particleSystem.calculationData()->m_pos;

		m_ext_particleSystem.resetForces();
		
		float de;
		for (int i = 0; i < m_ext_graph.neighborsCount(); i++)
		{
			const auto element = m_ext_graph.getNeighbors(i);
			const size_t pi = element.i;
			const size_t pj = element.j;

			if (awake[pi] && awake[pj])
			{
				auto df = calculateForces(i, pi, pj, de);

				if (element.type == NeighborsType::Near)
				{
					df *= m_distanceKernelParameters.near;
				}
				else if (element.type == NeighborsType::Random)
				{
					df *= m_distanceKernelParameters.random;
				}
				else
				{
					df *= m_distanceKernelParameters.far;
				}

				{
					forces[pi] += df;
					forces[pj] -= df;
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
		m_ext_system.logger().logInfo("[CasterAB] Finished.");
	}

	glm::vec4 CasterAB::calculateForces(size_t pairIndex, size_t pi, size_t pj, float& energy) const
	{
		auto& pos = m_ext_particleSystem.calculationData()->m_pos;

		const auto rv = glm::vec2(pos[pi].x, pos[pi].y) - glm::vec2(pos[pj].x, pos[pj].y);
		const auto r = glm::distance(glm::vec2(pos[pi].x, pos[pi].y), glm::vec2(pos[pj].x, pos[pj].y)) + 0.00001f;

		const auto element = m_ext_graph.getNeighbors(pairIndex);
		auto D = element.r;

		if (element.type == NeighborsType::Near || element.type == NeighborsType::Reverse) D *= 0;

		energy = (D-r)/r;

		return glm::vec4{ rv.x*energy, rv.y*energy, 0.0f, 0.0f };
	}
}
