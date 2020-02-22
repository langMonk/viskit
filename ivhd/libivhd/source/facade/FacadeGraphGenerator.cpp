///
/// \author Bartosz Minch <minch@agh.edu.pl>
/// \date 10.02.2020
///

#include "facade/FacadeGraphGenerator.h"

namespace ivhd::facade
{
	FacadeGraphGenerator::FacadeGraphGenerator(std::shared_ptr<core::Core> core)
		: m_ext_core(core)
	{
	}
}
