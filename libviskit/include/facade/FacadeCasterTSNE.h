#pragma once

#include "facade/FacadeCaster.h"
#include "viskit/IParticleSystem.h"
#include "embed/cast/ivhd/CasterTSNE.h"

namespace viskit::facade
{
	/// <summary>
	/// Implementation of ICaster interface.
	/// </summary>
	class FacadeCasterTSNE : public FacadeCaster
	{
		// public construction and destruction methods
	public:

		explicit FacadeCasterTSNE(std::shared_ptr<core::Core> core);
		~FacadeCasterTSNE() = default;

		FacadeCasterTSNE(const FacadeCasterTSNE&) = delete;
		FacadeCasterTSNE(FacadeCasterTSNE&&) = delete;

		FacadeCasterTSNE& operator=(const FacadeCasterTSNE&) = delete;
		FacadeCasterTSNE& operator=(FacadeCasterTSNE&&) = delete;

		// public methods
	public:
		void calculatePositions(IParticleSystem& ps) override;

		void calculateForces(IParticleSystem& ps, IGraph& graph) override;

		CasterType type() override { return CasterType::IVHD; }

		OptimizerType optimizerType() override { return OptimizerType::tSNE; }
	};
}