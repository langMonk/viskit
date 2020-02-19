///
/// \author Bartosz Minch <minch@agh.edu.pl>
/// \date 10.02.2020
///

#pragma once

#include <mutex>

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
		FacadeGraphGeneratorKDTree(std::shared_ptr<core::Core> core, particles::ParticleSystem& ps);
		
		void generate(size_t nearestNeighbors, size_t furthestNeighbors, size_t randomNeighbors, bool distancesEqualOne) override;
		
	private:
		static void kNNQueryThread(int start, int end, bool setDistancesToOne, const graph::generate::KDTree& kd, size_t k, const particles::Dataset& data, graph::Graph& graph);

		static std::mutex m_generationMutex;

	private:
		std::shared_ptr<graph::generate::KDTree> m_graphGenerator;
		
	};
}