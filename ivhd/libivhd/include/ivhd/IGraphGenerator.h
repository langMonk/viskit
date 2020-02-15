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
		virtual void generate(size_t nearestNeighbors, size_t furthestNeighbors, size_t randomNeighbors) = 0;

		/// <summary>
		/// Set if graph should be generated from cache (disk space) if possible, or not (regenerate whole graph).
		/// </summary>
		/// <param name="useCache"> True if graph was already generated. </param>
		virtual void useCache(bool useCache) = 0;
	};
}