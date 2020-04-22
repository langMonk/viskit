#include "facade/gpu/FacadeGpuCasterMomentum.h"
#include "caster/caster_cuda_ab.h"

namespace ivhd::facade::gpu
{
	FacadeGpuCasterMomentum::FacadeGpuCasterMomentum(std::shared_ptr<core::Core> core)
		: FacadeGpuCaster(core)

	{
		m_internalCaster = nullptr;
	}
}