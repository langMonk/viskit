///
/// \author Bartosz Minch <minch@agh.edu.pl>
/// \date 18.04.2019
///

#pragma once

#include <memory>
#include <vector>
#include <map>
#include <numeric>
#include <functional>

#include "core/System.h"
#include "particles/ParticleData.h"
#include "particles/generate/ParticleGenerator.h"
#include "particles/emit/ParticleEmitter.h"
#include "particles/update/ParticleUpdater.h"
#include "graph/Point.h"
#include "graph/Graph.h"

using namespace ivhd::graph;

namespace ivhd::particles
{
	// public sub-types
	using Dataset = std::vector<std::pair<Point, size_t>>;

	enum class MetricType { Euclidean, Cosine };

	class ParticleSystem
	{
		// public construction and destruction methods
	public:
		explicit ParticleSystem(core::System& system);
		~ParticleSystem(){}

		ParticleSystem(const ParticleSystem&) = delete;
		ParticleSystem& operator=(const ParticleSystem&) = delete;

		// public methods
	public:
		virtual size_t countParticles() const { return m_particles.m_count; }
		virtual size_t countAwakeParticles() const { return m_particles.m_countAlive; }

		void addEmitter(std::shared_ptr<emit::ParticleEmitter> em) { m_emitters.push_back(em); }
		void addUpdater(std::shared_ptr<update::ParticleUpdater> up) { m_updaters.push_back(up); }

		Dataset& originalCoordinates() { return m_originalCoordinates; }

		void loadData(Dataset container) { m_originalCoordinates = container; }
		void clear() { m_originalCoordinates.clear(); }

		void setMetric(MetricType type);
		MetricType& currentMetric();

		ParticleData* calculationData() { return &m_particles; }

		Graph* neighbourhoodGraph() { return &m_neighbourhoodGraph; }

		template<class Value_T>
		struct DiffSquared
		{
			Value_T operator()(Value_T x, Value_T y) const {
				return (x - y) * (x - y);
			}
		};

		float vectorDistance(size_t i, size_t j)
		{
			float ret = std::inner_product(m_originalCoordinates[i].first.begin(), m_originalCoordinates[i].first.end(),
										m_originalCoordinates[j].first.begin(), 0.0f, std::plus<float>(), DiffSquared <float>());
			return ret > 0.0f ? sqrt(ret) : 0.0f;
		}

		// private members
	private:
		core::System& m_ext_system;

		Graph m_neighbourhoodGraph;

		Dataset m_originalCoordinates;

		ParticleData m_particles;
		
		std::vector<std::shared_ptr<emit::ParticleEmitter>> m_emitters;
		std::vector<std::shared_ptr<update::ParticleUpdater>> m_updaters;

		MetricType m_currentMetric;
	};
}