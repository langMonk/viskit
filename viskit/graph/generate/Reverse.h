///
/// \author Bartosz Minch <minch@agh.edu.pl>
/// \date 12.06.2020
///

#pragma once

#include <viskit/graph/generate/GraphGenerator.h>
#include <viskit/particles/ParticleSystem.h>
#include <viskit/graph/Graph.h>

namespace viskit::graph::generate
{
    class Reverse final : public GraphGenerator
    {
        // public construction and destruction methods
    public:
        explicit Reverse(core::System& system);

        // public methods
    public:
        void generate(particles::ParticleSystem &ps, graph::Graph &graph, graph::Graph &helperGraph);
    };
}