///
/// \author Bartosz Minch <minch@agh.edu.pl>
/// \date 04.05.2019
///

#include <exception>

#include "facade/FacadeParticleSystem.h"
#include "ivhd/ICaster.h"

namespace ivhd::facade
{ 
	FacadeParticleSystem::FacadeParticleSystem(core::ParticleSystem& system)
		: m_ext_particleSystem(system)
	{
	}

	std::vector<std::vector<float>> FacadeParticleSystem::originalCoordinates()
	{
		return m_ext_particleSystem.originalCoordinates();
	}

	ParticleData* FacadeParticleSystem::finalData()
	{
		return m_ext_particleSystem.finalData();
	}

	void FacadeParticleSystem::castData(std::shared_ptr<ICaster> caster)
	{
		caster->cast();
	}

	void FacadeParticleSystem::reduceData(IReducer& reducer)
	{
	}

	void FacadeParticleSystem::clusterData(IClusterer& clusterer)
	{
	}

}
