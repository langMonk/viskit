///
/// \author Bartosz Minch <minch@agh.edu.pl>
/// \date 12.05.2019
///

#pragma once

#include "facade/FacadeCaster.h"
#include "ivhd/IParticleSystem.h"
#include "embed/cast/CasterRandom.h"

namespace ivhd::facade
{
	/// <summary>
	/// Implementation of ICaster interface.
	/// </summary>
	class FacadeCasterRandom : public FacadeCaster
	{
		// public construction and destruction methods
	public:

		explicit FacadeCasterRandom(std::shared_ptr<core::Core> core, particles::ParticleSystem& ps);
		~FacadeCasterRandom() = default;

		FacadeCasterRandom(const FacadeCasterRandom&) = delete;
		FacadeCasterRandom(FacadeCasterRandom&&) = delete;

		FacadeCasterRandom& operator=(const FacadeCasterRandom&) = delete;
		FacadeCasterRandom& operator=(FacadeCasterRandom&&) = delete;

		// public methods
	public:
		void castParticleSystem() override;

		void castParticle(size_t index) override;

		// private members
	private:
		std::shared_ptr<embed::cast::CasterRandom> m_internalCaster;
	};
}