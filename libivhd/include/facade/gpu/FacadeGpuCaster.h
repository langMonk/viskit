///
/// \author Bartosz Minch <minch@agh.edu.pl>
/// \date 12.05.2019
///

#pragma once

#include "ivhd/IGpuCaster.h"
#include "facade/FacadeParticleSystem.h"
#include "facade/FacadeGraph.h"
#include "caster/caster_cuda.h"

namespace ivhd::facade::gpu
{
	/// <summary>
	/// Implementation of ICaster interface.
	/// </summary>
	class FacadeGpuCaster : public virtual IGpuCaster
	{
		// public construction and destruction methods
	public:

		explicit FacadeGpuCaster(std::shared_ptr<core::Core> core,
                    std::function<void(float)> onError,
                    std::function<void(vector<float2>&)> onPos);

		virtual ~FacadeGpuCaster() = default;

		FacadeGpuCaster(const FacadeGpuCaster&) = delete;
		FacadeGpuCaster(FacadeGpuCaster&&) = delete;

		FacadeGpuCaster& operator=(const FacadeGpuCaster&) = delete;
		FacadeGpuCaster& operator=(FacadeGpuCaster&&) = delete;

        void initialize(IParticleSystem& ps, IGraph& graph) override;
		void step() override;

		// protected members
	protected:
		std::shared_ptr<core::Core> m_ext_core;

		std::shared_ptr<CasterCuda> m_internalCaster;

		std::function<void(float)> m_onError;

		std::function<void(vector<float2>&)> m_onPos;
	};
}