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

	void ParticleSystem::setDataset(Dataset dataset, std::vector<DataPointLabel> labels)
	{
		utils::RandomColor color;
		if (!dataset.empty())
		{
			m_originalDataset = dataset;
		}

		for (const auto label : labels)
		{
			m_colorsMap.insert(std::pair<DataPointLabel, Color>(label, color.generate()));
		}

		for (size_t i = 0; i < countParticles(); i++)
		{
			m_particles.m_col[i] = m_colorsMap[dataset[i].second];
		}
	}

	void ParticleSystem::clear()
	{
		if (!m_originalDataset.empty() && !m_particles.empty())
		{
			m_originalDataset.clear();
			m_particles.clear();
		}
	}

	bool ParticleSystem::empty()
	{
		return (m_originalDataset.empty() && m_particles.empty()) ? true : false;
	}


	void ParticleSystem::setMetric(MetricType type)
	{
		m_currentMetric = type;
	}

	float ParticleSystem::vectorDistance(size_t i, size_t j)
	{
		float ret = std::inner_product(m_originalDataset[i].first.begin(), m_originalDataset[i].first.end(),
				m_originalDataset[j].first.begin(), 0.0f, std::plus<float>(), DiffSquared <float>());

		return ret > 0.0f ? sqrt(ret) : 0.0f;
	}
}
