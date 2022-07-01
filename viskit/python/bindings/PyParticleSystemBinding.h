//
// \author Dawid Dębowski <ddebowsk@student.agh.edu.pl>
// \date 21.05.2022.
//

#pragma once

#include <pybind11/pybind11.h>

#include "viskit/viskit/IParticleSystem.h"
#include "viskit/viskit/Structures.h"
#include "viskit/facade/FacadeParticleSystem.h"
#include "viskit/viskit/IGraph.h"

namespace viskit::python::bindings
{
    class PyParticleSystemBinding: public IParticleSystem {

    public:
        using IParticleSystem::IParticleSystem;

        DatasetInfo datasetInfo() override;

        std::vector<std::pair<DataPoint, size_t>> originalCoordinates() override;

        std::vector<size_t> labels() override;

        std::vector<viskit::vec4> positions() override;

        std::vector<viskit::vec4> forces() override;

        std::vector<viskit::vec4> velocities() override;

        std::vector<viskit::vec4> colors() override;

        void setPosition(size_t index, float x, float y) override;

        size_t countAlive() override;

        size_t countParticles() override;

        void clear() override;

        bool empty() override;

        bool saveToFile(const std::string& fileName) override;

        bool saveToFile(const std::string& fileName, IGraph& graph) override;

        void static bind(pybind11::module &m);

    };
}
