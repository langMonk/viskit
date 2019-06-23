#include "core/System.h"

namespace ivhd::core
{ 
	System::System(OnLogAdded logHandler)
		: m_logger(logHandler)
	{
	}
}