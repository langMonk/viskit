///
/// \author Bartosz Minch <minch@agh.edu.pl>
/// \date 12.05.2019
///

#pragma once

#include "facade/FacadeParticleSystem.h"
#include "facade/FacadeGraph.h"
#include "ivhd/ICaster.h"
#include "caster/caster_cuda.h"

namespace ivhd::facade::gpu
{
	/// <summary>
	/// Implementation of ICaster interface for GPU casting.
	/// </summary>
	class FacadeGpuCaster : public virtual ICaster
	{
		// public construction and destruction methods
	public:

		explicit FacadeGpuCaster(std::shared_ptr<core::Core> core);

		virtual ~FacadeGpuCaster() = default;

		FacadeGpuCaster(const FacadeGpuCaster&) = delete;
		FacadeGpuCaster(FacadeGpuCaster&&) = delete;

		FacadeGpuCaster& operator=(const FacadeGpuCaster&) = delete;
		FacadeGpuCaster& operator=(FacadeGpuCaster&&) = delete;

		void calculatePositions(IParticleSystem& ps) override;
		void calculateForces(IParticleSystem& ps, IGraph& graph) override;
        void initialize(IParticleSystem& ps, IGraph& graph) override;
		void step(IParticleSystem& ps, IGraph& graph) override;

		// protected members
	protected:
		std::shared_ptr<core::Core> m_ext_core;

		std::shared_ptr<CasterCuda> m_internalCaster;

		bool m_initialized {false};
	};
}