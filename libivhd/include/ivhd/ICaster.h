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
		/// [Optional] Initialization process, which uses particle system and graph. Necessary for GPU casters.
		/// </summary>
		/// <param name="ps"> Particle system, which contains positions that should be initialized. </param>
		/// <param name="graph"> Graph, which contains distances that should be initialized. </param>
		virtual void initialize(ivhd::IParticleSystem& ps, ivhd::IGraph& graph) = 0;

		/// <summary>
		/// Handles process of position calculation.
		/// </summary>
		/// <param name="ps"> Particle system for which positions should be calculated. </param>
		virtual void calculatePositions(IParticleSystem& ps) = 0;

		/// <summary>
		/// Handles process of force calculation.
		/// </summary>
        /// <param name="ps"> Particle system for which forces should be calculated. </param>
        /// <param name="graph"> kNN graph used for calculations. </param>
		virtual void calculateForces(IParticleSystem& ps, IGraph& graph) = 0;

		/// <summary>
		/// Handles casting step (usually just call calculatePositions and calculateForces)
		/// </summary>
		/// <param name="ps"> Particle system, which should be casted. </param>
		/// <param name="graph"> Graph used for casting. </param>
		virtual void step(IParticleSystem& ps, IGraph& graph) = 0;

		/// <summary>
		/// Returns Caster Type
		/// </summary>
		virtual CasterType type() = 0;

		/// <summary>
		/// Returns Optimizer Type
		/// </summary>
		virtual OptimizerType optimizerType() = 0;

        /// <summary>
		/// Process, which occurs when casting is finished.
		/// </summary>
		virtual void finalize() = 0;
	};
}