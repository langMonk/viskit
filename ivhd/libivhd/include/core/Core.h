///
/// \author Bartosz Minch <minch@agh.edu.pl>
/// \date 18.04.2019
///

#pragma once

#include "ParticleSystem.h"
#include "Logger.h"

namespace ivhd::core
{
	class Core
	{
		// public construction and destruction methods
	public:
		Core();

		const Logger& logger() const { return m_logger; }
		Logger& logger() { return m_logger; }

		ParticleSystem& particleSystem() { return m_system; }

	private:
		ParticleSystem m_system;
		Logger m_logger;
	};
}