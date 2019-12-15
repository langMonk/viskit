///
/// \author Bartosz Minch <minch@agh.edu.pl>
/// \date 18.04.2019
///

#pragma once

#include <vector>
#include <memory>
#include "Structures.h"
#include "particles/ParticleData.h"
#include "graph/Point.h"

namespace ivhd
{
	class ICaster;
	class IReducer;
	class IClusterer;

	class IParticleSystem
	{

	public:
		/// <summary>
		/// Returns original coordinates.
		/// </summary>
		/// <returns> Container with data original coordinates.</returns>
		virtual std::vector<std::pair<graph::Point, size_t>> originalCoordinates() = 0;

		/// <summary>
		/// Returns current final data (after transformations).
		/// <returns> Container with current final data.</returns>
		virtual particles::ParticleData* availableData() = 0;

		/// <summary>
		/// Counts alive particles.
		/// <returns> Number of particles, that are currently alive.</returns>
		virtual size_t countAlive() = 0;

		/// <summary>
		/// Clears the particle system (if not empty).
		///
		virtual void clear() = 0;

		/// <summary>
		/// Checks if particles system is empty
		/// <returns> True if particle system is empty, false otherwise.</returns>
		virtual bool empty() = 0;
	};
}