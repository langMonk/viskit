///
/// \author Bartosz Minch <minch@agh.edu.pl>
/// \date 18.04.2019
///

#pragma once

#include "Logger.h"
#include "System.h"

namespace ivhd::core
{
	class Core
	{
		// public construction and destruction methods
	public:
		Core(OnLogAdded handler);

		// public methods
	public:
		Logger& logger() { return m_system.logger(); }

		System& system() { return m_system; }

	private:
		OnLogAdded m_logHandler;
		System m_system;
	};
}