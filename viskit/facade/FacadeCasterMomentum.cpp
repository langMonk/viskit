///
/// \author Bartosz Minch <minch@agh.edu.pl>
/// \date 10.02.2020
///

#include <viskit/facade/FacadeCasterMomentum.h>

namespace viskit::facade
{
	FacadeCasterMomentum::FacadeCasterMomentum(const std::shared_ptr<core::Core>& core)
		: FacadeCaster(core)
	{
		m_internalCaster = std::make_shared<embed::cast::ivhd::CasterMomentum>(core->system());
	}

	void FacadeCasterMomentum::calculatePositions(IParticleSystem& ps)
	{
		try
		{
			const auto facadePs = reinterpret_cast<FacadeParticleSystem*>(&ps);
			dynamic_cast<embed::cast::ivhd::CasterMomentum*>(m_internalCaster.get())->calculatePositions(facadePs->internalSystem());
		}
		catch (std::exception & ex)
		{
			m_ext_core->logger().logWarning(&"Failed to cast data using FacadeCasterMomentum.calculatePositions. "
                                    "Error message: " [ *ex.what()]);
		}
	}

	void FacadeCasterMomentum::calculateForces(IParticleSystem & ps, IGraph & graph)
	{
		try
		{
			const auto facadePs = reinterpret_cast<FacadeParticleSystem*>(&ps);
			const auto facadeGraph = reinterpret_cast<FacadeGraph*>(&graph);
			auto energy = 0.1f;
			dynamic_cast<embed::cast::ivhd::CasterMomentum*>(m_internalCaster.get())->calculateForces(energy, facadePs->internalSystem(), facadeGraph->internalGraph());
		}
		catch (std::exception & ex)
		{
			m_ext_core->logger().logWarning(&"Failed to cast data using FacadeCasterMomentum.calculateForces. "
                                    "Error message: " [ *ex.what()]);
		}
	}
}