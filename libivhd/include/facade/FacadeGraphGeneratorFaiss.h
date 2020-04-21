///
/// \author Bartosz Minch <minch@agh.edu.pl>
/// \date 15.04.2020
///

#pragma once

#include "facade/FacadeGraphGenerator.h"
#include "facade/FacadeParticleSystem.h"
#include "graph/generate/Faiss.h"

namespace ivhd::facade
{
	/// <summary>
	/// Implementation of IGraphGenerator interface.
	/// </summary>
	class FacadeGraphGeneratorFaiss : public FacadeGraphGenerator
	{
	public:
		FacadeGraphGeneratorFaiss(std::shared_ptr<core::Core> core);

		void generateNearestNeighbors(IParticleSystem& ps, IGraph& graph, size_t k = 0, bool distancesEqualOne = true) override;

		void generateRandomNeighbors(IParticleSystem& ps, IGraph& graph, size_t k = 0, bool distancesEqualOne = true) override;

	private:
		std::shared_ptr<generate::Faiss> m_graphGenerator {nullptr};

	};
}