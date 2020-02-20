#include "facade\FacadeCasterNesterov.h"

namespace ivhd::facade
{
	FacadeCasterNesterov::FacadeCasterNesterov(std::shared_ptr<core::Core> core, particles::ParticleSystem& ps)
		: FacadeCaster(core, ps)
		, m_internalCaster(std::make_shared<ivhd::embed::cast::ivhd::CasterNesterov>(core->system(), ps))
	{
	}

	void FacadeCasterNesterov::castParticleSystem()
	{
		try
		{
			m_internalCaster->castParticleSystem();
		}
		catch (std::exception& ex)
		{
			m_ext_core->logger().logWarning("Failed to cast data using CasterNesterov.castParticleSystem. Error message: " + *ex.what());
		}
	}

	void FacadeCasterNesterov::castParticle(size_t index)
	{
		try
		{
			m_internalCaster->castParticle(index);
		}
		catch (std::exception& ex)
		{
			m_ext_core->logger().logWarning("Failed to cast data using CasterNesterov.castParticle. Error message: " + *ex.what());
		}
	}
}