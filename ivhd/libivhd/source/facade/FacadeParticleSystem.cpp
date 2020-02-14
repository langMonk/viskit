///
/// \author Bartosz Minch <minch@agh.edu.pl>
/// \date 04.05.2019
///

#include <exception>

#include "facade/FacadeParticleSystem.h"
#include "facade/FacadeGraph.h"
#include <memory>

namespace ivhd::facade
{ 
	FacadeParticleSystem::FacadeParticleSystem(std::shared_ptr<core::Core> core, particles::ParticleSystem& ps)
		: m_ext_core(core)
		, m_internalParticleSystem(ps)
		, m_ext_graph(*core, ps.neighbourhoodGraph())
	{
	}

	std::vector<std::pair<DataPoint, size_t>> FacadeParticleSystem::originalCoordinates()
	{
		return m_internalParticleSystem.originalCoordinates();
	}

	std::vector<glm::vec4> FacadeParticleSystem::positions()
	{
		return m_internalParticleSystem.calculationData()->m_pos;
	};

	std::vector<glm::vec4> FacadeParticleSystem::colors()
	{
		return m_internalParticleSystem.calculationData()->m_col;
	}

	void FacadeParticleSystem::castParticleSystem(ICaster& caster)
	{
		
	};
	
	IGraph& FacadeParticleSystem::kNNGraph()
	{
		return m_ext_graph;
	}

	size_t FacadeParticleSystem::countAlive()
	{
		return m_internalParticleSystem.countAwakeParticles();
	}

	size_t FacadeParticleSystem::countParticles()
	{
		return m_internalParticleSystem.countParticles();
	}

	void FacadeParticleSystem::clear()
	{
	
		m_internalParticleSystem.clear();
	}

	bool FacadeParticleSystem::empty()
	{
		return m_internalParticleSystem.empty();
	}
}
