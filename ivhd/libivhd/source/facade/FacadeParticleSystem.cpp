///
/// \author Bartosz Minch <minch@agh.edu.pl>
/// \date 04.05.2019
///

#include <exception>

#include "facade/FacadeParticleSystem.h"
#include "ivhd/ICaster.h"

namespace ivhd::facade
{ 
	FacadeParticleSystem::FacadeParticleSystem(std::shared_ptr<core::Core> core)
		: m_internalParticleSystem(std::make_shared<particles::ParticleSystem>(core->system()))
	{
	}

	std::vector<std::vector<float>> FacadeParticleSystem::originalCoordinates()
	{
		return m_internalParticleSystem->originalCoordinates();
	}

	std::shared_ptr<particles::ParticleSystem> FacadeParticleSystem::internalParticleSystem() const
	{
		return m_internalParticleSystem;
	}

	size_t FacadeParticleSystem::countAlive()
	{
		return m_internalParticleSystem->numAliveParticles();
	}

	particles::ParticleData* FacadeParticleSystem::finalData()
	{
		return m_internalParticleSystem->finalData();
	}
}
