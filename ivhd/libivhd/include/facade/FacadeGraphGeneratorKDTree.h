///
/// \author Bartosz Minch <minch@agh.edu.pl>
/// \date 10.02.2020
///

#pragma once

#include <mutex>
#include <thread>

#include "ivhd/IParticleSystem.h"
#include "ivhd/IGraphGenerator.h"
#include "facade/FacadeGraphGenerator.h"
#include "facade/FacadeParticleSystem.h"
#include "graph/generate/KDTree.h"

namespace ivhd::facade
{
	/// <summary>
	/// Implementation of IGraphGenerator interface.
	/// </summary>
	class FacadeGraphGeneratorKDTree : public FacadeGraphGenerator
	{
	public:
		std::shared_ptr<IGraph> generate(std::shared_ptr<ivhd::IParticleSystem>& ps) override;

	private:
		static void kNNQueryThread(int start, int end, bool setDistancesToOne, const graph::generate::KDTree& kd, size_t k, const particles::Dataset& data, graph::Graph& graph);

		static std::mutex m_generationMutex;

	private:
		std::shared_ptr<graph::generate::KDTree> m_graph;
	};
}