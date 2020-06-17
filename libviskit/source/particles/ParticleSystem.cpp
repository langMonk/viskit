///
/// \author Bartosz Minch <minch@agh.edu.pl>
/// \date 18.04.2019
///

#include "particles/ParticleSystem.h"
#include <numeric>

namespace viskit::particles
{
	ParticleSystem::ParticleSystem(core::System& system)
		: m_ext_system(system)
		, m_particles(ParticleData())
		, m_currentMetric(MetricType::Euclidean)
	{
		
	}

	size_t ParticleSystem::countParticles()
	{
		std::scoped_lock lock{ m_lock };
		return m_particles.m_count;
	}

	size_t ParticleSystem::countAwakeParticles()
	{
		std::scoped_lock lock{ m_lock };
		return m_particles.m_countAlive;
	}
	
	void ParticleSystem::setDataset(Dataset dataset, const std::vector<DataPointLabel>& labels)
	{
		m_labels = labels;

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

    std::vector<size_t> ParticleSystem::labels()
    {
	    std::vector<DataPointLabel> labels;
        labels.reserve(m_originalDataset.size());

        for (auto& point : m_originalDataset)
        {
            labels.emplace_back(point.second);
        }
        return labels;
    }

    void ParticleSystem::resetForces()
	{
		for(auto i = 0; i < countParticles(); i++)
		{
			m_particles.m_force[i] = glm::vec4{ 0.0f, 0.0f,0.0f, 0.0f };
		}
	}

	void ParticleSystem::resetVelocities()
	{
		for (auto i = 0; i < countParticles(); i++)
		{
			m_particles.m_vel[i] = glm::vec4{ 0.0f, 0.0f,0.0f, 0.0f };
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
		return m_originalDataset.empty() && m_particles.empty();
	}

	ParticleData* ParticleSystem::calculationData()
	{
		std::scoped_lock lock{ m_lock };
		return &m_particles;
	}

	float ParticleSystem::vectorDistance(size_t i, size_t j)
	{
		const auto ret = std::inner_product(m_originalDataset[i].first.begin(), m_originalDataset[i].first.end(),
		                                    m_originalDataset[j].first.begin(), 0.0f, std::plus<>(),
		                                    DiffSquared<float>());

		return ret > 0.0f ? static_cast<float>(sqrt(ret)) : 0.0f;
	}
}
