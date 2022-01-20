///
/// \author Bartosz Minch <minch@agh.edu.pl>
/// \date 12.05.2019
///

#pragma once

#include <viskit/facade/FacadeCaster.h>
#include <viskit/viskit/IParticleSystem.h>
#include <viskit/embed/cast/CasterRandom.h>

namespace viskit::facade
{
	/// <summary>
	/// Implementation of ICaster interface.
	/// </summary>
	class FacadeCasterRandom : public FacadeCaster
	{
		// public construction and destruction methods
	public:

		explicit FacadeCasterRandom(const std::shared_ptr<core::Core>& core);
		~FacadeCasterRandom() = default;

		FacadeCasterRandom(const FacadeCasterRandom&) = delete;
		FacadeCasterRandom(FacadeCasterRandom&&) = delete;

		FacadeCasterRandom& operator=(const FacadeCasterRandom&) = delete;
		FacadeCasterRandom& operator=(FacadeCasterRandom&&) = delete;

		// public methods
	public:
		void calculatePositions(IParticleSystem& ps) override;

		void calculateForces(IParticleSystem& ps, IGraph& graph) override {};

		CasterType type() override { return CasterType::Random; }

		OptimizerType optimizerType() override { return OptimizerType::None; }
	};
}