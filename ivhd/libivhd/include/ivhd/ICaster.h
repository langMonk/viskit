///
/// \author Bartosz Minch <minch@agh.edu.pl>
/// \date 18.04.2019
///

#pragma once

#include "Structures.h"

namespace ivhd
{
	class IParticleSystem;
	class IGraph;

	class ICaster
	{
		// public methods 
	public:
		/// <summary>
		/// Handles process of casting particle system between spaces
		/// </summary>
		/// <param name="ps"> Particle system, which should be cased by this caster. </param>
		virtual void calculatePositions(IParticleSystem& ps) = 0;

		/// <summary>
		/// Handles process of casting specific particle between spaces
		/// </summary>
		/// <param name="ps"> Particle system, which should be cased by this caster. </param>
		/// <param name="graph"> Graph used for force calculations. </param>
		virtual void calculateForces(IParticleSystem& ps, IGraph& graph) = 0;

		/// <summary>
		/// Returns CasterType
		/// </summary>
		virtual CasterType type() = 0;
	};
}