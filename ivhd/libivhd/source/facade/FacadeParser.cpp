#include "facade/FacadeParser.h"

namespace ivhd::facade
{
	FacadeParser::FacadeParser(std::shared_ptr<core::Core> core)
		: m_ext_core(core)
	{
	}
}
