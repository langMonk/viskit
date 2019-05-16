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
		void loadDataFile(std::string dataFilePath, std::shared_ptr<IParser> parser) override;

		IResourceFactory& resourceFactory() override;

		IParticleSystem& particleSystem() override;

		std::shared_ptr<core::Core> core()
		{
			return m_ext_core;
		}

		//private properties
	private:
		std::shared_ptr<core::Core> m_ext_core;
		facade::FacadeResourceFactory m_resourceFactory {*this};
		facade::FacadeParticleSystem m_particleSystem {*this};
	};
}