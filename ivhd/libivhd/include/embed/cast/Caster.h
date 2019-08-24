///
/// \author Bartosz Minch <minch@agh.edu.pl>
/// \date 18.04.2019
///

#pragma once

#include <thread>
#include <mutex>

#include "core/System.h"
#include "graph/Graph.h"
#include "particles/ParticleSystem.h"

namespace ivhd::embed::cast
{
	class Caster
	{
		// public construction and destruction methods
	public:
		Caster(core::System& system);
		virtual ~Caster();

		Caster(const Caster&) = delete;
		Caster& operator=(const Caster&) = delete;

		// protected methods
	protected:
		virtual void initialize();

		virtual void cast(particles::ParticleSystem& ps);

		virtual void casterThread(int start, int end, particles::ParticleSystem& ps);

		virtual void finalize();

		virtual void runCasting(particles::ParticleSystem& ps);

		virtual void stopCasting();


	protected:
		core::System& m_ext_system;

		bool m_casting;

		float dtFactor{ 1.0f };

		float speedFactor{200};

	};
}