#include "facade\FacadeCaster.h"

namespace ivhd::facade
{
	FacadeCaster::FacadeCaster(std::shared_ptr<core::Core> core)
		: m_ext_core(core)
	{
	}

	void FacadeCaster::step(IParticleSystem& ps, IGraph& graph)
	{
		try
		{
			auto facadePs = reinterpret_cast<FacadeParticleSystem*>(&ps);
			auto facadeGraph = reinterpret_cast<FacadeGraph*>(&graph);
			m_internalCaster->castParticleSystem(facadePs->internalSystem(), facadeGraph->internalGraph());
		}
		catch (std::exception & ex)
		{
			m_ext_core->logger().logWarning("Failed to cast data using FacadeCaster.castParticleSystem. Error message: " + *ex.what());
		}
	}
}
