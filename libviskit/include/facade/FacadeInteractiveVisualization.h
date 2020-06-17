///
/// \author Bartosz Minch <minch@agh.edu.pl>
/// \date 18.04.2019
///

#pragma once

#include <vector>

#include "core/Core.h"
#include "viskit/IInteractiveVisualization.h"
#include "viskit/InteractiveVisualizationBuilder.h"
#include "viskit/ICaster.h"
#include "facade/FacadeResourceFactory.h"
#include "facade/FacadeParticleSystem.h"
#include "facade/FacadeParserCSV.h"

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
		
		void computePositions(IParticleSystem& ps, IGraph& graph, ICaster& caster) override;

		std::vector<std::pair<float, float>> calculateBoundingBox() override;
		
		//private properties
	private:
		using CastingStepFinishedCallback = std::function<void(void)>;
		
		std::shared_ptr<core::Core> m_core;

		FacadeResourceFactory m_resourceFactory {*this};

		CastingStepFinishedCallback m_onCastingStepFinished;
		
		bool m_castingRunning {false};
		
	};
}