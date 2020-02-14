///
/// \author Bartosz Minch <minch@agh.edu.pl>
/// \date 10.02.2020
///

#pragma once

#include "particles/ParticleSystem.h"

namespace ivhd::graph::generate
{
	class IGraphGenerator
	{
		// public construction and destruction methods
	public:
		virtual void generate(particles::ParticleSystem& ps) = 0;
	};
}