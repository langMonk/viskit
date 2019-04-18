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
		~FacadeInteractiveVizualization();


		// public methods
	public:
		std::shared_ptr<core::Core> core()
		{
			return m_core;
		}

		core::ParticleSystem& system()
		{
			return m_core->particleSystem();
		}

		//private properties
	private:
		std::shared_ptr<core::Core> m_core;
	};
}