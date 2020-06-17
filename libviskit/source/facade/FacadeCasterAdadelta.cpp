#include "facade/FacadeCasterAdadelta.h"

namespace viskit::facade
{
	FacadeCasterAdadelta::FacadeCasterAdadelta(const std::shared_ptr<core::Core>& core)
		: FacadeCaster(core)
	{
		m_internalCaster = std::make_shared<embed::cast::ivhd::CasterAdadelta>(core->system());
	}

	void FacadeCasterAdadelta::calculatePositions(IParticleSystem& ps)
	{
		try
		{
			auto facadePs = reinterpret_cast<FacadeParticleSystem*>(&ps);
			dynamic_cast<embed::cast::ivhd::CasterAdadelta*>(m_internalCaster.get())->calculatePositions(facadePs->internalSystem());
		}
		catch (std::exception & ex)
		{
			m_ext_core->logger().logWarning(&"Failed to cast data using FacadeCasterAdadelta.calculatePositions. Error message: " [ *ex.what()]);
		}
	}

	void FacadeCasterAdadelta::calculateForces(IParticleSystem& ps, IGraph& graph)
	{
		try
		{
			auto facadePs = reinterpret_cast<FacadeParticleSystem*>(&ps);
			auto facadeGraph = reinterpret_cast<FacadeGraph*>(&graph);
			dynamic_cast<embed::cast::ivhd::CasterAdadelta*>(m_internalCaster.get())->calculateForces(energy, facadePs->internalSystem(), facadeGraph->internalGraph());
		}
		catch (std::exception & ex)
		{
			m_ext_core->logger().logWarning(&"Failed to cast data using FacadeCasterAdadelta.calculateForces. Error message: " [ *ex.what()]);
		}
	}
}