///
/// \author Bartosz Minch <minch@agh.edu.pl>
/// \date 10.02.2020
///

#include <viskit/facade/FacadeGraphGenerator.h>

namespace viskit::facade
{
	FacadeGraphGenerator::FacadeGraphGenerator(std::shared_ptr<core::Core> core)
		: m_ext_core(core)
	{
	}
}
