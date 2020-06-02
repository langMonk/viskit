///
/// \author Bartosz Minch <minch@agh.edu.pl>
/// \date 18.04.2019
///

#pragma once

#include <vector>
#include "Structures.h"
#include "glm/glm/glm.hpp"

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
        /// Get basic information, that concerns dataset loaded to this particle system.
        /// </summary>
        /// <returns> Dataset information.</returns>
        virtual DatasetInfo datasetInfo() = 0;

		/// <summary>
		/// Returns original coordinates.
		/// </summary>
		/// <returns> Container with data original coordinates.</returns>
		virtual std::vector<std::pair<DataPoint, size_t>> originalCoordinates() = 0;

		/// <summary>
		/// Returns labels associated with this dataset.
		/// </summary>
		/// <returns> Container with current particle labels.</returns>
		virtual std::vector<size_t> labels() = 0;

		/// <summary>
		/// Returns current positions.
		/// </summary>
		/// <returns> Container with current particle positions.</returns>
		virtual std::vector<glm::vec4> positions() = 0;

		/// <summary>
		/// Returns current forces.
		/// </summary>
		/// <returns> Container with current particle forces.</returns>
		virtual std::vector<glm::vec4> forces() = 0;

		/// <summary>
		/// Returns current velocities.
		/// </summary>
		/// <returns> Container with current particle velocities.</returns>
		virtual std::vector<glm::vec4> velocities() = 0;

		/// <summary>
		/// Returns colors associated with each particle.
		/// </summary>
		/// <returns> Container with colors.</returns>
		virtual std::vector<glm::vec4> colors() = 0;
		
		/// <summary>
		/// Sets the specified particle position.
		/// </summary>
		/// <param="index"> Index of particle for which we want to set new coordinates. </param>
		/// <param="x"> X coordinate. </param>
		/// <param="y"> Y coordinate. </param>
		virtual void setPosition(size_t index, float x, float y) = 0;

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
		/// Checks if particles system is empty.
		/// </summary>
		/// <returns> True if particle system is empty, false otherwise.</returns>
		virtual bool empty() = 0;

		virtual ~IParticleSystem() = default;
	};
}