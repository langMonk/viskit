///
/// \author Bartosz Minch <minch@agh.edu.pl>
/// \date 17.05.2019
///

#include <viskit/facade/FacadeParser.h>

namespace viskit::facade
{
	FacadeParser::FacadeParser(const std::shared_ptr<core::Core> core)
		: m_ext_core(core)
	{
	}
}
