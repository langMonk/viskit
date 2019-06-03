///
/// \author Bartosz Minch <minch@agh.edu.pl>
/// \date 04.05.2019
///

#pragma once

#include "ivhd/IParticleSystem.h"
#include "core/Core.h"
#include "core/ParticleSystem.h"
#include "particles/ParticleData.h"

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
		FacadeParticleSystem(std::shared_ptr<core::Core> core);

		FacadeParticleSystem(const FacadeParticleSystem&) = delete;
		FacadeParticleSystem(FacadeParticleSystem&&) = delete;

		FacadeParticleSystem& operator=(const FacadeParticleSystem&) = delete;
		FacadeParticleSystem& operator=(FacadeParticleSystem&&) = delete;

		// public methods
	public:
		std::vector<std::vector<float>> originalCoordinates() override;

		ParticleData* finalData() override;

		size_t countAlive() override;

		void castData(std::shared_ptr<ICaster> caster) override;

		void reduceData(IReducer& reducer) override;

		void clusterData(IClusterer& clusterer) override;

	private:
		std::shared_ptr<core::ParticleSystem> m_internalParticleSystem;
	};
}