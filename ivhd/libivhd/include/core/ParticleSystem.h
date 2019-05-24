///
/// \author Bartosz Minch <minch@agh.edu.pl>
/// \date 18.04.2019
///

#pragma once

#include <memory>
#include <vector>
#include <map>

#include "core/Logger.h"
#include "particles/ParticleData.h"
#include "particles/generate/ParticleGenerator.h"
#include "particles/emit/ParticleEmitter.h"
#include "particles/update/ParticleUpdater.h"

using namespace ivhd::particles;

namespace ivhd::core
{
		// public sub-types
	using CoordinatesContainer = std::vector<std::vector<float>>;

	class ParticleSystem
	{
		// public construction and destruction methods
	public:
		explicit ParticleSystem(OnLogAdded handler, size_t maxCount);
		virtual ~ParticleSystem() { }

		ParticleSystem(const ParticleSystem&) = delete;
		ParticleSystem& operator=(const ParticleSystem&) = delete;

		// public methods
	public:
		virtual size_t numAllParticles() const { return m_particles.m_count; }
		virtual size_t numAliveParticles() const { return m_particles.m_countAlive; }

		void addEmitter(std::shared_ptr<emit::ParticleEmitter> em) { m_emitters.push_back(em); }
		void addUpdater(std::shared_ptr<update::ParticleUpdater> up) { m_updaters.push_back(up); }

		CoordinatesContainer& originalCoordinates() { return m_originalCoordinates; }
		CoordinatesContainer& reducedCoordinates() { return m_reducedCoordinates; }
		ParticleData* finalData() { return &m_particles; }

		const Logger& logger() const { return m_logger; }
		Logger& logger() { return m_logger; }

		// private members
	private:
		Logger m_logger;

		CoordinatesContainer m_originalCoordinates;

		CoordinatesContainer m_reducedCoordinates;

		ParticleData m_particles;

		size_t m_count;

		std::vector<std::shared_ptr<emit::ParticleEmitter>> m_emitters;
		std::vector<std::shared_ptr<update::ParticleUpdater>> m_updaters;

	};
}