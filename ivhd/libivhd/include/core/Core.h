///
/// \author Bartosz Minch <minch@agh.edu.pl>
/// \date 18.04.2019
///

#pragma once

#include "ParticleSystem.h"
#include "Logger.h"
#include "ivhd/Structures.h"
#include "ivhd/IParser.h"

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

		void clusterParticles();

		void reduceParticles();

		void castParticles();

		void freezeParticle(Particle particle);

		void defrostParticle(Particle particle);

		const Logger& logger() const { return m_logger; }
		Logger& logger() { return m_logger; }

		ParticleSystem& particleSystem() { return m_system; }

	private:
		ParticleSystem m_system;
		Logger m_logger;
	};
}