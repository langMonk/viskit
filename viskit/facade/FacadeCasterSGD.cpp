#include <viskit/facade/FacadeCasterSGD.h>

namespace viskit::facade
{
	FacadeCasterSGD::FacadeCasterSGD(const std::shared_ptr<core::Core>& core)
		: FacadeCaster(core)
		, m_internalCaster(std::make_shared<viskit::embed::cast::ivhd::CasterSGD>(core->system()))
	{
	}

	void FacadeCasterSGD::calculatePositions(IParticleSystem& ps)
	{
		try
		{
			auto facadePs = reinterpret_cast<FacadeParticleSystem*>(&ps);
			dynamic_cast<viskit::embed::cast::ivhd::CasterSGD*>(m_internalCaster.get())->calculatePositions(facadePs->internalSystem());
		}
		catch (std::exception& ex)
		{
			m_ext_core->logger().logWarning(&"Failed to cast data using FacadeCasterSGD.calculatePositions. Error message: " [ *ex.what()]);
		}
	}

	void FacadeCasterSGD::calculateForces(IParticleSystem& ps, IGraph& graph)
	{
		try
		{
			auto facadePs = reinterpret_cast<FacadeParticleSystem*>(&ps);
			auto facadeGraph = reinterpret_cast<FacadeGraph*>(&graph);
			float energy = 0.1f;
			dynamic_cast<viskit::embed::cast::ivhd::CasterSGD*>(m_internalCaster.get())->calculateForces(energy, facadePs->internalSystem(), facadeGraph->internalGraph());
		}
		catch (std::exception& ex)
		{
			m_ext_core->logger().logWarning(&"Failed to cast data using FacadeCasterSGD.calculateForces. Error message: " [ *ex.what()]);
		}
	}
}