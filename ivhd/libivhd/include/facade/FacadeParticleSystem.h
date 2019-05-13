///
/// \author Bartosz Minch <minch@agh.edu.pl>
/// \date 04.05.2019
///

#pragma once

#include "ivhd/IParticleSystem.h"

namespace ivhd::facade
{
	class FacadeInteractiveVizualization;

	/// <summary>
	/// Implementation of ParticleSystem interface.
	/// </summary>
	class FacadeParticleSystem: public IParticleSystem
	{
		// public construction and destruction methods
	public:
		FacadeParticleSystem(FacadeInteractiveVizualization& ivhd);

		std::vector<std::vector<float>> originalCoordinates() override;

		void castData(std::shared_ptr<ICaster> caster) override;

		void reduceData(IReducer& reducer) override;

		void clusterData(IClusterer& clusterer) override;

	private:
		FacadeInteractiveVizualization& m_ext_ivhd;
	};
}