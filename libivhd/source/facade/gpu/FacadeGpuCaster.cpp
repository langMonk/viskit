#include <utility>

#include "facade/gpu/FacadeGpuCaster.h"


namespace ivhd::facade::gpu
{
	FacadeGpuCaster::FacadeGpuCaster(std::shared_ptr<core::Core> core,
                    std::function<void(float)> onError,
                    std::function<void(vector<float2>&)> onPos)
		: m_ext_core(std::move(core))
        , m_onError(onError)
        , m_onPos(onPos)
	{
	}

	void FacadeGpuCaster::step()
	{
		
	}

    void FacadeGpuCaster::initialize(IParticleSystem& ps, IGraph& graph)
	{
		
	}
}
