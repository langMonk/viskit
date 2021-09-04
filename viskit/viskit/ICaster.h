///
/// \author Bartosz Minch <minch@agh.edu.pl>
/// \date 18.04.2019
///

#pragma once

#include <viskit/viskit/ITransformer.h>
#include <viskit/viskit/Structures.h>

namespace viskit
{
	class IParticleSystem;
	class IGraph;

	class ICaster : public virtual ITransformer
    {
		// public methods
    public:
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
		/// Returns the Caster Type
		/// </summary>
		virtual CasterType type() = 0;

		/// <summary>
		/// Returns the Optimizer Type
		/// </summary>
		virtual OptimizerType optimizerType() = 0;
	};
}