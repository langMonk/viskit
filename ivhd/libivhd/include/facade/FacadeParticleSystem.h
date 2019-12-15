///
/// \author Bartosz Minch <minch@agh.edu.pl>
/// \date 04.05.2019
///

#pragma once

#include "ivhd/IParticleSystem.h"
#include "core/Core.h"
#include "particles/ParticleSystem.h"

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
		std::vector<std::pair<graph::DataPoint, size_t>> originalCoordinates() override;

		std::shared_ptr<particles::ParticleSystem> internalParticleSystem() const;

		particles::ParticleData* availableData() override;

		size_t countAlive() override;

		void clear() override;

		bool empty() override;

	private:
		std::shared_ptr<particles::ParticleSystem> m_internalParticleSystem;
	};
}