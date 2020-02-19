///
/// \author Bartosz Minch <minch@agh.edu.pl>
/// \date 10.02.2020
///

#pragma once

#include "facade/FacadeCaster.h"
#include "embed/cast/ivhd/CasterAdadelta.h"

namespace ivhd::facade
{
	/// <summary>
	/// Implementation of ICaster interface.
	/// </summary>
	class FacadeCasterAdadelta : public FacadeCaster
	{
		// public construction and destruction methods
	public:

		explicit FacadeCasterAdadelta(std::shared_ptr<core::Core> core, particles::ParticleSystem& ps);
		~FacadeCasterAdadelta() = default;

		FacadeCasterAdadelta(const FacadeCasterAdadelta&) = delete;
		FacadeCasterAdadelta(FacadeCasterAdadelta&&) = delete;

		FacadeCasterAdadelta& operator=(const FacadeCasterAdadelta&) = delete;
		FacadeCasterAdadelta& operator=(FacadeCasterAdadelta&&) = delete;

		// public methods
	public:
		void castParticleSystem() override;

		void castParticle(size_t index) override;

		CasterType type() override { return CasterType::Adadelta; }

		// private members
	private:
		std::shared_ptr<embed::cast::ivhd::CasterAdadelta> m_internalCaster;
	};
}