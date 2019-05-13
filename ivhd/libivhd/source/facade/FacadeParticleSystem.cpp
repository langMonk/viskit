///
/// \author Bartosz Minch <minch@agh.edu.pl>
/// \date 04.05.2019
///

#include "facade/FacadeParticleSystem.h"
#include "ivhd/ICaster.h"
#include "facade/FacadeInteractiveVizualization.h"

namespace ivhd::facade
{ 
	FacadeParticleSystem::FacadeParticleSystem(FacadeInteractiveVizualization& ivhd)
		: m_ext_ivhd(ivhd)
	{
	}

	std::vector<std::vector<float>> FacadeParticleSystem::originalCoordinates()
	{
		return m_ext_ivhd.core()->particleSystem().originalCoordinates();
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
