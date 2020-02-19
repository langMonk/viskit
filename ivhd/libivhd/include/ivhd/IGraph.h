///
/// \author Bartosz Minch <minch@agh.edu.pl>
/// \date 10.02.2020
///

#pragma once

#include <ivhd/Structures.h>

namespace ivhd
{
	/// <summary>
	/// The public graph generator interface.
	/// </summary>
	class IGraph
	{
		// public methods 
	public:
		/// <summary>
		/// Get neighbors from graph for specified by index element.
		/// </summary>
		/// <param name="index"> Index of element for which get neighbor.</param>
		std::vector<Neighbors> virtual getNeighbors(size_t idx) = 0;

		/// <summary>
		/// Add one neighbor to graph.
		/// </summary>
		/// <param name="index"> Index of element to which add neighbor.</param>
		/// <param name="neighbors"> Neighbor to add.</param>
		void virtual addNeighbors(size_t index, Neighbors neighbor) = 0;

		/// <summary>
		/// Add vector of neighbors to graph.
		/// </summary>
		/// <param name="index"> Index of element to which add neighbors.</param>
		/// <param name="neighbors"> Neighbors to add.</param>
		void virtual addNeighbors(size_t index, std::vector<Neighbors> neighbors) = 0;

		/// <summary>
		/// Get neighbors count
		/// </summary>
		size_t virtual neighborsCount() = 0;

		/// <summary>
		/// Sort a graph
		/// </summary>
		void virtual sort() = 0;

		/// <summary>
		/// Dumping whole graph to readable plain text format (.txt).
		/// Only for debug purposes.
		/// </summary>
		/// <param name="filePath"> Filepath, where graph should be dumped.</param>
		/// <param name="fileName"> Filename.</param>
		void virtual dump(std::string filePath, std::string fileName) = 0;
	};
}