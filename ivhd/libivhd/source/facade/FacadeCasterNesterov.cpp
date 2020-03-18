#include "facade\FacadeCasterNesterov.h"

namespace ivhd::facade
{
	FacadeCasterNesterov::FacadeCasterNesterov(std::shared_ptr<core::Core> core)
		: FacadeCaster(core)
	{
		m_internalCaster = std::make_shared<embed::cast::ivhd::CasterNesterov>(core->system());
	}

	void FacadeCasterNesterov::calculatePositions(IParticleSystem& ps)
	{
		try
		{
			const auto facadePs = reinterpret_cast<FacadeParticleSystem*>(&ps);
			dynamic_cast<embed::cast::ivhd::CasterNesterov*>(m_internalCaster.get())->calculatePositions(facadePs->internalSystem());
		}
		catch (std::exception & ex)
		{
			m_ext_core->logger().logWarning("Failed to cast data using FacadeCasterNesterov.calculatePositions. Error message: " + *ex.what());
		}
	}

	void FacadeCasterNesterov::calculateForces(IParticleSystem& ps, IGraph& graph)
	{
		try
		{
			const auto facadePs = reinterpret_cast<FacadeParticleSystem*>(&ps);
			const auto facadeGraph = reinterpret_cast<FacadeGraph*>(&graph);
			auto energy = 0.1f;
			dynamic_cast<embed::cast::ivhd::CasterNesterov*>(m_internalCaster.get())->calculateForces(energy, facadePs->internalSystem(), facadeGraph->internalGraph());
		}
		catch (std::exception & ex)
		{
			m_ext_core->logger().logWarning("Failed to cast data using FacadeCasterNesterov.calculatePositions. Error message: " + *ex.what());
		}
	}
}