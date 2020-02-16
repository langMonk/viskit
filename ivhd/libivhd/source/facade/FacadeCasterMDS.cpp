#include "facade\FacadeCasterMDS.h"

namespace ivhd::facade
{
	FacadeCasterMDS::FacadeCasterMDS(std::shared_ptr<core::Core> core, particles::ParticleSystem& ps)
		: FacadeCaster(core, ps)
		, m_internalCaster(std::make_shared<ivhd::embed::cast::CasterMDS>(core->system(), ps))
	{
	}

	void FacadeCasterMDS::castParticleSystem()
	{
		try
		{
			m_internalCaster->castParticleSystem();
		}
		catch (std::exception& ex)
		{
			m_ext_core->logger().logWarning("Failed to cast data using CasterMDS.castParticleSystem. Error message: " + *ex.what());
		}
	}
	
	void FacadeCasterMDS::castParticle(size_t index)
	{
		try
		{
			m_internalCaster->castParticle(index);
		}
		catch (std::exception& ex)
		{
			m_ext_core->logger().logWarning("Failed to cast data using CasterMDS.castParticle. Error message: " + *ex.what());
		}
	}
}