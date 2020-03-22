///
/// \author Bartosz Minch <minch@agh.edu.pl>
/// \date 18.04.2019
///

#pragma once

#include <utility>
#include <vector>
#include <map>
#include <mutex>

#include "core/System.h"
#include "particles/ParticleData.h"
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

	struct DatasetInfo
	{
		std::string path;
		std::string fileName;
		size_t count{};
	};

	enum class MetricType { Euclidean, Cosine };

	class ParticleSystem
	{
		// public construction and destruction methods
	public:
		explicit ParticleSystem(core::System& system);
		~ParticleSystem() = default;

		ParticleSystem(const ParticleSystem&) = delete;
		ParticleSystem& operator=(const ParticleSystem&) = delete;

		// public methods
	public:
		virtual size_t countParticles();

		virtual size_t countAwakeParticles();

		void setDataset(Dataset dataset, const std::vector<DataPointLabel>& labels);

		std::vector<DataPointLabel> labels() { return m_labels; };

		void resetForces();

		void resetVelocities();

		void clear();

		bool empty();

		// public getters and setters
	public:
		Dataset& originalCoordinates() { return m_originalDataset; }

		MetricType* currentMetric() { return &m_currentMetric; };

		ParticleData* calculationData();

		void setMetric(MetricType type) { m_currentMetric = type; };

		size_t step() { return m_step; }

		void increaseStep() { m_step++; }

		[[nodiscard]] DatasetInfo datasetInfo() const { return m_datasetFileName; }

		void datasetInfo(DatasetInfo info) { m_datasetFileName = std::move(info); }

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

		Dataset m_originalDataset;

		ParticleData m_particles;

		std::vector<DataPointLabel> m_labels;

		std::map<DataPointLabel, Color> m_colorsMap;

		DatasetInfo m_datasetFileName;

		MetricType m_currentMetric;

		size_t m_step{ 0 };

		std::mutex m_lock;
	};
}
