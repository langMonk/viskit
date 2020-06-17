#include <utility>
#include "core/System.h"

namespace viskit::core
{ 
	System::System(OnLogAdded logHandler)
		: m_logger(std::move(logHandler))
	{
	}
}