#include "embed/cast/ivhd/CasterIVHD.h"

namespace ivhd::embed::cast
{
	CasterIVHD::CasterIVHD(core::System& system, particles::ParticleSystem& ps, Graph& graph)
		: Caster(system, ps, graph)
	{
	}

	glm::vec4 CasterIVHD::calculateForces(Neighbors neighbors, float& energy) const
	{
		auto& pos = m_ext_particleSystem.calculationData()->m_pos;
		auto& forces = m_ext_particleSystem.calculationData()->m_force;

		const auto pi = neighbors.i;
		const auto pj = neighbors.j;

		const auto rv = pos[pi] - pos[pj];
		const auto r = glm::distance(glm::vec2(pos[pi].x, pos[pi].y), glm::vec2(pos[pj].x, pos[pj].y)) + 0.00001f;

		auto D = neighbors.r;

		if (neighbors.type == NeighborsType::Near || neighbors.type == NeighborsType::Reverse) D *= 0;

		energy = (D - r) / r;

		return glm::vec4{ rv.x * energy, rv.y * energy, 0.0f, 0.0f };
		
	}
}
