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
		m_ext_system.logger().logInfo("[Caster IVHD ForceDirected] Casting particle system...");

		auto& awake = m_ext_particleSystem.calculationData()->m_alive;
		auto& forces = m_ext_particleSystem.calculationData()->m_force;
		auto& velocities = m_ext_particleSystem.calculationData()->m_vel;
		auto& positions = m_ext_particleSystem.calculationData()->m_pos;

		m_ext_particleSystem.resetForces();

		float de;
		for (auto i = 0; i < m_ext_graph.size(); i++)
		{
			calculateForces(i, de);
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

	void CasterForceDirected::calculateForces(size_t index, float& energy) const
	{
		auto& pos = m_ext_particleSystem.calculationData()->m_pos;
		auto& forces = m_ext_particleSystem.calculationData()->m_force;

		if (auto neighbors = m_ext_graph.getNeighbors(index))
		{
			for (const auto neighbor : *neighbors)
			{
				const auto pi = neighbor.i;
				const auto pj = neighbor.j;


				const auto rv = pos[pi] - pos[pj];
				const auto r = glm::distance(glm::vec2(pos[pi].x, pos[pi].y), glm::vec2(pos[pj].x, pos[pj].y)) + 0.00001f;

				auto D = neighbor.r;

				if (neighbor.type == NeighborsType::Near || neighbor.type == NeighborsType::Reverse) D *= 0;

				energy = (D - r) / r;

				auto df = glm::vec4{ rv.x * energy, rv.y * energy, 0.0f, 0.0f };

				switch(neighbor.type)
				{
					case NeighborsType::Random: df *= w_random;
					default: ;
				}

				forces[pi] += df;
				forces[pj] -= df;
			}
		}
	}
}
