///
/// \author Bartosz Minch <minch@agh.edu.pl>
/// \date 18.04.2019
///

#pragma once

#include <vector>

#include "core/Core.h"
#include "ivhd/IInteractiveVizualization.h"
#include "ivhd/InteractiveVizualizationBuilder.h"
#include "ivhd/ICaster.h"
#include "facade/FacadeResourceFactory.h"
#include "facade/FacadeParticleSystem.h"
#include "facade/FacadeParserCsv.h"

namespace ivhd::facade
{
	/// <summary>
	/// Implementation of IVHD interface.
	/// </summary>
	class FacadeInteractiveVizualization : public IInteractiveVizualization
	{
		// public construction and destruction methods
	public:
		FacadeInteractiveVizualization(LogHandler logHandler);

		// public methods
	public:
		IResourceFactory& resourceFactory() override;

		IParticleSystem& particleSystem() override;
		
		particles::ParticleSystem& internalParticleSystem();

		[[nodiscard]] auto core() const -> std::shared_ptr<core::Core>;

		void subscribeOnCastingStepFinish(CasterEventHandler handler) override;
		
		void currentCaster(std::shared_ptr<ivhd::ICaster> caster) override;

		void startCasting() override;
		
		void stopCasting() override;

		void pauseCasting() override;

		std::vector<std::pair<float, float>> calculateBoundingBox() override;
		
		//private properties
	private:
		using CastingStepFinishedCallback = std::function<void(void)>;
		
		std::shared_ptr<core::Core> m_core;

		particles::ParticleSystem m_internalParticleSystem{ m_core->system() };
		
		FacadeParticleSystem m_particleSystem{ m_core, m_internalParticleSystem };
		FacadeResourceFactory m_resourceFactory {*this};

		std::shared_ptr<ivhd::ICaster> m_currentCaster { nullptr };
		CastingStepFinishedCallback m_onCastingStepFinished;
		
		bool m_castingRunning {false};
		
	};
}