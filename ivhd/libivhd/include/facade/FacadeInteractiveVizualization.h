///
/// \author Bartosz Minch <minch@agh.edu.pl>
/// \date 18.04.2019
///

#pragma once

#include "core/Core.h"
#include "ivhd/IInteractiveVizualization.h"
#include <memory>

namespace ivhd::facade
{
	/// <summary>
	/// Implementation of IVHD interface.
	/// </summary>
	class FacadeInteractiveVizualization : public IInteractiveVizualization
	{
		// public construction and destruction methods
	public:
		FacadeInteractiveVizualization();
		~FacadeInteractiveVizualization() = default;


		// public methods
	public:
		bool loadDataFile(std::string dataFilePath, IParser& parser) override;

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
	};
}