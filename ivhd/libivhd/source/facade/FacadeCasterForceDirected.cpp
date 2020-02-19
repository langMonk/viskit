#include "facade\FacadeCasterForceDirected.h"

namespace ivhd::facade
{
	FacadeCasterForceDirected::FacadeCasterForceDirected(std::shared_ptr<core::Core> core, particles::ParticleSystem& ps)
		: FacadeCaster(core, ps)
		, m_internalCaster(std::make_shared<ivhd::embed::cast::ivhd::CasterForceDirected>(core->system(), ps))
	{
	}

	void FacadeCasterForceDirected::castParticleSystem()
	{
		try
		{
			m_internalCaster->castParticleSystem();
		}
		catch (std::exception& ex)
		{
			m_ext_core->logger().logWarning("Failed to cast data using CasterForceDirected.castParticleSystem. Error message: " + *ex.what());
		}
	}

	void FacadeCasterForceDirected::castParticle(size_t index)
	{
		try
		{
			m_internalCaster->castParticle(index);
		}
		catch (std::exception& ex)
		{
			m_ext_core->logger().logWarning("Failed to cast data using CasterForceDirected.castParticle. Error message: " + *ex.what());
		}
	}
}