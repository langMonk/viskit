///
/// \author Bartosz Minch <minch@agh.edu.pl>
/// \date 04.05.2019
///

#include "facade/FacadeParticleSystem.h"
#include "facade/FacadeGraph.h"
#include <memory>

namespace ivhd::facade
{ 
	FacadeParticleSystem::FacadeParticleSystem(std::shared_ptr<core::Core> core)
		: m_ext_core(core)
		, m_internalParticleSystem(std::make_shared<particles::ParticleSystem>(core->system()))
	{
	}

	std::vector<std::pair<DataPoint, size_t>> FacadeParticleSystem::originalCoordinates()
	{
		return m_internalParticleSystem->originalCoordinates();
	}

	std::vector<glm::vec4> FacadeParticleSystem::positions()
	{
		return m_internalParticleSystem->calculationData()->m_pos;
	};

	std::vector<glm::vec4> FacadeParticleSystem::forces()
	{
		return m_internalParticleSystem->calculationData()->m_force;
	};

	std::vector<glm::vec4> FacadeParticleSystem::velocities()
	{
		return m_internalParticleSystem->calculationData()->m_vel;
	};

	std::vector<glm::vec4> FacadeParticleSystem::colors()
	{
		return m_internalParticleSystem->calculationData()->m_col;
	}

	std::vector<size_t> FacadeParticleSystem::labels()
	{
		return m_internalParticleSystem->labels();
	}

	void FacadeParticleSystem::setPositon(size_t index, float x, float y)
	{
		m_internalParticleSystem->calculationData()->m_pos[index] = glm::vec4{ x, y, 0.0f, 1.0f };
	}

	size_t FacadeParticleSystem::countAlive()
	{
		return m_internalParticleSystem->countAwakeParticles();
	}

	size_t FacadeParticleSystem::countParticles()
	{
		return m_internalParticleSystem->countParticles();
	}

	void FacadeParticleSystem::clear()
	{
	
		m_internalParticleSystem->clear();
	}

	bool FacadeParticleSystem::empty()
	{
		return m_internalParticleSystem->empty();
	}
}
