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
		virtual void castParticleSystem(std::shared_ptr<ivhd::IParticleSystem>& ps) = 0;

		/// <summary>
		/// Handles process of casting specific particle between spaces
		/// </summary>
		virtual void castParticle(std::shared_ptr<ivhd::IParticleSystem>& ps, size_t index) = 0;
	};
}