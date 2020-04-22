#include "facade/gpu/FacadeGpuCasterMomentum.h"
#include "caster/caster_cuda_ab.h"

namespace ivhd::facade::gpu
{
	FacadeGpuCasterMomentum::FacadeGpuCasterMomentum(std::shared_ptr<core::Core> core,
					std::function<void(float)> onError,
                    std::function<void(vector<float2>&)> onPos)
		: FacadeGpuCaster(core, onError, onPos)

	{
		m_internalCaster = std::make_shared<CasterCudaAB>(10, onError, onPos);
	}
}