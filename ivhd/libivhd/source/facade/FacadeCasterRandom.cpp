///
/// \author Bartosz Minch <minch@agh.edu.pl>
/// \date 12.05.2019
///

#include "facade/FacadeCasterRandom.h"

namespace ivhd::facade
{
	FacadeCasterRandom::FacadeCasterRandom(std::shared_ptr<core::Core> core)
		: FacadeCaster(core)
		, m_internalCaster(std::make_shared<ivhd::embed::cast::CasterRandom>(core->system()))
	{
	}

	void FacadeCasterRandom::calculatePositions(IParticleSystem& ps)
	{
		try
		{
			auto facadePs = reinterpret_cast<FacadeParticleSystem*>(&ps);
			dynamic_cast<ivhd::embed::cast::CasterRandom*>(m_internalCaster.get())->calculatePositions(facadePs->internalSystem());
		}
		catch (std::exception& ex)
		{
			m_ext_core->logger().logWarning("Failed to cast data using FacadeCasterNesterov.calculatePositions. Error message: " + *ex.what());
		}
	}
}
