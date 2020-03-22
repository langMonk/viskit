///
/// \author Bartosz Minch <minch@agh.edu.pl>
/// \date 18.03.2020
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

		explicit FacadeCasterForceDirected(const std::shared_ptr<core::Core>& core);
		~FacadeCasterForceDirected() = default;

		FacadeCasterForceDirected(const FacadeCasterForceDirected&) = delete;
		FacadeCasterForceDirected(FacadeCasterForceDirected&&) = delete;

		FacadeCasterForceDirected& operator=(const FacadeCasterForceDirected&) = delete;
		FacadeCasterForceDirected& operator=(FacadeCasterForceDirected&&) = delete;

		// public methods
	public:
		void calculatePositions(IParticleSystem& ps) override;

		void calculateForces(IParticleSystem& ps, IGraph& graph) override;

		CasterType type() override { return CasterType::IVHD; }

	};
}