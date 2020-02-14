///
/// \author Bartosz Minch <minch@agh.edu.pl>
/// \date 18.04.2019
///

#pragma once

#include <memory>
#include <vector>
#include <map>

#include "core/System.h"
#include "particles/ParticleData.h"
#include "particles/generate/ParticleGenerator.h"
#include "particles/emit/ParticleEmitter.h"
#include "particles/update/ParticleUpdater.h"
#include "graph/Graph.h"
#include "ivhd/Structures.h"
#include "utils/RandomColor.h"

using namespace ivhd::graph;

namespace ivhd::particles
{
	// public sub-types
	using DataPointLabel = size_t;
	using Color = glm::vec4;
	using Dataset = std::vector<std::pair<DataPoint, DataPointLabel>>;

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
		
		void setDataset(Dataset dataset, std::vector<DataPointLabel> labels);
		
		void clear();
		
		bool empty();

		// public getters and setters
	public:
		Dataset& originalCoordinates() { return m_originalDataset; }
		
		MetricType* currentMetric() { return &m_currentMetric; };
		
		ParticleData* calculationData() { return &m_particles; }
		
		Graph& neighbourhoodGraph() { return m_neighbourhoodGraph; }
		
		void setMetric(MetricType type);

		// add emitters, casters, etc.
	public:
		void addEmitter(std::shared_ptr<emit::ParticleEmitter> em) { m_emitters.push_back(em); }
		
		void addUpdater(std::shared_ptr<update::ParticleUpdater> up) { m_updaters.push_back(up); }

		// add emitters, casters, etc.
	public:
		template<class T>
		struct DiffSquared
		{
			T operator()(T x, T y) const {
				return (x - y) * (x - y);
			}
		};

		float vectorDistance(size_t i, size_t j);

		// private members
	private:
		core::System& m_ext_system;

		Graph m_neighbourhoodGraph;

		Dataset m_originalDataset;

		ParticleData m_particles;

		std::map<DataPointLabel, Color> m_colorsMap;

		std::vector<std::shared_ptr<emit::ParticleEmitter>> m_emitters;
		
		std::vector<std::shared_ptr<update::ParticleUpdater>> m_updaters;

		MetricType m_currentMetric;
	};
}