//
// \author Dawid Dębowski <ddebowsk@student.agh.edu.pl>
// \date 21.05.2022.
//

#pragma once

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include "viskit/viskit/IGraph.h"
#include "viskit/viskit/Structures.h"

namespace viskit::python::bindings {
class PyGraphBinding : public IGraph {
public:
    void initialize(size_t size) override;
    std::vector<Neighbors> getNeighbors(size_t index) override;
    void addNeighbors(std::vector<Neighbors> neighbors) override;
    void addNeighbors(Neighbors neighbors) override;
    viskit::NeighborsCounter neighborsCounter() override;
    size_t overallNeighborsCount() override;
    size_t size() override;
    void sort() override;
    bool saveNearestNeighborsToCache(const std::string& fileName) override;
    void removeRandomNeighbors() override;
    bool loadNearestNeighborsFromCache(const std::string& fileName, size_t nearestNeighborsCountToRead, bool binaryDistances) override;
    void dump(std::string filePath, std::string fileName) override;
    void static bind(pybind11::module& m);
};
}