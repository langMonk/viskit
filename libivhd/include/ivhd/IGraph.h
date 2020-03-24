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
		/// <returns> Vector of neighbors assign to neighbor with index. <\returns>
		std::vector<Neighbors> virtual getNeighbors(size_t index) = 0;

		/// <summary>
		/// Add one neighbor to graph.
		/// </summary>
		/// <param name="neighbors"> Neighbor to add.</param>
		void virtual addNeighbors(Neighbors neighbors) = 0;

		/// <summary>
		/// Add vector of neighbors to graph.
		/// </summary>
		/// <param name="neighbors"> Neighbors to add.</param>
		void virtual addNeighbors(std::vector<Neighbors> neighbors) = 0;

		/// <summary>
		/// Get overall neighbors count
		/// </summary>
		/// <returns> Numer of neighbors in graph structure. <\returns>
		size_t virtual neighborsCount() = 0;

		/// <summary>
		/// Get size of graph structure, for which NN was calculated.
		/// Ex. We have 7000 data points and we calculate 3 NN for each -> neighorsCount() = 7000, size() = 21000
		/// </summary>
		/// <returns> Size of graph structure. <\returns>
		size_t virtual size() = 0;
		
		/// <summary>
		/// Sort a graph
		/// </summary>
		void virtual sort() = 0;

		/// <summary>
		/// Saves a graph to cache (disk space) after calculation.
		/// </summary>
		/// <param name="fileName"> Filename, where graph file should be located.</param>
		/// <returns> True if save operation succeded. <\returns>
		bool virtual saveToCache(const std::string& fileName) = 0;

		/// <summary>
		/// Loads a graph from cache (disk space) and no recalculation is needed.
		/// </summary>
		/// <param name="fileName"> Filename, where graph file is located.</param>
		/// <returns> True if load operation succeded. <\returns>
		bool virtual loadFromCache(const std::string& fileName) = 0;
		
		/// <summary>
		/// Dumping whole graph to a readable plain text format (.txt)> For debug purposes.
		/// saveToCache saves graph as well, but is uses binary (non-readable) format.
		/// </summary>
		/// <param name="filePath"> Filepath, where graph should be dumped.</param>
		/// <param name="fileName"> Filename.</param>
		void virtual dump(std::string filePath, std::string fileName) = 0;

	public:
		virtual ~IGraph() = default;

	};
}