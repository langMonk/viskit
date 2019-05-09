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
		Core(OnLogAdded handler);

		// public methods
	public:

		bool load(std::string dataFilePath, IParser& parser);

		Logger& logger() { return m_particleSystem.logger(); }

		ParticleSystem& particleSystem() { return m_particleSystem; }

	private:
		ParticleSystem m_particleSystem;
		
	};
}