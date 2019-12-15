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

	float ParticleSystem::vectorDistance(size_t i, size_t j)
	{
		float ret = std::inner_product(m_originalCoordinates[i].first.begin(), m_originalCoordinates[i].first.end(),
				m_originalCoordinates[j].first.begin(), 0.0f, std::plus<float>(), DiffSquared <float>());

		return ret > 0.0f ? sqrt(ret) : 0.0f;
	}
}
