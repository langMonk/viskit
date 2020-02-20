#include "embed/cast/ivhd/CasterNesterov.h"

namespace ivhd::embed::cast::ivhd
{
	CasterNesterov::CasterNesterov(core::System& system, particles::ParticleSystem& ps)
		: CasterIVHD(system, ps, ps.neighbourhoodGraph())
	{

	}

	void CasterNesterov::calculateForces(float& energy)
	{
		auto& pos = m_ext_particleSystem.calculationData()->m_pos;
		auto& forces = m_ext_particleSystem.calculationData()->m_force;
		auto& velocities = m_ext_particleSystem.calculationData()->m_vel;

		m_ext_particleSystem.resetForces();

		for (auto index = 0; index < m_ext_graph.size(); index++)
		{
			if (auto neighbors = m_ext_graph.getNeighbors(index))
			{
				for (const auto neighbor : *neighbors)
				{

					const auto pi = neighbor.i;
					const auto pj = neighbor.j;

					glm::vec4 posI = pos[pi];
					glm::vec4 posJ = pos[pj];

					// estimate next positions with previous velocity
					posI.x += velocities[pi].x;
					posI.y += velocities[pi].y;
					posJ.x += velocities[pj].x;
					posJ.y += velocities[pj].y;
					
					const auto rv = posI - posJ;
					const auto r = glm::distance(glm::vec2(posI.x, posI.y), glm::vec2(posJ.x, posJ.y)) + 0.00001f;

					auto D = neighbor.r;

					if (neighbor.type == NeighborsType::Near || neighbor.type == NeighborsType::Reverse) D *= 0;

					energy = (D - r) / r;

					auto df = glm::vec4{ rv.x * energy, rv.y * energy, 0.0f, 0.0f };
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
	}
	
	void CasterNesterov::calculatePositions()
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
