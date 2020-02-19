#include "embed/cast/ivhd/CasterForceDirected.h"

namespace ivhd::embed::cast::ivhd
{
	CasterForceDirected::CasterForceDirected(core::System& system, particles::ParticleSystem& ps)
		: Caster(system, ps)
		, m_ext_graph(ps.neighbourhoodGraph())
	{
		
	}

	void CasterForceDirected::castParticle(size_t index)
	{
	}

	void CasterForceDirected::castParticleSystem()
	{
		m_ext_system.logger().logInfo("[Caster AB] Casting particle system...");

		auto& awake = m_ext_particleSystem.calculationData()->m_alive;
		auto& forces = m_ext_particleSystem.calculationData()->m_force;
		auto& velocities = m_ext_particleSystem.calculationData()->m_vel;
		auto& positions = m_ext_particleSystem.calculationData()->m_pos;
			
		m_ext_particleSystem.resetForces();

		float de;
		for (int i = 0; i < m_ext_graph.size(); i++)
		{
			if (const auto neighbors = m_ext_graph.getNeighbors(i))
			{
				for (const auto element : *neighbors)
				{
					const auto pi = element.i;
					const auto pj = element.j;
					const auto r = element.r;
					const auto type = element.type;

					if (awake[pi] && awake[pj])
					{
						auto df = calculateForces(i, pi, pj, r, type, de);

						if (element.type == NeighborsType::Random)
						{
							df *= w_random;
						}

						{
							forces[pi] += df;
							forces[pj] -= df;
						}
					}
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


	glm::vec4 CasterForceDirected::calculateForces(size_t pairIndex, size_t pi, size_t pj, float r_element, NeighborsType type, float& energy) const
	{
		auto& pos = m_ext_particleSystem.calculationData()->m_pos;

		const auto pipos = glm::vec2(pos[pi].x, pos[pi].y);
		const auto pjpos = glm::vec2(pos[pj].x, pos[pj].y);
		const auto rv = pipos - pjpos;

		const auto r = glm::distance(pipos, pjpos) + 0.00001f;

		auto D = r_element;

		if (type == NeighborsType::Near)
			D *= 0;

		energy = (D - r) / r;
		
		return glm::vec4{ rv.x * energy, rv.y * energy, 0.0f, 0.0f };
	}
}
