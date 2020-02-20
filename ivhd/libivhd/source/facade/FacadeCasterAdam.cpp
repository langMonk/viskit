#include "facade\FacadeCasterAdam.h"

namespace ivhd::facade
{
	FacadeCasterAdam::FacadeCasterAdam(std::shared_ptr<core::Core> core, particles::ParticleSystem& ps)
		: FacadeCaster(core, ps)
		, m_internalCaster(std::make_shared<ivhd::embed::cast::ivhd::CasterAdam>(core->system(), ps))
	{
	}

	void FacadeCasterAdam::castParticleSystem()
	{
		try
		{
			m_internalCaster->castParticleSystem();
		}
		catch (std::exception& ex)
		{
			m_ext_core->logger().logWarning("Failed to cast data using CasterAdadelta.castParticleSystem. Error message: " + *ex.what());
		}
	}

	void FacadeCasterAdam::castParticle(size_t index)
	{
		try
		{
			m_internalCaster->castParticle(index);
		}
		catch (std::exception& ex)
		{
			m_ext_core->logger().logWarning("Failed to cast data using CasterAdadelta.castParticle. Error message: " + *ex.what());
		}
	}
}