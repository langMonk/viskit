#include <utility>

#include "facade\FacadeCaster.h"


namespace ivhd::facade
{
	FacadeCaster::FacadeCaster(std::shared_ptr<core::Core> core)
		: m_ext_core(std::move(core))
	{
	}

	void FacadeCaster::step(IParticleSystem& ps, IGraph& graph)
	{
		try
		{
			const auto facadePs = reinterpret_cast<FacadeParticleSystem*>(&ps);
			const auto facadeGraph = reinterpret_cast<FacadeGraph*>(&graph);
			m_internalCaster->castParticleSystem(facadePs->internalSystem(), facadeGraph->internalGraph());
		}
		catch (std::exception & ex)
		{
			m_ext_core->logger().logWarning("Failed to cast data using FacadeCaster.castParticleSystem. Error message: " + *ex.what());
		}
	}
}
