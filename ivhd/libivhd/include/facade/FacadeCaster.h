///
/// \author Bartosz Minch <minch@agh.edu.pl>
/// \date 18.04.2019
///

#pragma once

#include "ivhd/ICaster.h"
#include "core/ParticleSystem.h"

namespace ivhd::facade
{
	/// <summary>
	/// Implementation of ICaster interface.
	/// </summary>
	class FacadeCaster : public ICaster
	{
		// public construction and destruction methods
	public:

		explicit FacadeCaster(core::ParticleSystem& system);
		~FacadeCaster() = default;

		FacadeCaster(const FacadeCaster&) = delete;
		FacadeCaster(FacadeCaster&&) = delete;

		FacadeCaster& operator=(const FacadeCaster&) = delete;
		FacadeCaster& operator=(FacadeCaster&&) = delete;

		// public methods
	public:


	};
}