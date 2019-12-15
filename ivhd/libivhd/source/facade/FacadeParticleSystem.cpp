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

	std::vector<std::pair<graph::DataPoint, size_t>> FacadeParticleSystem::originalCoordinates()
	{
		return m_internalParticleSystem->originalCoordinates();
	}

	std::shared_ptr<particles::ParticleSystem> FacadeParticleSystem::internalParticleSystem() const
	{
		return m_internalParticleSystem;
	}

	size_t FacadeParticleSystem::countAlive()
	{
		return m_internalParticleSystem->countAwakeParticles();
	}

	void FacadeParticleSystem::clear()
	{
		if (m_internalParticleSystem != nullptr)
		{
			m_internalParticleSystem->clear();
		}
	}

	bool FacadeParticleSystem::empty()
	{
		return m_internalParticleSystem->empty();
	}

	particles::ParticleData* FacadeParticleSystem::availableData()
	{
		return m_internalParticleSystem->calculationData();
	}
}
