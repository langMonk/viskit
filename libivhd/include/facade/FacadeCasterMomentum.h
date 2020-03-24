///
/// \author Bartosz Minch <minch@agh.edu.pl>
/// \date 10.02.2020
///

#pragma once

#include "facade/FacadeCaster.h"
#include "embed/cast/ivhd/CasterMomentum.h"

namespace ivhd::facade
{
	/// <summary>
	/// Implementation of ICaster interface.
	/// </summary>
	class FacadeCasterMomentum : public FacadeCaster
	{
		// public construction and destruction methods
	public:

		explicit FacadeCasterMomentum(const std::shared_ptr<core::Core>& core);
		~FacadeCasterMomentum() = default;

		FacadeCasterMomentum(const FacadeCasterMomentum&) = delete;
		FacadeCasterMomentum(FacadeCasterMomentum&&) = delete;

		FacadeCasterMomentum& operator=(const FacadeCasterMomentum&) = delete;
		FacadeCasterMomentum& operator=(FacadeCasterMomentum&&) = delete;

		// public methods
	public:
		void calculatePositions(IParticleSystem& ps) override;

		void calculateForces(IParticleSystem& ps, IGraph& graph) override;

		CasterType type() override { return CasterType::IVHD; }
		
	};
}