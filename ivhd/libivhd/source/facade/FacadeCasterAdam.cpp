#include "facade\FacadeCasterAdam.h"

namespace ivhd::facade
{
	FacadeCasterAdam::FacadeCasterAdam(std::shared_ptr<core::Core> core)
		: FacadeCaster(core)
	{
		m_internalCaster = std::make_shared<embed::cast::ivhd::CasterAdam>(core->system());
	}

	void FacadeCasterAdam::calculatePositions(IParticleSystem& ps)
	{
		try
		{
			auto facadePs = reinterpret_cast<FacadeParticleSystem*>(&ps);
			dynamic_cast<embed::cast::ivhd::CasterAdam*>(m_internalCaster.get())->calculatePositions(facadePs->internalSystem());
		}
		catch (std::exception & ex)
		{
			m_ext_core->logger().logWarning("Failed to cast data using CasterAdam.calculatePositions. Error message: " + *ex.what());
		}
	}

	void FacadeCasterAdam::calculateForces(IParticleSystem & ps, IGraph & graph)
	{
		try
		{
			auto facadePs = reinterpret_cast<FacadeParticleSystem*>(&ps);
			auto facadeGraph = reinterpret_cast<FacadeGraph*>(&graph);
			float energy = 0.1f;
			dynamic_cast<embed::cast::ivhd::CasterAdam*>(m_internalCaster.get())->calculateForces(energy, facadePs->internalSystem(), facadeGraph->internalGraph());
		}
		catch (std::exception & ex)
		{
			m_ext_core->logger().logWarning("Failed to cast data using CasterAdam.calculatePositions. Error message: " + *ex.what());
		}
	}
}