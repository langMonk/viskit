///
/// \author Bartosz Minch <minch@agh.edu.pl>
/// \date 15.02.2020
///

#pragma once

#include "facade/FacadeGraphGenerator.h"
#include "facade/FacadeParticleSystem.h"
#include "graph/generate/BruteForce.h"

namespace ivhd::facade
{
	/// <summary>
	/// Implementation of IGraphGenerator interface.
	/// </summary>
	class FacadeGraphGeneratorBruteForce : public FacadeGraphGenerator
	{
	public:
		explicit FacadeGraphGeneratorBruteForce(const std::shared_ptr<core::Core>& core);

		void generate(IParticleSystem& ps, IGraph& graph, size_t k , bool distancesEqualOne) override;

	private:
		std::shared_ptr<generate::BruteForce> m_graphGenerator {nullptr};

	};
}