///
/// \author Bartosz Minch <minch@agh.edu.pl>
/// \date 10.02.2020
///

#pragma once

#include "ivhd/IParticleSystem.h"
#include "ivhd/IGraphGenerator.h"
#include "facade/FacadeGraphGenerator.h"
#include "facade/FacadeParticleSystem.h"

namespace ivhd::facade
{
	/// <summary>
	/// Implementation of IGraphGenerator interface.
	/// </summary>
	class FacadeGraphGenerator : public IGraphGenerator
	{
		// public construction and destruction methods
	public:

		explicit FacadeGraphGenerator(std::shared_ptr<core::Core> core);
		~FacadeGraphGenerator() = default;

		FacadeGraphGenerator(const FacadeGraphGenerator&) = delete;
		FacadeGraphGenerator(FacadeGraphGenerator&&) = delete;

		FacadeGraphGenerator& operator=(const FacadeGraphGenerator&) = delete;
		FacadeGraphGenerator& operator=(FacadeGraphGenerator&&) = delete;

		// protected members
	protected:
		std::shared_ptr<core::Core> m_ext_core;

	};
}