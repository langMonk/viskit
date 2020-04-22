#include "facade/gpu/FacadeGpuGraphGeneratorFaiss.h"
#include "facade/FacadeGraph.h"

namespace ivhd::facade::gpu
{
	FacadeGpuGraphGeneratorFaiss::FacadeGpuGraphGeneratorFaiss(std::shared_ptr<core::Core> core)
		: FacadeGraphGenerator(core)
		, m_graphGenerator(std::make_shared<generate::Faiss>(core->system()))
	{
	}

	void FacadeGpuGraphGeneratorFaiss::generateNearestNeighbors(IParticleSystem& ps, IGraph& graph, size_t k, bool distancesEqualOne)
	{
		try
		{
			const auto facadePs = reinterpret_cast<FacadeParticleSystem*>(&ps);
			const auto facadeGraph = reinterpret_cast<FacadeGraph*>(&graph);
			dynamic_cast<generate::Faiss*> (m_graphGenerator.get())->
				generateNearestNeighbors(facadePs->internalSystem(), facadeGraph->internalGraph(), k, distancesEqualOne);
		}
		catch (std::exception & ex)
		{
			m_ext_core->logger().logWarning("Failed to cast data using FacadeGpuGraphGeneratorFaiss.generateNearestNeighbors. Error message: " + *ex.what());
		}
	}

	void FacadeGpuGraphGeneratorFaiss::generateRandomNeighbors(IParticleSystem& ps, IGraph& graph, size_t k, bool distancesEqualOne)
	{
		try
		{
			const auto facadePs = reinterpret_cast<FacadeParticleSystem*>(&ps);
			const auto facadeGraph = reinterpret_cast<FacadeGraph*>(&graph);
			dynamic_cast<generate::Faiss*> (m_graphGenerator.get())->
				generateRandomNeighbors(facadePs->internalSystem(), facadeGraph->internalGraph(), k, distancesEqualOne);
		}
		catch (std::exception & ex)
		{
			m_ext_core->logger().logWarning("Failed to cast data using FacadeGpuGraphGeneratorFaiss.generateRandomNeighbors. Error message: " + *ex.what());
		}
	}
}
