///
/// \author Bartosz Minch <minch@agh.edu.pl>
/// \date 18.04.2019
///

#pragma once

#include "core/System.h"
#include "graph/Graph.h"

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

		virtual void finalize();

	protected:
		core::System& m_ext_system;

		float dtFactor{ 1.0f };

		float speedFactor{200};
	};
}