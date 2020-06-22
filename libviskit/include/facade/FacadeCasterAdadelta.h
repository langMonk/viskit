///
/// \author Bartosz Minch <minch@agh.edu.pl>
/// \date 19.02.2020
///

#pragma once

#include "facade/FacadeCaster.h"
#include "embed/cast/ivhd/CasterAdadelta.h"

namespace viskit::facade
{
	/// <summary>
	/// Implementation of ICaster interface.
	/// </summary>
	class FacadeCasterAdadelta : public FacadeCaster
	{
		// public construction and destruction methods
	public:

		explicit FacadeCasterAdadelta(const std::shared_ptr<core::Core>& core);
		~FacadeCasterAdadelta() = default;

		FacadeCasterAdadelta(const FacadeCasterAdadelta&) = delete;
		FacadeCasterAdadelta(FacadeCasterAdadelta&&) = delete;

		FacadeCasterAdadelta& operator=(const FacadeCasterAdadelta&) = delete;
		FacadeCasterAdadelta& operator=(FacadeCasterAdadelta&&) = delete;

		// public methods
	public:
		void calculatePositions(IParticleSystem& ps) override;

		void calculateForces(IParticleSystem& ps, IGraph& graph) override;

		CasterType type() override { return CasterType::IVHD; }

		OptimizerType optimizerType() override { return OptimizerType::Adadelta; }
		
	private:
		float energy{ 0.1f };

	};
}