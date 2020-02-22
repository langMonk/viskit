#include "embed/cast/ivhd/CasterIVHD.h"

namespace ivhd::embed::cast
{
	CasterIVHD::CasterIVHD(core::System& system)
		: Caster(system)
	{
	}

	void CasterIVHD::castParticleSystem(particles::ParticleSystem& ps, graph::Graph& graph)
	{
		float energy = 0.1f;
		calculateForces(energy, ps, graph);
		calculatePositions(ps);
	}

	void CasterIVHD::calculateForces(float& energy, particles::ParticleSystem& ps, graph::Graph& graph)
	{
		auto& pos = ps.calculationData()->m_pos;
		auto& forces = ps.calculationData()->m_force;

		ps.resetForces();
		
		for (auto index = 0; index < graph.size(); index++)
		{
			if (auto neighbors = graph.getNeighbors(index))
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
}
