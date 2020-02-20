#include "embed/cast/ivhd/CasterIVHD.h"

namespace ivhd::embed::cast
{
	CasterIVHD::CasterIVHD(core::System& system, particles::ParticleSystem& ps, Graph& graph)
		: Caster(system, ps, graph)
	{
	}

	void CasterIVHD::castParticle(size_t index)
	{
	}

	void CasterIVHD::castParticleSystem()
	{
		float energy = 0.1f;
		calculateForces(energy);
		calculatePositions();
	}

	void CasterIVHD::calculateForces(float& energy)
	{
		auto& pos = m_ext_particleSystem.calculationData()->m_pos;
		auto& forces = m_ext_particleSystem.calculationData()->m_force;

		m_ext_particleSystem.resetForces();
		
		for (auto index = 0; index < m_ext_graph.size(); index++)
		{
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

	void CasterIVHD::calculatePositions()
	{
		
	}
}
