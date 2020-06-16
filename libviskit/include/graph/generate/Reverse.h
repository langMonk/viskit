///
/// \author Bartosz Minch <minch@agh.edu.pl>
/// \date 12.06.2020
///

#pragma once

#include "graph/generate/GraphGenerator.h"
#include "particles/ParticleSystem.h"
#include "graph/Graph.h"

namespace ivhd::graph::generate
{
    class Reverse final : public GraphGenerator
    {
        // public construction and destruction methods
    public:
        explicit Reverse(core::System& system);

        // public methods
    public:
        void generate(particles::ParticleSystem& ps, graph::Graph& graph, size_t k, bool distancesEqualOne) override;

    private:
        static std::optional<std::vector<Neighbors>> validateReverseNeighbors(graph::Graph &graph, size_t count, size_t k, size_t index);
    };
}