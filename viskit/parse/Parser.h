///
/// \author Bartosz Minch <minch@agh.edu.pl>
/// \date 15.05.2019
///

#pragma once

#include <string>
#include <viskit/core/System.h>
#include <viskit/particles/ParticleSystem.h>

namespace viskit::parse
{
	class Parser
	{
		// public construction and destruction methods
	public:
		explicit Parser(core::System& system);

		Parser(const Parser&) = delete;
		Parser& operator=(const Parser&) = delete;

		// public methods
	public:
		virtual void finalize(particles::ParticleSystem& ps);

	protected:
		core::System& m_ext_system;
	};
}