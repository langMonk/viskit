#include "facade\FacadeInteractiveVizualization.h"
#include <exception>

namespace ivhd::facade
{
	FacadeInteractiveVizualization::FacadeInteractiveVizualization(LogHandler logHandler)
		: m_core(std::make_shared<core::Core>(logHandler))
	{

	}

	std::shared_ptr<core::Core> FacadeInteractiveVizualization::core() const
	{
		return m_core;
	}

	IParticleSystem& FacadeInteractiveVizualization::particleSystem()
	{
		return m_particleSystem;
	}

	particles::ParticleSystem& FacadeInteractiveVizualization::internalParticleSystem()
	{
		return m_internalParticleSystem;
	}
	
	IResourceFactory& FacadeInteractiveVizualization::resourceFactory()
	{
		return m_resourceFactory;
	}
}
