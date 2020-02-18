#include "embed/cast/CasterSGD.h"

namespace ivhd::embed::cast
{
	CasterSGD::CasterSGD(core::System& system, particles::ParticleSystem& ps)
		: Caster(system, ps)
		, m_randomCaster(system, ps)
		, m_ext_graph(ps.neighbourhoodGraph())
	{
		
	}

	void CasterSGD::castParticle(size_t index)
	{
	}

	void CasterSGD::castParticleSystem()
	{
		auto& positions = m_ext_particleSystem.calculationData()->m_pos;
		auto& velocities = m_ext_particleSystem.calculationData()->m_vel;
		auto& forces = m_ext_particleSystem.calculationData()->m_force;
		
		float lenPK;

		initPos();
		
		auto& awake = m_ext_particleSystem.calculationData()->m_alive;

		if (m_ext_particleSystem.step() == 0)
		{
			m_ext_particleSystem.resetVelocities();
			m_ext_particleSystem.resetForces();
		}
		
		for (auto i = 0; i < m_ext_graph.neighborsCount(); i++)
		{
			const auto element = m_ext_graph.getNeighbors(i);
			const size_t pi = element.i;
			const size_t pj = element.j;

			if (awake[pi] && awake[pj])
			{
				if (element.type == NeighborsType::Random)
				{
					lenPK = 1 - (1 / glm::distance(positions[pi], positions[pj]));
					forces[pi] += c * (lenPK * (positions[pi] - positions[pj]));
					forces[pj] += c * (lenPK * (positions[pi] - positions[pj]));
				}
				if (element.type == NeighborsType::Near)
				{
					forces[pi] += 2 * B * (positions[pi] - positions[pj]);
					forces[pj] += 2 * B * (positions[pi] - positions[pj]);
				}
			}
		}

		for (auto i = 0; i < m_ext_particleSystem.countAwakeParticles(); i++)
		{
			positions[i] += forces[i] * learningRate;
		}
		
		m_ext_particleSystem.increaseStep();
	}

	void CasterSGD::initPos()
	{
		m_randomCaster.castParticleSystem();
	}
}
