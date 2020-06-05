///
/// \author Bartosz Minch <minch@agh.edu.pl>
/// \date 04.06.2020
///

#ifdef USE_CUDA

#pragma once

#include "graph/generate/GraphGenerator.h"
#include "particles/ParticleSystem.h"
#include "graph/Graph.h"

namespace ivhd::graph::generate
{
    class Faiss final : public GraphGenerator
    {
        // public construction and destruction methods
    public:

        explicit Faiss(core::System& system);

        // public methods
    public:
        void generateNearestNeighbors(particles::ParticleSystem& ps, graph::Graph& graph, size_t k, bool distancesEqualOne) override;

    };
}

#endif