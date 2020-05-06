///
/// \author Bartosz Minch <minch@agh.edu.pl>
/// \date 30.04.2020
///

#pragma once

#include <IGraphGenerator.h>
#include <IGraph.h>
#include <IParticleSystem.h>

namespace ivhd { namespace cuda { namespace graph {
    class FaissGraphGenerator : public ivhd::IGraphGenerator
    {
    public:
        FaissGraphGenerator() = default;

        void generateNearestNeighbors(ivhd::IParticleSystem& ps, ivhd::IGraph& graph, size_t k,
                bool distancesEqualOne) override;

        void generateRandomNeighbors(ivhd::IParticleSystem& ps, ivhd::IGraph& graph, size_t k,
                bool distancesEqualOne) override;
    };
} } }