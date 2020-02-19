///
/// \author Bartosz Minch <minch@agh.edu.pl>
/// \date 10.02.2020
///

#pragma once

#include "facade/FacadeCaster.h"
#include "embed/cast/ivhd/CasterForceDirected.h"

namespace ivhd::facade
{
	/// <summary>
	/// Implementation of ICaster interface.
	/// </summary>
	class FacadeCasterForceDirected : public FacadeCaster
	{
		// public construction and destruction methods
	public:

		explicit FacadeCasterForceDirected(std::shared_ptr<core::Core> core, particles::ParticleSystem& ps);
		~FacadeCasterForceDirected() = default;

		FacadeCasterForceDirected(const FacadeCasterForceDirected&) = delete;
		FacadeCasterForceDirected(FacadeCasterForceDirected&&) = delete;

		FacadeCasterForceDirected& operator=(const FacadeCasterForceDirected&) = delete;
		FacadeCasterForceDirected& operator=(FacadeCasterForceDirected&&) = delete;

		// public methods
	public:
		void castParticleSystem() override;

		void castParticle(size_t index) override;

		CasterType type() override { return CasterType::ForceDirected; }

		// private members
	private:
		std::shared_ptr<embed::cast::ivhd::CasterForceDirected> m_internalCaster;
	};
}