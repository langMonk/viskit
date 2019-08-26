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
#include "threading/ThreadPool.h"
#include "math/IvhdMath.h"
#include "ICaster.h"

namespace ivhd::embed::cast
{
	class Caster : public virtual ICaster
	{
		// public construction and destruction methods
	public:
		Caster(core::System& system);
		virtual ~Caster() = default;

		Caster(const Caster&) = delete;
		Caster& operator=(const Caster&) = delete;

	protected:
		core::System& m_ext_system;

		bool m_casting{ false };

		float dtFactor{ 1.0f };

		float speedFactor{200};

		threading::ThreadPool m_threadPool;
	};
}