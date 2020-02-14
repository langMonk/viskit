///
/// \author Bartosz Minch <minch@agh.edu.pl>
/// \date 18.04.2019
///

#pragma once

#include "IParticleSystem.h"

namespace ivhd
{
	class ICaster
	{
		// public methods 
	public:
		/// <summary>
		/// Handles process of casting particle system between spaces
		/// </summary>
		/// <param name="ps"> Particle system which should be casted by this caster.</param>
		virtual void castParticleSystem() = 0;

		/// <summary>
		/// Handles process of casting specific particle between spaces
		/// </summary>
		/// <param name="ps"> Particle system from which the particle should be casted.</param>
		/// <param name="index"> Index of a particle to cast</param>
		virtual void castParticle(size_t index) = 0;
	};
}