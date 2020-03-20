///
/// \author Bartosz Minch <minch@agh.edu.pl>
/// \date 20.02.2020
///

#pragma once

#include "facade/FacadeCaster.h"
#include "embed/cast/ivhd/CasterNesterov.h"

namespace ivhd::facade
{
	/// <summary>
	/// Implementation of ICaster interface.
	/// </summary>
	class FacadeCasterNesterov : public FacadeCaster
	{
		// public construction and destruction methods
	public:

		explicit FacadeCasterNesterov(const std::shared_ptr<core::Core>& core);
		~FacadeCasterNesterov() = default;

		FacadeCasterNesterov(const FacadeCasterNesterov&) = delete;
		FacadeCasterNesterov(FacadeCasterNesterov&&) = delete;

		FacadeCasterNesterov& operator=(const FacadeCasterNesterov&) = delete;
		FacadeCasterNesterov& operator=(FacadeCasterNesterov&&) = delete;

		// public methods
	public:
		void calculatePositions(IParticleSystem& ps) override;

		void calculateForces(IParticleSystem& ps, IGraph& graph) override;

		CasterType type() override { return CasterType::IVHD; }
		
	};
}