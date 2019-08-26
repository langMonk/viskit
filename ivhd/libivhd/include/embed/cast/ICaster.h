///
/// \author Bartosz Minch <minch@agh.edu.pl>
/// \date 18.04.2019
///

#pragma once

#include "particles/ParticleSystem.h"

namespace ivhd::embed::cast
{
	class ICaster
	{
		// public construction and destruction methods
	public:
		virtual void castParticle(particles::ParticleSystem& ps, size_t index) = 0;

		virtual void castParticleSystem(particles::ParticleSystem& ps) = 0;
	};
}