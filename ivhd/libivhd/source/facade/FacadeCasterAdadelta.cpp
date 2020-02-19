#include "facade\FacadeCasterAdadelta.h"

namespace ivhd::facade
{
	FacadeCasterAdadelta::FacadeCasterAdadelta(std::shared_ptr<core::Core> core, particles::ParticleSystem& ps)
		: FacadeCaster(core, ps)
		, m_internalCaster(std::make_shared<ivhd::embed::cast::ivhd::CasterAdadelta>(core->system(), ps))
	{
	}

	void FacadeCasterAdadelta::castParticleSystem()
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

	void FacadeCasterAdadelta::castParticle(size_t index)
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