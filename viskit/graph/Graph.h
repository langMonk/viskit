///
/// \author Bartosz Minch <minch@agh.edu.pl>
/// \date 18.02.2020
///
///

#pragma once

#include <optional>

#include <viskit/core/System.h>
#include <viskit/viskit/Structures.h>

namespace viskit::graph {
class Graph {
    // public construction and destruction methods
public:
    explicit Graph(core::System& system);

    // public methods
public:
    void initialize(size_t elements);

    std::optional<std::vector<Neighbors>> getNeighbors(size_t index);

    std::optional<std::vector<size_t>> getAllNeighborsIndexes(size_t index);

    std::optional<std::vector<size_t>> getNearestNeighborsIndexes(size_t index);

    void addNeighbors(const std::vector<Neighbors>& neighbors);

    void addNeighbors(Neighbors neighbor);

    void removeNeighbors(size_t i, size_t j);

    size_t overallNeighborsCount();

    void sort();

    void removeRandomNeighbors();

    void clear();

    [[nodiscard]] size_t size() const;

    bool saveNearestNeighborsToCache(const std::string& fileName);

    bool loadNearestNeighborsFromCache(const std::string& fileName, size_t nearestNeighborsCountToRead, bool binaryDistances);

    NeighborsCounter neighborsCounter { 0, 0 };

    // private members
private:
    core::System& m_ext_system;

    std::vector<std::vector<Neighbors>> m_data;
};
}
