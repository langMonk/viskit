#include "facade\FacadeCasterForceDirected.h"

namespace ivhd::facade
{
	FacadeCasterForceDirected::FacadeCasterForceDirected(std::shared_ptr<core::Core> core)
		: FacadeCaster(core)
		, m_internalCaster(std::make_shared<ivhd::embed::cast::ivhd::CasterForceDirected>(core->system()))
	{
	}

	void FacadeCasterForceDirected::calculatePositions(IParticleSystem& ps)
	{
		try
		{
			auto facadePs = reinterpret_cast<FacadeParticleSystem*>(&ps);
			dynamic_cast<ivhd::embed::cast::ivhd::CasterForceDirected*>(m_internalCaster.get())->calculatePositions(facadePs->internalSystem());
		}
		catch (std::exception & ex)
		{
			m_ext_core->logger().logWarning("Failed to cast data using CasterAdadelta.calculatePositions. Error message: " + *ex.what());
		}
	}

	void FacadeCasterForceDirected::calculateForces(IParticleSystem & ps, IGraph & graph)
	{
		try
		{
			auto facadePs = reinterpret_cast<FacadeParticleSystem*>(&ps);
			auto facadeGraph = reinterpret_cast<FacadeGraph*>(&graph);
			float energy = 0.1f;
			dynamic_cast<ivhd::embed::cast::ivhd::CasterForceDirected*>(m_internalCaster.get())->calculateForces(energy, facadePs->internalSystem(), facadeGraph->internalGraph());
		}
		catch (std::exception & ex)
		{
			m_ext_core->logger().logWarning("Failed to cast data using CasterAdadelta.calculatePositions. Error message: " + *ex.what());
		}
	}
}