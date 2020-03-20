///
/// \author Bartosz Minch <minch@agh.edu.pl>
/// \date 19.02.2020
///

#pragma once

#include "facade/FacadeCaster.h"
#include "embed/cast/ivhd/CasterAdam.h"

namespace ivhd::facade
{
	/// <summary>
	/// Implementation of ICaster interface.
	/// </summary>
	class FacadeCasterAdam : public FacadeCaster
	{
		// public construction and destruction methods
	public:

		explicit FacadeCasterAdam(const std::shared_ptr<core::Core>& core);
		~FacadeCasterAdam() = default;

		FacadeCasterAdam(const FacadeCasterAdam&) = delete;
		FacadeCasterAdam(FacadeCasterAdam&&) = delete;

		FacadeCasterAdam& operator=(const FacadeCasterAdam&) = delete;
		FacadeCasterAdam& operator=(FacadeCasterAdam&&) = delete;

		// public methods
	public:
		void calculatePositions(IParticleSystem& ps) override;

		void calculateForces(IParticleSystem& ps, IGraph& graph) override;

		CasterType type() override { return CasterType::IVHD; }
		
	};
}