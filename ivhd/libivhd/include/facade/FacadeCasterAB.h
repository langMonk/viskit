///
/// \author Bartosz Minch <minch@agh.edu.pl>
/// \date 10.02.2020
///

#pragma once

#include "facade/FacadeCaster.h"
#include "embed/cast/CasterAB.h"

namespace ivhd::facade
{
	/// <summary>
	/// Implementation of ICaster interface.
	/// </summary>
	class FacadeCasterAB : public FacadeCaster
	{
		// public construction and destruction methods
	public:

		explicit FacadeCasterAB(std::shared_ptr<core::Core> core, particles::ParticleSystem& ps);
		~FacadeCasterAB() = default;

		FacadeCasterAB(const FacadeCasterAB&) = delete;
		FacadeCasterAB(FacadeCasterAB&&) = delete;

		FacadeCasterAB& operator=(const FacadeCasterAB&) = delete;
		FacadeCasterAB& operator=(FacadeCasterAB&&) = delete;

		// public methods
	public:
		void castParticleSystem() override;

		void castParticle(size_t index) override;

		CasterType type() override { return CasterType::AB; }

		// private members
	private:
		std::shared_ptr<embed::cast::CasterAB> m_internalCaster;
	};
}