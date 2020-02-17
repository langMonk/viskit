#include "facade\FacadeCasterAB.h"

namespace ivhd::facade
{
	FacadeCasterAB::FacadeCasterAB(std::shared_ptr<core::Core> core, particles::ParticleSystem& ps)
		: FacadeCaster(core, ps)
		, m_internalCaster(std::make_shared<ivhd::embed::cast::CasterAB>(core->system(), ps))
	{
	}

	void FacadeCasterAB::castParticleSystem()
	{
		try
		{
			m_internalCaster->castParticleSystem();
		}
		catch (std::exception& ex)
		{
			m_ext_core->logger().logWarning("Failed to cast data using CasterAB.castParticleSystem. Error message: " + *ex.what());
		}
	}

	void FacadeCasterAB::castParticle(size_t index)
	{
		try
		{
			m_internalCaster->castParticle(index);
		}
		catch (std::exception& ex)
		{
			m_ext_core->logger().logWarning("Failed to cast data using CasterAB.castParticle. Error message: " + *ex.what());
		}
	}
}