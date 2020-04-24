///
/// \author Bartosz Minch <minch@agh.edu.pl>
/// \date 20.04.2020
///

#pragma once

#include "facade/gpu/FacadeGpuCaster.h"

namespace ivhd::facade::gpu
{
	/// <summary>
	/// Implementation of ICaster interface.
	/// </summary>
	class FacadeGpuCasterMomentum : public FacadeGpuCaster
	{
		// public construction and destruction methods
	public:

		explicit FacadeGpuCasterMomentum(std::shared_ptr<core::Core> core);

		~FacadeGpuCasterMomentum() = default;

		FacadeGpuCasterMomentum(const FacadeGpuCasterMomentum&) = delete;
		FacadeGpuCasterMomentum(FacadeGpuCasterMomentum&&) = delete;

		FacadeGpuCasterMomentum& operator=(const FacadeGpuCasterMomentum&) = delete;
		FacadeGpuCasterMomentum& operator=(FacadeGpuCasterMomentum&&) = delete;

		// public methods
	public:
		CasterType type() override { return CasterType::IVHD; }

		OptimizerType optimizerType() override { return OptimizerType::Momentum; }
	};
}