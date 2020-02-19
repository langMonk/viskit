#include "embed/cast/CasterMDS.h"

namespace ivhd::embed::cast::ivhd
{
	CasterMDS::CasterMDS(core::System& system, particles::ParticleSystem& ps)
		: Caster(system, ps)
		, m_ext_graph(ps.neighbourhoodGraph())
	{
	}

	void CasterMDS::castParticle(size_t index)
	{
	}

	glm::vec4 CasterMDS::calculateForces(size_t pairIndex, size_t pi, size_t pj, float& energy) const
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

		if (m_sammonParameters.k == 1 && m_sammonParameters.m == 2 && m_sammonParameters.w == 0)
		{ 
			energy = r == 0 ? 0 : (2.0 / r) * (r - D);
		}
		else
		{ 
			const auto mkDw = m_sammonParameters.k * m_sammonParameters.m * std::pow(D, -m_sammonParameters.w);
			const auto rk2 = std::pow(r, m_sammonParameters.k - 2);

			const auto rk = std::pow(r, m_sammonParameters.k);
			const auto Dk = std::pow(D, m_sammonParameters.k);
			auto rdm = std::pow(rk - Dk, m_sammonParameters.m - 1);
			if (m_sammonParameters.m % 2 && rk < Dk)
				rdm *= -1;

			energy = mkDw * rk2 * rdm;
		}

		const auto rv2 = glm::vec4{ rv.x, rv.y, 0.0f, 0.0f };
		return rv2 * (-energy);
	}

	void CasterMDS::castParticleSystem()
	{
		m_ext_system.logger().logInfo("[CasterMDS] Casting particle system...");
		
		const float dt = 1e-3f * speedFactor * dtFactor;
		const float dtHalf = 0.5f * dt;

		//-------------------------------------------------------------
		// update velocities and positions
		//-------------------------------------------------------------

		float avg_velocity = 0;
		auto cnt = 0;
		auto mv2 = 0.0f;

		auto& velocities = m_ext_particleSystem.calculationData()->m_vel;
		auto& forces = m_ext_particleSystem.calculationData()->m_force;
		auto& positions = m_ext_particleSystem.calculationData()->m_pos;


		if(m_ext_particleSystem.step() > 0)
		{
			for (auto i = 0; i < m_ext_particleSystem.countAwakeParticles(); i++)
			{
				velocities[i] += forces[i] * dtHalf;

				auto vl = glm::dot(velocities[i], velocities[i]);
				
				if (vl > mv2) mv2 = vl;

				if (vl > maxVelocity * maxVelocity)
				{
					velocities[i] *= maxVelocity / std::sqrt(vl);
					vl = maxVelocity * maxVelocity;
				}

				avg_velocity += vl;
				cnt++;

				positions[i] += velocities[i] * dt;
			}
		}
		
		avg_velocity /= cnt;
		avg_velocity = std::sqrt(avg_velocity);

		m_ext_particleSystem.resetForces();
		
		//-------------------------------------------------------------
		// calculate forces
		//-------------------------------------------------------------

		auto& awake = m_ext_particleSystem.calculationData()->m_alive;

		float de = 0.1f;
		for (auto i = 0; i < m_ext_graph.neighborsCount(); i++)
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
			/*	else if (element.type == NeighborsType::Reversed && m_graphGenerator->name == "rkNN")
				{
					reversed = true;
					df *= w_reversed;
				}*/
				else
				{
					df *= m_distanceKernelParameters.far;
				}

				forces[pi] += df;
				forces[pj] -= df;

			}
		}

		//-------------------------------------------------------------
		// update velocities
		//-------------------------------------------------------------

		for (auto i = 0; i < m_ext_particleSystem.countAwakeParticles(); i++)
		{
			velocities[i] += forces[i] * dtHalf;
			velocities[i] *= dumpVelocity;
		}

		m_ext_particleSystem.increaseStep();
		m_ext_system.logger().logInfo("[CasterMDS] Step finished.");
	}
}