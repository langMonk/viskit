///
/// \author Bartosz Minch <minch@agh.edu.pl>
/// \date 04.05.2019
///

#pragma once

#include "ivhd/IParticleSystem.h"
#include "ivhd/IGraph.h"
#include "core/Core.h"
#include "graph/DataPoint.h"
#include "particles/ParticleSystem.h"
#include "FacadeGraph.h"

namespace ivhd::facade
{
	class FacadeInteractiveVizualization;

	/// <summary>
	/// Implementation of ParticleSystem interface.
	/// </summary>
	class FacadeParticleSystem final : public IParticleSystem
	{
		// public construction and destruction methods
	public:
		FacadeParticleSystem(std::shared_ptr<core::Core> core);

		FacadeParticleSystem(const FacadeParticleSystem&) = delete;
		FacadeParticleSystem(FacadeParticleSystem&&) = delete;

		FacadeParticleSystem& operator=(const FacadeParticleSystem&) = delete;
		FacadeParticleSystem& operator=(FacadeParticleSystem&&) = delete;

		~FacadeParticleSystem() = default;
		
		particles::ParticleSystem& internalSystem() { return *m_internalParticleSystem.get(); }

		// public methods
	public:
		std::vector<std::pair<DataPoint, size_t>> originalCoordinates() override;

		std::vector<glm::vec4> positions() override;

		std::vector<glm::vec4> velocities() override;

		std::vector<glm::vec4> forces() override;

		std::vector<glm::vec4> colors() override;
	
		size_t countAlive() override;

		size_t countParticles() override;

		void clear() override;

		bool empty() override;

	private:
		std::shared_ptr<core::Core> m_ext_core;

		std::shared_ptr<particles::ParticleSystem> m_internalParticleSystem;
	};
}
