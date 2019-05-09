///
/// \author Bartosz Minch <minch@agh.edu.pl>
/// \date 18.04.2019
///

#pragma once

#include "core/Core.h"
#include "ivhd/IInteractiveVizualization.h"
#include "ivhd/InteractiveVizualizationBuilder.h"
#include "facade/FacadeResourceFactory.h"

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
		void loadDataFile(std::string dataFilePath, IParser& parser) override;

		void castData(ICaster& caster) override;

		IResourceFactory& resourceFactory() override;

		std::shared_ptr<core::Core> core()
		{
			return m_core;
		}

		core::ParticleSystem& particleSystem()
		{
			return m_core->particleSystem();
		}

		//private properties
	private:
		std::shared_ptr<core::Core> m_core;
		facade::FacadeResourceFactory m_resourceFactory {*this};
	};
}