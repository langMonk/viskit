///
/// \author Bartosz Minch <minch@agh.edu.pl>
/// \date 18.02.2020
///

#pragma once

#include "facade/FacadeCaster.h"
#include "embed/cast/CasterSGD.h"

namespace ivhd::facade
{
	/// <summary>
	/// Implementation of ICaster interface.
	/// </summary>
	class FacadeCasterSGD : public FacadeCaster
	{
		// public construction and destruction methods
	public:

		explicit FacadeCasterSGD(std::shared_ptr<core::Core> core, particles::ParticleSystem& ps);
		~FacadeCasterSGD() = default;

		FacadeCasterSGD(const FacadeCasterSGD&) = delete;
		FacadeCasterSGD(FacadeCasterSGD&&) = delete;

		FacadeCasterSGD& operator=(const FacadeCasterSGD&) = delete;
		FacadeCasterSGD& operator=(FacadeCasterSGD&&) = delete;

		// public methods
	public:
		void castParticleSystem() override;

		void castParticle(size_t index) override;

		CasterType type() override { return CasterType::MDS; }

		// private members
	private:
		std::shared_ptr<embed::cast::CasterSGD> m_internalCaster;
	};
}