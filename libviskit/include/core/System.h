///
/// \author Bartosz Minch <minch@agh.edu.pl>
/// \date 10.06.2019
///

#pragma once

#include "Logger.h"

namespace ivhd::core
{
	class System
	{
		// public construction and destruction methods
	public:
		explicit System(OnLogAdded logHandler);

		// public methods
	public:
		[[nodiscard]] const Logger& logger() const { return m_logger; }
		Logger& logger() { return m_logger; }

		// private properties
	private:
		Logger m_logger;

	};
}
