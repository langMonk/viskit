///
/// \author Bartosz Minch <minch@agh.edu.pl>
/// \date 18.04.2019
///

#include "particles/ParticleSystem.h"

namespace ivhd::particles
{
	ParticleSystem::ParticleSystem(core::System& system)
		: m_ext_system(system)
		, m_particles(ParticleData())
		, m_neighbourhoodGraph(system)
		, m_currentMetric(MetricType::Euclidean)
	{
		
	}

	void ParticleSystem::clear()
	{
		if (!m_originalCoordinates.empty() && !m_particles.empty())
		{
			m_originalCoordinates.clear();
			m_particles.clear();
		}
	}

	bool ParticleSystem::empty()
	{
		return (m_originalCoordinates.empty() && m_particles.empty()) ? true : false;
	}

	void ParticleSystem::setMetric(MetricType type)
	{
		m_currentMetric = type;
	}

	MetricType& ParticleSystem::currentMetric()
	{
		return m_currentMetric;
	}
}
