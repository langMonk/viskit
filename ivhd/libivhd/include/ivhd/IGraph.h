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
	class IGraph
	{
		/// <summary>
		/// Get neighbors from graph with specified index.
		/// </summary>
		/// <param name="index"> Index of neighbors to get.</param>
		Neighbors virtual getNeighbors(size_t idx) = 0;

		/// <summary>
		/// Add neighbors to graph.
		/// </summary>
		/// <param name="neighbors"> Neighbors to add.</param>
		void virtual addNeighbors(Neighbors neighbors) = 0;

		/// <summary>
		/// Get neighbors count
		/// </summary>
		size_t virtual neighborsCount() = 0;

		/// <summary>
		/// Sort a graph
		/// </summary>
		void virtual sort() = 0;
	};
}