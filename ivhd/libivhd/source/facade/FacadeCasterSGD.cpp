#include "facade\FacadeCasterSGD.h"

namespace ivhd::facade
{
	FacadeCasterSGD::FacadeCasterSGD(std::shared_ptr<core::Core> core, particles::ParticleSystem& ps)
		: FacadeCaster(core, ps)
		, m_internalCaster(std::make_shared<ivhd::embed::cast::ivhd::CasterSGD>(core->system(), ps))
	{
	}

	void FacadeCasterSGD::castParticleSystem()
	{
		try
		{
			m_internalCaster->castParticleSystem();
		}
		catch (std::exception& ex)
		{
			m_ext_core->logger().logWarning("Failed to cast data using CasterSGD.castParticleSystem. Error message: " + *ex.what());
		}
	}

	void FacadeCasterSGD::castParticle(size_t index)
	{
		try
		{
			m_internalCaster->castParticle(index);
		}
		catch (std::exception& ex)
		{
			m_ext_core->logger().logWarning("Failed to cast data using CasterSGD.castParticle. Error message: " + *ex.what());
		}
	}
}