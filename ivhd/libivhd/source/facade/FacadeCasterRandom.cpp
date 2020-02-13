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

	void FacadeCasterRandom::castParticleSystem(std::shared_ptr<ivhd::IParticleSystem>& ps)
	{
		try
		{
			auto particleSystem = dynamic_cast<FacadeParticleSystem*>(ps.get());
			m_internalCaster->castParticleSystem(*particleSystem->internalParticleSystem().get());
		}
		catch (std::exception& ex)
		{
			m_ext_core->logger().logWarning("Failed to cast data using CasterRandom.castParticleSystem. Error message: " + *ex.what());
		}
	}

	void FacadeCasterRandom::castParticle(std::shared_ptr<ivhd::IParticleSystem>& ps, size_t index)
	{
		try
		{
			auto particleSystem = dynamic_cast<FacadeParticleSystem*>(ps.get());
			m_internalCaster->castParticle(*particleSystem->internalParticleSystem().get(), index);
		}
		catch (std::exception& ex)
		{
			m_ext_core->logger().logWarning("Failed to cast data using CasterRandom.castParticle. Error message: " + *ex.what());
		}
	}
}
