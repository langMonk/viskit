///
/// \author Bartosz Minch <minch@agh.edu.pl>
/// \date 10.02.2020
///

#pragma once

#include <viskit/viskit/Structures.h>

namespace viskit {
/// <summary>
/// The public graph generator interface.
/// </summary>
class IGraph {
    // public methods
public:
    /// <summary>
    /// Initialize graph.
    /// </summary>
    /// <param name="size"> Size of initialization graph (equal to numbers of particles in system).</param>
    virtual void initialize(size_t size) = 0;

    /// <summary>
    /// Get neighbors from graph.
    /// </summary>
    /// <param name="index"> Index for which neighbor should be retrieved.</param>
    /// <returns> Neighbors assign to the specified neighbor. </returns>
    virtual std::vector<Neighbors> getNeighbors(size_t index) = 0;

    /// <summary>
    /// Add one neighbor to graph.
    /// </summary>
    /// <param name="neighbors"> Neighbor to add.</param>
    virtual void addNeighbors(Neighbors neighbors) = 0;

    /// <summary>
    /// Add vector of neighbors to graph.
    /// </summary>
    /// <param name="neighbors"> Neighbors to add.</param>
    virtual void addNeighbors(std::vector<Neighbors> neighbors) = 0;

    /// <summary>
    /// Get the neighbors counter
    /// </summary>
    /// Eg. We have NN=3, RN=1, Reverse=1, so the struct NeighborsCount = {3,1,1} will be returned.
    /// <returns> Number of overall different types of neighbors in graph structure. </returns>
    virtual viskit::NeighborsCounter neighborsCounter() = 0;

    /// <summary>
    /// Get overall neighbors count
    /// Eg. We have 7000 data points and we calculate 3 NN for each -> overallNeighborsCount() = 7000, size() = 21000
    /// </summary>
    /// <returns> Number of neighbors in graph structure. </returns>
    virtual size_t overallNeighborsCount() = 0;

    /// <summary>
    /// Get size of graph structure, for which NN was calculated.
    /// Eg. We have 7000 data points and we calculate 3 NN for each -> neighborsCount() = 7000, size() = 21000
    /// </summary>
    /// <returns> Size of graph structure. </returns>
    virtual size_t size() = 0;

    /// <summary>
    /// Sort a graph using indices.
    /// </summary>
    virtual void sort() = 0;

    /// <summary>
    /// Saves a graph to cache (disk space) after calculation.
    /// </summary>
    /// <param name="fileName"> Filename, where graph file should be located.</param>
    /// <returns> True if save operation succeed. </returns>
    virtual bool saveNearestNeighborsToCache(const std::string& fileName) = 0;

    /// <summary>
    /// Disable random neighbors in the graph.
    /// </summary>
    virtual void removeRandomNeighbors() = 0;

    /// <summary>
    /// Loads a graph from cache (disk space) and no recalculation is needed.
    /// </summary>
    /// <param name="fileName"> Filename, where graph file is located.</param>
    /// <param name="nearestNeighborsCountToRead"> Number of nearest neighbors that should be loaded into a graph structure.</param>
    /// <param name="binaryDistances"> If distances should be binary.</param>
    /// <returns> True if load operation succeed. </returns>
    virtual bool loadNearestNeighborsFromCache(const std::string& fileName, size_t nearestNeighborsCountToRead, bool binaryDistances) = 0;

    /// <summary>
    /// [DEBUG OPTION] Dumping whole graph to a readable plain text format (.txt).
    /// saveNearestNeighborsToCache saves graph as well, but is uses binary (non-readable) format.
    /// </summary>
    /// <param name="filePath"> Filepath, where graph should be dumped.</param>
    /// <param name="fileName"> Filename.</param>
    virtual void dump(std::string filePath, std::string fileName) = 0;

public:
    virtual ~IGraph() = default;
};
}