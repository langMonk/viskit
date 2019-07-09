#include "facade\FacadeCaster.h"

namespace ivhd::facade
{
	FacadeCaster::FacadeCaster(std::shared_ptr<core::Core> core)
		: m_ext_core(core)
	{
	}
}
