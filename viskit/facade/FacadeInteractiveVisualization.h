///
/// \author Bartosz Minch <minch@agh.edu.pl>
/// \date 18.04.2019
///

#pragma once

#include <vector>

#include <viskit/core/Core.h>
#include <viskit/viskit/IInteractiveVisualization.h>
#include <viskit/viskit/InteractiveVisualizationBuilder.h>
#include <viskit/viskit/ICaster.h>
#include <viskit/facade/FacadeResourceFactory.h>
#include <viskit/facade/FacadeParticleSystem.h>
#include <viskit/facade/FacadeParserCSV.h>

namespace viskit::facade
{
	/// <summary>
	/// Implementation of IVHD interface.
	/// </summary>
	class FacadeInteractiveVisualization final : public IInteractiveVisualization
	{
		// public construction and destruction methods
	public:
		explicit FacadeInteractiveVisualization(const LogHandler& logHandler);

        FacadeInteractiveVisualization(const FacadeInteractiveVisualization&) = delete;
        FacadeInteractiveVisualization(FacadeInteractiveVisualization&&) = delete;

        FacadeInteractiveVisualization& operator=(const FacadeInteractiveVisualization&) = delete;
        FacadeInteractiveVisualization& operator=(FacadeInteractiveVisualization&&) = delete;

		// public methods
	public:
		IResourceFactory& resourceFactory() override;
		
		[[nodiscard]] auto core() const -> std::shared_ptr<core::Core>;

		void subscribeOnCastingStepFinish(CasterEventHandler handler) override;
		
		void computeCastingStep(IParticleSystem& ps, IGraph& graph, ICaster& caster) override;

		std::vector<std::pair<float, float>> calculateBoundingBox() override;
		
		//private properties
	private:
		using CastingStepFinishedCallback = std::function<void(void)>;
		
		std::shared_ptr<core::Core> m_core;

		FacadeResourceFactory m_resourceFactory {*this};

		CastingStepFinishedCallback m_onCastingStepFinished = nullptr;
		
		bool m_castingRunning {false};
		
	};
}