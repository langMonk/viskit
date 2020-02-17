#include "embed/cast/CasterAB.h"

namespace ivhd::embed::cast
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
		
		if (m_ext_particleSystem.step() == 0)
		{
			m_ext_particleSystem.resetVelocities();
		}
		else
		{			
			for (auto i = 0; i < m_ext_particleSystem.countParticles(); i++)
				if (awake[i])
				{
					velocities[i] = velocities[i] * a_factor + forces[i] * b_factor;
					positions[i] += velocities[i];
				}
		}

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

		m_ext_particleSystem.increaseStep();
		m_ext_system.logger().logInfo("[CasterAB] Finished.");
	}

	glm::vec4 CasterAB::calculateForces(size_t pairIndex, size_t pi, size_t pj, float& energy) const
	{
		auto& pos = m_ext_particleSystem.calculationData()->m_pos;

		const auto pipos = glm::vec2(pos[pi].x, pos[pi].y);
		const auto pjpos = glm::vec2(pos[pj].x, pos[pj].y);
		const auto rv = pipos - pjpos;

		const auto r = glm::distance(pipos, pjpos);

		const auto element = m_ext_graph.getNeighbors(pairIndex);
		auto D = element.r;

		if (element.type == NeighborsType::Near)
			D *= 0;
		else if (element.type == NeighborsType::Reverse)
			D *= 0;
		else if (element.type == NeighborsType::Far)
			D *= 1;
		
		const auto mkDw = m_sammonParameters.k * m_sammonParameters.m * std::pow(D, -m_sammonParameters.w);
		const auto rk2 = std::pow(r, m_sammonParameters.k - 2);

		const auto rk = std::pow(r, m_sammonParameters.k);
		const auto Dk = std::pow(D, m_sammonParameters.k);
		auto rdm = std::pow(rk - Dk, m_sammonParameters.m - 1);
		
		if (m_sammonParameters.m % 2 && rk < Dk)
			rdm *= -1;

		energy = mkDw * rk2 * rdm;

		const auto rv2 = glm::vec4{ rv.x, rv.y, 0.0f, 0.0f };
		return rv2 * (-energy);
	}
}
