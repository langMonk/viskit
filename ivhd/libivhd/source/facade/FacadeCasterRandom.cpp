///
/// \author Bartosz Minch <minch@agh.edu.pl>
/// \date 12.05.2019
///

#include "facade/FacadeCasterRandom.h"

namespace ivhd::facade
{
	FacadeCasterRandom::FacadeCasterRandom(std::shared_ptr<core::Core> core, particles::ParticleSystem& ps)
		: FacadeCaster(core, ps)
		, m_internalCaster(std::make_shared<ivhd::embed::cast::CasterRandom>(core->system(), ps))
	{
	}

	void FacadeCasterRandom::castParticleSystem()
	{
		try
		{
			m_internalCaster->castParticleSystem();
		}
		catch (std::exception& ex)
		{
			m_ext_core->logger().logWarning("Failed to cast data using CasterRandom.castParticleSystem. Error message: " + *ex.what());
		}
	}

	void FacadeCasterRandom::castParticle(size_t index)
	{
		try
		{
			m_internalCaster->castParticle(index);
		}
		catch (std::exception& ex)
		{
			m_ext_core->logger().logWarning("Failed to cast data using CasterRandom.castParticle. Error message: " + *ex.what());
		}
	}
}
