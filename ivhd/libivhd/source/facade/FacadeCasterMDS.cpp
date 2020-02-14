#include "facade\FacadeCasterMDS.h"

namespace ivhd::facade
{ 
	void FacadeCasterMDS::castParticleSystem(std::shared_ptr<ivhd::IParticleSystem>& ps)
	{
		try
		{
			auto particleSystem = dynamic_cast<FacadeParticleSystem*>(ps.get());
			m_internalCaster->castParticleSystem(*particleSystem->internalParticleSystem().get());
		}
		catch (std::exception & ex)
		{
			m_ext_core->logger().logWarning("Failed to cast data using CasterMDS.castParticleSystem. Error message: " + *ex.what());
		}
	}

	void FacadeCasterMDS::castParticle(std::shared_ptr<ivhd::IParticleSystem>& ps, size_t index)
	{
		try
		{
			auto particleSystem = dynamic_cast<FacadeParticleSystem*>(ps.get());
			m_internalCaster->castParticle(*particleSystem->internalParticleSystem().get(), index);
		}
		catch (std::exception & ex)
		{
			m_ext_core->logger().logWarning("Failed to cast data using CasterMDS.castParticle. Error message: " + *ex.what());
		}
	}
}