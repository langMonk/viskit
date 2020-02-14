///
/// \author Bartosz Minch <minch@agh.edu.pl>
/// \date 18.04.2019
///

#pragma once

#include <vector>

#include "particles/ParticleData.h"
#include "ivhd/Structures.h"

namespace ivhd
{
	class ICaster;
	class IReducer;
	class IClusterer;
	class IGraph;

	class IParticleSystem
	{
	public:
		/// <summary>
		/// Returns original coordinates.
		/// </summary>
		/// <returns> Container with data original coordinates.</returns>
		virtual std::vector<std::pair<DataPoint, size_t>> originalCoordinates() = 0;

		/// <summary>
		/// Returns current positions (after transformations).
		/// </summary>
		/// <returns> Container with current particle positions.</returns>
		virtual std::vector<glm::vec4> positions() = 0;

		/// <summary>
		/// Returns colors of each particle.
		/// </summary>
		/// <returns> Container with colors for each particle.</returns>
		virtual std::vector<glm::vec4> colors() = 0;
		
		/// <summary>
		/// Get already calculated with kNNGenerator Graph (based on this particle system).
		/// </summary>
		/// <returns> Calculated kNN Graph. </returns>
		virtual IGraph& kNNGraph() = 0;
		
		/// <summary>
		/// Counts alive particles.
		/// </summary>
		/// <returns> Number of particles, that are currently alive.</returns>
		virtual size_t countAlive() = 0;

		/// <summary>
		/// Count particles.
		/// </summary>
		/// <returns> Number of particles in the system.</returns>
		virtual size_t countParticles() = 0;

		/// <summary>
		/// Clears the particle system (if not empty).
		/// </summary>
		virtual void clear() = 0;

		/// <summary>
		/// Casts the particle system (if not empty).
		/// </summary>
		virtual void castParticleSystem(ICaster& caster) = 0;
		
		/// <summary>
		/// Checks if particles system is empty.
		/// </summary>
		/// <returns> True if particle system is empty, false otherwise.</returns>
		virtual bool empty() = 0;

		virtual ~IParticleSystem() = default;
	};
}