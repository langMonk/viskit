///
/// \author Bartosz Minch <minch@agh.edu.pl>
/// \date 18.04.2019
///

#pragma once

#include "core/Core.h"
#include "ivhd/IInteractiveVizualization.h"
#include "ivhd/InteractiveVizualizationBuilder.h"
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

		//private properties
	private:
		std::shared_ptr<core::Core> m_core;

		particles::ParticleSystem m_internalParticleSystem{ m_core->system() };
		
		FacadeParticleSystem m_particleSystem{ m_core, m_internalParticleSystem };
		FacadeResourceFactory m_resourceFactory {*this};
	};
}