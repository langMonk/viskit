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

	void FacadeCasterRandom::cast(std::shared_ptr<ivhd::IParticleSystem>& ps)
	{
		try
		{
			auto particleSystem = dynamic_cast<FacadeParticleSystem*>(ps.get());
			m_internalCaster->cast(*particleSystem->internalParticleSystem().get());
		}
		catch (std::exception& ex)
		{
			m_ext_core->logger().logWarning("Failed to cast data using RandomCaster. Error message: " + *ex.what());
		}
	}
}
