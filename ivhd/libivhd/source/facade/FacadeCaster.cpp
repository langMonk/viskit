#include "facade\FacadeCaster.h"

namespace ivhd::facade
{
	FacadeCaster::FacadeCaster(std::shared_ptr<core::Core> core, particles::ParticleSystem& ps)
		: m_ext_core(core)
		, m_ext_particleSystem(ps)
	{
	}
}
