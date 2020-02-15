///
/// \author Bartosz Minch <minch@agh.edu.pl>
/// \date 18.04.2019
///

#pragma once

#include "core/System.h"
#include "ivhd/IGraphGenerator.h"
#include "particles/ParticleSystem.h"

namespace ivhd::graph::generate
{
	class GraphGenerator : public virtual IGraphGenerator
	{
		// public construction and destruction methods
	public:
		GraphGenerator(core::System& system, particles::ParticleSystem& ps);
		virtual ~GraphGenerator() = default;

		GraphGenerator(const GraphGenerator&) = delete;
		GraphGenerator& operator=(const GraphGenerator&) = delete;

	protected:
		core::System& m_ext_system;

		particles::ParticleSystem& m_ext_particleSystem;
	};
}
