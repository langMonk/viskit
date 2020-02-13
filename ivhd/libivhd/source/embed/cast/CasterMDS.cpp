#include "embed/cast/CasterMDS.h"

namespace ivhd::embed::cast
{
	CasterMDS::CasterMDS(core::System& system, graph::Graph& graph)
		: Caster(system)
		, m_graph(graph)
	{
	}

	glm::vec4 CasterMDS::calculateForces(long pair_indx, long pi, long pj, float& energy, particles::ParticleSystem& ps)
	{
		auto pos = ps.calculationData()->m_pos;
		glm::vec4 rv = pos[pi] - pos[pj];

		float r = ps.vectorDistance(pi, pj);

		auto element = m_graph.getNeighbors(pair_indx);

		float D = element.r;

		if (element.type == NeighborsType::Near)
			D *= 0;
		else if (element.type == NeighborsType::Reverse)
			D *= 0;
		else if (element.type == NeighborsType::Far)
			D *= 1;

		// kmD^w factor...
		float mkDw = m_sammonParameters.k * m_sammonParameters.m * std::pow(D, -m_sammonParameters.w);

		// r^(k-2) factor...
		float rk2 = std::pow(r, m_sammonParameters.k - 2);

		// (r^k-D^k)^(m-1) factor...
		float rk = std::pow(r, m_sammonParameters.k);
		float Dk = std::pow(D, m_sammonParameters.k);
		float rdm = std::pow(rk - Dk, m_sammonParameters.m - 1);
		if (m_sammonParameters.m % 2 && rk < Dk)
			rdm *= -1;

		energy = mkDw * rk2 * rdm;
		return rv * (-energy);
	}

	void CasterMDS::cast(particles::ParticleSystem& ps)
	{
		float dt = 1e-3 * speedFactor * dtFactor;
		float dtHalf = dt * 0.5;

		//-------------------------------------------------------------
		// update velocities and positions
		//-------------------------------------------------------------

		float vl;
		float avg_velocity = 0;
		int cnt = 0;
		float mv2 = 0;

		auto velocities = ps.calculationData()->m_vel;
		auto forces = ps.calculationData()->m_force;
		auto positions = ps.calculationData()->m_pos;

		
		for (int i = 0; i < ps.countAwakeParticles(); i++)
		{
			velocities[i] += forces[i] * dtHalf;

			vl = velocities[i].length();
			if (vl > mv2) mv2 = vl;

			if (vl > maxVelocity * maxVelocity)
			{
				velocities[i] *= maxVelocity / std::sqrt(vl);
				vl = maxVelocity * maxVelocity;
			}

			avg_velocity += vl;
			cnt++;

			positions[i] = velocities[i] * dt;

		}

		avg_velocity /= cnt;
		

		avg_velocity = sqrt(avg_velocity);

		//-------------------------------------------------------------
		// calculate forces
		//-------------------------------------------------------------

		long pi, pj;
		float de;
		for (int i = 0; i < m_graph.neighborsCount(); i++)
		{
			auto element = m_graph.getNeighbors(i);
			pi = element.i;
			pj = element.j;

			auto awake = ps.calculationData()->m_alive;

			if (awake[pi] && awake[pj])
			{
				glm::vec4 df = calculateForces(i, pi, pj, de, ps);

				bool reversed = false;
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

		for (int i = 0; i < ps.countAwakeParticles(); i++)
		{
			velocities[i] += forces[i] * dtHalf;
			velocities[i] *= dumpVelocity;
		}
	}
}