///
/// \author Bartosz Minch <minch@agh.edu.pl>
/// \date 15.05.2019
///

#pragma once

#include <string>
#include "core/System.h"
#include "particles/ParticleSystem.h"

namespace ivhd::parse
{
	class Parser
	{
		// public construction and destruction methods
	public:
		Parser(core::System& system);

		Parser(const Parser&) = delete;
		Parser& operator=(const Parser&) = delete;

		// public methods
	public:
		virtual void finalize(particles::ParticleSystem& ps);

	protected:
		core::System& m_ext_system;
	};
}