///
/// \author Bartosz Minch <minch@agh.edu.pl>
/// \date 10.02.2020
///

#include <fstream>

#include <viskit/facade/FacadeGraph.h>

namespace viskit::facade {
FacadeGraph::FacadeGraph(const std::shared_ptr<core::Core>& core)
    : m_ext_core(core)
    , m_internalGraph(std::make_shared<graph::Graph>(core->system()))
{
}

std::vector<Neighbors> FacadeGraph::getNeighbors(size_t idx)
{
    try {
        if (const auto neighbors = m_internalGraph->getNeighbors(idx)) {
            return *neighbors;
        }
    } catch (std::exception& exception) {
        std::string message = "Failed to get the neighbors from the graph: ";
        message += exception.what();
        m_ext_core->logger().logWarning(message);
    }
    return {};
}

void FacadeGraph::addNeighbors(Neighbors neighbors)
{
    try {
        m_internalGraph->addNeighbors(neighbors);
    } catch (std::exception& exception) {
        std::string message = "Failed to add the neighbor to the graph: ";
        message += exception.what();
        m_ext_core->logger().logWarning(message);
    }
}

void FacadeGraph::addNeighbors(std::vector<Neighbors> neighbors)
{
    try {
        m_internalGraph->addNeighbors(neighbors);
    } catch (std::exception& exception) {
        std::string message = "Failed to add the neighbors to the graph: ";
        message += exception.what();
        m_ext_core->logger().logWarning(message);
    }
}

void FacadeGraph::removeRandomNeighbors()
{
    try {
        m_internalGraph->removeRandomNeighbors();
    } catch (std::exception& exception) {
        std::string message = "Failed to remove random. ";
        message += exception.what();
        m_ext_core->logger().logWarning(message);
    }
}

size_t FacadeGraph::overallNeighborsCount()
{
    try {
        return m_internalGraph->overallNeighborsCount();
    } catch (std::exception& exception) {
        std::string message = "Failed to get the number of neighbors currently in the graph: ";
        message += exception.what();
        m_ext_core->logger().logWarning(message);
    }
    return size_t {};
}

NeighborsCounter FacadeGraph::neighborsCounter()
{
    try {
        return m_internalGraph->neighborsCounter;
    } catch (std::exception& exception) {
        std::string message = "Failed to get the number of different types of neighbors: ";
        message += exception.what();
        m_ext_core->logger().logWarning(message);
    }
    return NeighborsCounter();
}

size_t FacadeGraph::size()
{
    try {
        return m_internalGraph->size();
    } catch (std::exception& exception) {
        std::string message = "Failed to get the size of graph: ";
        message += exception.what();
        m_ext_core->logger().logWarning(message);
    }
    return size_t {};
}

void FacadeGraph::sort()
{
    try {
        m_internalGraph->sort();
    } catch (std::exception& exception) {
        std::string message = "Failed to sort the graph: ";
        message += exception.what();
        m_ext_core->logger().logWarning(message);
    }
}

bool FacadeGraph::saveNearestNeighborsToCache(const std::string& fileName)
{
    try {
        return m_internalGraph->saveNearestNeighborsToCache(fileName);
    } catch (std::exception& exception) {
        std::string message = "Failed to save graph to cache: ";
        message += exception.what();
        m_ext_core->logger().logWarning(message);
    }
    return false;
}

bool FacadeGraph::loadNearestNeighborsFromCache(const std::string& fileName, size_t nearestNeighborsCountToRead, bool binaryDistances)
{
    try {
        return m_internalGraph->loadNearestNeighborsFromCache(fileName, nearestNeighborsCountToRead, binaryDistances);
    } catch (std::exception& exception) {
        std::string message = "Failed to load graph from cache: ";
        message += exception.what();
        m_ext_core->logger().logWarning(message);
    }
    return false;
}

void FacadeGraph::dump(std::string filePath, std::string fileName)
{
    std::ofstream m_file;

    try {
        m_file.open(filePath + "\\" + fileName + ".txt");
        for (int i = 0; i < m_internalGraph->size(); i++) {
            if (const auto neighbors = m_internalGraph->getNeighbors(i)) {
                for (const auto neighbor : *neighbors) {
                    if (neighbor.type == NeighborsType::Near) {
                        m_file << neighbor.i << "," << neighbor.j << "," << neighbor.r << ","
                               << "Near" << std::endl;
                    } else if (neighbor.type == NeighborsType::Far) {
                        m_file << neighbor.i << "," << neighbor.j << "," << neighbor.r << ","
                               << "Far" << std::endl;
                    } else {
                        m_file << neighbor.i << "," << neighbor.j << "," << neighbor.r << ","
                               << "Random" << std::endl;
                    }
                }
            }
        }

        m_file.close();
    } catch (std::exception& exception) {
        std::string message = "Failed to dump graph to plain text file: ";
        message += exception.what();
        m_ext_core->logger().logWarning(message);
        m_file.close();
    }
}

void FacadeGraph::initialize(size_t size)
{
    m_internalGraph->initialize(size);
}
}
