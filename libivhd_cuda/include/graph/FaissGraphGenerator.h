///
/// \author Bartosz Minch <minch@agh.edu.pl>
/// \date 30.04.2020
///

#pragma once

#include <ivhd/IGraphGenerator.h>
#include <ivhd/IGraph.h>
#include <ivhd/IParticleSystem.h>

namespace ivhd { namespace cuda { namespace graph {
    class FaissGraphGenerator : public ivhd::IGraphGenerator
    {
        FaissGraphGenerator() = default;

        void generateNearestNeighbors(ivhd::IParticleSystem& ps, ivhd::IGraph& graph, size_t k,
                bool distancesEqualOne) override;

        void generateRandomNeighbors(ivhd::IParticleSystem& ps, ivhd::IGraph& graph, size_t k,
                bool distancesEqualOne) override;
    };
} } }