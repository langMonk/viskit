///
/// \author Bartosz Minch <minch@agh.edu.pl>
/// \date 10.02.2020
///

#pragma once

namespace ivhd
{
	/// <summary>
	/// The public graph generator interface.
	/// </summary>
	class IGraphGenerator
	{
		// public methods 
	public:
		/// <summary>
		/// Generate a graph using specified method
		/// </summary>
		/// <param name="nearestNeighbors"> Number of nearest neighbors, which should be calculated in this graph.</param>
		/// <param name="furthestNeighbors"> Number of furthest neighbors, which should be calculated in this graph.</param>
		/// <param name="randomNeighbors"> Number of random neighbors, which should be calculated in this graph.</param>
		/// <param name="distancesEqualOne"> If true all distances while generating graph are set to 1.</param>
		virtual void generate(size_t nearestNeighbors, size_t furthestNeighbors, size_t randomNeighbors, bool distancesEqualOne) = 0;
	};
}