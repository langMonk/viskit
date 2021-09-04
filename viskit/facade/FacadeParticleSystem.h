///
/// \author Bartosz Minch <minch@agh.edu.pl>
/// \date 04.05.2019
///

#pragma once

#include <viskit/viskit/IParticleSystem.h>
#include <viskit/viskit/IGraph.h>
#include <viskit/core/Core.h>
#include <viskit/graph/DataPoint.h>
#include <viskit/particles/ParticleSystem.h>

namespace viskit::facade
{
	class FacadeInteractiveVizualization;

	/// <summary>
	/// Implementation of ParticleSystem interface.
	/// </summary>
	class FacadeParticleSystem final : public IParticleSystem
	{
		// public construction and destruction methods
	public:
		explicit FacadeParticleSystem(const std::shared_ptr<core::Core>& core);

		FacadeParticleSystem(const FacadeParticleSystem&) = delete;
		FacadeParticleSystem(FacadeParticleSystem&&) = delete;

		FacadeParticleSystem& operator=(const FacadeParticleSystem&) = delete;
		FacadeParticleSystem& operator=(FacadeParticleSystem&&) = delete;

		[[nodiscard]] particles::ParticleSystem& internalSystem() const { return *m_internalParticleSystem; }

		// public methods
	public:
        DatasetInfo datasetInfo() override;

		std::vector<std::pair<DataPoint, size_t>> originalCoordinates() override;

        glm::vec4* positions() override;

        glm::vec4* velocities() override;

        glm::vec4* forces() override;

        glm::vec4* colors() override;

		std::vector<size_t> labels() override;
	
		void setPosition(size_t index, float x, float y) override;

		size_t countAlive() override;

		size_t countParticles() override;

		void clear() override;

		bool empty() override;

		bool saveToFile(const std::string& fileName) override;

	private:
		std::shared_ptr<core::Core> m_ext_core;

		std::shared_ptr<particles::ParticleSystem> m_internalParticleSystem;
	};
}
