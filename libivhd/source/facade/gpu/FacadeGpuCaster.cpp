#include <utility>

#include "facade/gpu/FacadeGpuCaster.h"


namespace ivhd::facade::gpu
{
	FacadeGpuCaster::FacadeGpuCaster(std::shared_ptr<core::Core> core)
		: m_ext_core(std::move(core))
	{
	}

	void FacadeGpuCaster::step()
	{
		if(m_initialized)
		{
			m_internalCaster->simul_step();
		}
	}

    void FacadeGpuCaster::initialize(IParticleSystem& ps, IGraph& graph)
	{
		std::function<void(float)> m_onError;
		std::function<void(vector<float2>&)> m_onPos;

		// TODO: create here actuall caster m_internalCaster

		m_initialized = true;
	}
}
