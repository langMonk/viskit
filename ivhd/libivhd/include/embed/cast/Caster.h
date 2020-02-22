///
/// \author Bartosz Minch <minch@agh.edu.pl>
/// \date 18.04.2019
///

#pragma once

#include "core/System.h"
#include "particles/ParticleSystem.h"
#include "threading/ThreadPool.h"

namespace ivhd::embed::cast
{
	class Caster
	{
		// public construction and destruction methods
	public:
		Caster(core::System& system);
		virtual ~Caster() = default;

		Caster(const Caster&) = delete;
		Caster& operator=(const Caster&) = delete;

		virtual void castParticleSystem(particles::ParticleSystem& ps, Graph& graph) {};

	protected:
		core::System& m_ext_system;
	};
}