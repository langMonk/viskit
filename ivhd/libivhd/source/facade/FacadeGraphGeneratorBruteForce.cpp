#include "facade\FacadeGraphGeneratorBruteForce.h"

namespace ivhd::facade
{
	FacadeGraphGeneratorBruteForce::FacadeGraphGeneratorBruteForce(std::shared_ptr<core::Core> core, particles::ParticleSystem& ps)
		: FacadeGraphGenerator(core, ps)
		, m_graphGenerator(std::make_shared<generate::BruteForce>(core->system(), ps))
	{
	}

	void FacadeGraphGeneratorBruteForce::generate(size_t nearestNeighbors, size_t furthestNeighbors, size_t randomNeighbors, bool distancesEqualOne)
	{
		if (m_graphGenerator != nullptr)
		{
			m_graphGenerator->generate(nearestNeighbors, furthestNeighbors, randomNeighbors, distancesEqualOne);
		}
	}
}
