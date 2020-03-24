#include "facade/FacadeGraphGeneratorBruteForce.h"
#include "facade/FacadeGraph.h"

namespace ivhd::facade
{
	FacadeGraphGeneratorBruteForce::FacadeGraphGeneratorBruteForce(std::shared_ptr<core::Core> core)
		: FacadeGraphGenerator(core)
		, m_graphGenerator(std::make_shared<generate::BruteForce>(core->system()))
	{
	}

	void FacadeGraphGeneratorBruteForce::generate(IParticleSystem& ps, IGraph& graph, size_t nn, size_t rn, bool distancesEqualOne)
	{
		try
		{
			generateNearestNeighbors(ps, graph, nn, distancesEqualOne);
			if (rn)
			{
				generateRandomNeighbors(ps, graph, rn, distancesEqualOne);

			}
		}
		catch (std::exception & ex)
		{
			m_ext_core->logger().logWarning("Failed to cast data using FacadeGraphGeneratorBruteForce.generate. Error message: " + *ex.what());
		}
	}

	void FacadeGraphGeneratorBruteForce::generateNearestNeighbors(IParticleSystem& ps, IGraph& graph, size_t k, bool distancesEqualOne)
	{
		try
		{
			const auto facadePs = reinterpret_cast<FacadeParticleSystem*>(&ps);
			const auto facadeGraph = reinterpret_cast<FacadeGraph*>(&graph);
			dynamic_cast<generate::BruteForce*> (m_graphGenerator.get())->
				generateNearestNeighbors(facadePs->internalSystem(), facadeGraph->internalGraph(), k, distancesEqualOne);
		}
		catch (std::exception & ex)
		{
			m_ext_core->logger().logWarning("Failed to cast data using FacadeGraphGeneratorBruteForce.generateNearestNeighbors. Error message: " + *ex.what());
		}
	}

	void FacadeGraphGeneratorBruteForce::generateRandomNeighbors(IParticleSystem& ps, IGraph& graph, size_t k, bool distancesEqualOne)
	{
		try
		{
			const auto facadePs = reinterpret_cast<FacadeParticleSystem*>(&ps);
			const auto facadeGraph = reinterpret_cast<FacadeGraph*>(&graph);
			dynamic_cast<generate::BruteForce*> (m_graphGenerator.get())->
				generateRandomNeighbors(facadePs->internalSystem(), facadeGraph->internalGraph(), k, distancesEqualOne);
		}
		catch (std::exception & ex)
		{
			m_ext_core->logger().logWarning("Failed to cast data using FacadeGraphGeneratorBruteForce.generateRandomNeighbors. Error message: " + *ex.what());
		}
	}
}
