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

	class IGpuCaster
	{
		// public methods 
	public:
		/// <summary>
		/// [Optional] Initialization process, which uses particle system and graph.
		/// </summary>
		/// <param name="ps"> Particle system, which should be casted by this caster. </param>
		/// <param name="graph"> Graph used for force calculations. </param>
		virtual void initialize(IParticleSystem& ps, IGraph& graph) = 0;

		/// <summary>
		/// Perform a step of casting (usally just calls calculate Positions and Forces)
		/// </summary>
		virtual void step() = 0;

		/// <summary>
		/// Returns CasterType
		/// </summary>
		virtual CasterType type() = 0;
	};
}