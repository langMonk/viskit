///
/// \author Bartosz Minch <minch@agh.edu.pl>
/// \date 18.02.2020
///

#pragma once

#include <viskit/facade/FacadeCaster.h>
#include <viskit/embed/cast/ivhd/CasterSGD.h>

namespace viskit::facade
{
	/// <summary>
	/// Implementation of ICaster interface.
	/// </summary>
	class FacadeCasterSGD : public FacadeCaster
	{
		// public construction and destruction methods
	public:

		explicit FacadeCasterSGD(const std::shared_ptr<core::Core>& core);
		~FacadeCasterSGD() = default;

		FacadeCasterSGD(const FacadeCasterSGD&) = delete;
		FacadeCasterSGD(FacadeCasterSGD&&) = delete;

		FacadeCasterSGD& operator=(const FacadeCasterSGD&) = delete;
		FacadeCasterSGD& operator=(FacadeCasterSGD&&) = delete;

		// public methods
	public:
		void calculatePositions(IParticleSystem& ps) override;

		void calculateForces(IParticleSystem& ps, IGraph& graph) override;

		CasterType type() override { return CasterType::IVHD; }
		
		OptimizerType optimizerType() override { return OptimizerType::SGD; }
		
		// private members
	};
}