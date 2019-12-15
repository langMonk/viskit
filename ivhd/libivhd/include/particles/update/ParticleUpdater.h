///
/// \author Bartosz Minch <minch@agh.edu.pl>
/// \date 18.05.2019
///

#pragma once

#include "particles/ParticleData.h"
#include <vector>

namespace ivhd::particles::update
{ 
	class ParticleUpdater
	{
		// public construction and destruction methods
	public:
		ParticleUpdater() { }
		virtual ~ParticleUpdater() { }

		// public methods
	public:
		virtual void update(double dt, ParticleData* data) = 0;
	};

	class EulerUpdater : public ParticleUpdater
	{
		// public methods
	public:
		virtual void update(double dt, ParticleData* data) override;

		// public members
	public:
		glm::vec4 m_globalAcceleration{ 0.0f };
	};


	class FloorUpdater : public ParticleUpdater
	{
		// public methods
	public:
		virtual void update(double dt, ParticleData* data) override;

		// public members
	public:
		float m_floorY{ 0.0f };
		float m_bounceFactor{ 0.5f };
	};

	class AttractorUpdater : public ParticleUpdater
	{
		// public methods
	public:
		virtual void update(double dt, ParticleData* data) override;

		size_t collectionSize() const { return m_attractors.size(); }
		void add(const glm::vec4& attr) { m_attractors.push_back(attr); }
		glm::vec4& get(size_t id) { return m_attractors[id]; }

		// protected members
	protected:
		std::vector<glm::vec4> m_attractors;
	};

	class PosColorUpdater : public ParticleUpdater
	{
		// public methods
	public:
		virtual void update(double dt, ParticleData* data) override;

		// public members
	public:
		glm::vec4 m_minPos{ 0.0 };
		glm::vec4 m_maxPos{ 1.0 };
	};

	class VelColorUpdater : public ParticleUpdater
	{
		// public methods
	public:
		virtual void update(double dt, ParticleData* data) override;

		// public members
	public:
		glm::vec4 m_minVel{ 0.0 };
		glm::vec4 m_maxVel{ 1.0 };
	};
}