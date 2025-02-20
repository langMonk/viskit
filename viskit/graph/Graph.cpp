///
/// \author Bartosz Minch <minch@agh.edu.pl>
/// \date 18.02.2020
///
///

#include <algorithm>
#include <boost/algorithm/string.hpp>
#include <fstream>
#include <random>
#include <string>

#include <viskit/graph/Graph.h>

namespace viskit::graph {
Graph::Graph(core::System& system)
    : m_ext_system(system)
{
}

void Graph::initialize(size_t elements)
{
    m_data.resize(elements);
}

std::optional<std::vector<Neighbors>> Graph::getNeighbors(size_t index)
{
    if (!m_data.empty()) {
        return m_data[index];
    } else {
        m_ext_system.logger().logError("There is no neighbor item with passed index.");
        return {};
    }
}

std::optional<std::vector<size_t>> Graph::getAllNeighborsIndexes(size_t index)
{
    if (!m_data.empty()) {
        std::vector<size_t> indexes;
        const auto neighbors = m_data[index];
        indexes.reserve(neighbors.size());
        for (const auto neighbor : neighbors) {
            indexes.emplace_back(neighbor.j);
        }
        return indexes;
    } else {
        m_ext_system.logger().logError("There is no neighbor item with passed index.");
        return {};
    }
}

std::optional<std::vector<size_t>> Graph::getNearestNeighborsIndexes(size_t index)
{
    if (!m_data.empty()) {
        std::vector<size_t> indexes;
        const auto neighbors = m_data[index];
        for (const auto neighbor : neighbors) {
            if (neighbor.type == NeighborsType::Near) {
                indexes.emplace_back(neighbor.j);
            }
        }
        return indexes;
    } else {
        m_ext_system.logger().logError("There is no neighbor item with passed index.");
        return {};
    }
}

void Graph::addNeighbors(Neighbors neighbor)
{
    m_data[neighbor.i].emplace_back(neighbor);
}

void Graph::removeNeighbors(size_t i, size_t j)
{
    auto position = std::find_if(m_data[i].begin(), m_data[i].end(), [i, j](Neighbors neighbor) { return neighbor.i == i && neighbor.j == j; });
    if (position != m_data[i].end())
        m_data[i].erase(position);
}

void Graph::addNeighbors(const std::vector<Neighbors>& neighbors)
{
    for (const auto& neighbor : neighbors) {
        m_data[neighbor.i].emplace_back(neighbor);
    }
}

size_t Graph::overallNeighborsCount()
{
    size_t size { 0 };
    for (const auto& neighbors : m_data) {
        size += neighbors.size();
    }
    return size;
}

struct dist_compare {
    bool operator()(const Neighbors& distElem1, const Neighbors& distElem2) const
    {
        if (distElem1.i != distElem2.i) {
            return distElem1.i < distElem2.i;
        }
        return (distElem1.j < distElem2.j);
    }
};

void Graph::sort()
{
    auto const numberOfElements = m_data.size();
    auto const numberOfNeighbors = m_data[0].size();

    const auto from = numberOfNeighbors * numberOfElements;

    // sort graph (for every index)
    for (auto neighbors : m_data) {
        std::sort(neighbors.begin(), neighbors.end(), dist_compare());
    }

    // mark duplicates
    for (auto neighbors : m_data) {
        neighbors.erase(std::remove_if(neighbors.begin(), neighbors.end(), [](Neighbors elem) {
            return elem.type == NeighborsType::ToRemove;
        }),
            neighbors.end());
    }

    // remove duplicates
    for (size_t i = 0; i < numberOfElements; i++) {
        for (size_t j = 1; j < numberOfNeighbors; j++) {
            if (m_data[i][j].i == m_data[i][j - 1].i && m_data[i][j].j == m_data[i][j - 1].j)
                m_data[i][j].type = NeighborsType::ToRemove;
        }
    }

    const auto to = m_data[0].size() * m_data.size();
    m_ext_system.logger().logInfo("Sorted and size reduced: " + std::to_string(from) + "-->" + std::to_string(to));

    // calculate min and max distance
    float maxd;
    float mind = maxd = m_data[0][0].r;
    for (size_t i = 0; i < numberOfElements; i++) {
        for (size_t j = 1; j < numberOfNeighbors; j++) {
            if (mind > m_data[i][j].r)
                mind = m_data[i][j].r;
            if (maxd < m_data[i][j].r)
                maxd = m_data[i][j].r;
        }
    }
    m_ext_system.logger().logInfo("Min distance: " + std::to_string(mind) + ", max distance: " + std::to_string(maxd));
}

void Graph::clear()
{
    m_data.clear();
}

size_t Graph::size() const
{
    return m_data.size();
}

bool Graph::saveNearestNeighborsToCache(const std::string& fileName)
{
    m_ext_system.logger().logInfo("[Graph] Saving graph to cache...");

    std::ofstream file(fileName, std::ios::out | std::ios::binary);

    if (!file.good()) {
        m_ext_system.logger().logError("[Graph] File to save graph couldn't be created!");
        return false;
    }

    long testNum = 0x01020304;
    file.write(reinterpret_cast<char*>(&testNum), sizeof(long));

    auto graphSize = size();
    file.write(reinterpret_cast<char*>(&graphSize), sizeof(long));

    auto graphNeighborsCount = overallNeighborsCount() - neighborsCounter.randomNeighbors * size();
    file.write(reinterpret_cast<char*>(&graphNeighborsCount), sizeof(long));

    for (auto& neighbors : m_data) {
        for (auto& neighbor : neighbors) {
            if (neighbor.type != NeighborsType::Random) {
                file.write(reinterpret_cast<char*>(&neighbor), sizeof(Neighbors));
            }
        }
    }

    file.close();

    m_ext_system.logger().logInfo("[Graph] Finished.");

    return true;
}

bool Graph::loadNearestNeighborsFromCache(const std::string& fileName, size_t nearestNeighborsCountToRead, bool binaryDistances)
{
    m_ext_system.logger().logInfo("[Graph] Loading graph from cache...");

    std::ifstream input_file(fileName, std::ios::in | std::ios::binary);

    if (!input_file.good()) {
        m_ext_system.logger().logError("[Graph] File to read graph couldn't be opened!");
        return false;
    }

    // read header
    long firstLineMaxSize = 64;
    char firstLine[64];
    input_file.getline(firstLine, firstLineMaxSize);

    std::vector<std::string> splits;
    boost::split(splits, firstLine, [](char c) { return c == ';'; });

    assert(splits.size() == 3);

    const auto graphSize = stoi(splits[0]);
    const auto nearestNeighborsCount = stoi(splits[1]);
    const auto longSize = 8;
    m_data.resize(graphSize);

    auto validateNum = 0;
    input_file.read(reinterpret_cast<char*>(&validateNum), longSize);
    assert(validateNum == 0x01020304);

    neighborsCounter.nearestNeighbors = nearestNeighborsCountToRead;

    for (auto& element : m_data) {
        element.resize(nearestNeighborsCountToRead);
    }

    for (auto i = 0; i < graphSize; i++) {
        for (auto j = 0; j < nearestNeighborsCount; j++) {
            long data;
            float distance;
            input_file.read(reinterpret_cast<char*>(&data), longSize);
            input_file.read(reinterpret_cast<char*>(&distance), longSize / 2);
            assert(input_file.gcount() == 8 || input_file.gcount() == longSize / 2);

            if (j < nearestNeighborsCountToRead) {
                if (binaryDistances) distance = 0.0f;
                m_data[i][j] = Neighbors(i, data, distance, NeighborsType::Near);
            }
        }
    }

    input_file.close();

    m_ext_system.logger().logInfo("[Graph] Finished.");

    return true;
}

    void Graph::removeRandomNeighbors() {
        for (const auto& neighbors : m_data) {
            for (auto neighbor : neighbors){
                if (neighbor.type == NeighborsType::Random){
                    removeNeighbors(neighbor.i, neighbor.j);
                }
            }
        }
    }
}
