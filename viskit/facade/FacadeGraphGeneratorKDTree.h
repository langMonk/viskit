///
/// \author Bartosz Minch <minch@agh.edu.pl>
/// \date 10.02.2020
///

#pragma once

#include <mutex>

#include <viskit/facade/FacadeGraphGenerator.h>
#include <viskit/facade/FacadeParticleSystem.h>
#include <viskit/graph/generate/KDTree.h>

namespace viskit::facade
{
	/// <summary>
	/// Implementation of IGraphGenerator interface.
	/// </summary>
	class FacadeGraphGeneratorKDTree : public FacadeGraphGenerator
	{
	public:
		explicit FacadeGraphGeneratorKDTree(std::shared_ptr<core::Core> core);
		
		void generate(IParticleSystem& ps, IGraph& graph, size_t k, bool distancesEqualOne) override {};

	private:
		static void kNNQueryThread(int start, int end, bool setDistancesToOne, const graph::generate::KDTree& kd, size_t k, const particles::Dataset& data, graph::Graph& graph);

		static std::mutex m_generationMutex;

	private:
		std::shared_ptr<graph::generate::KDTree> m_graphGenerator;
		
	};
}