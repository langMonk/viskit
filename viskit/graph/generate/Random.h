///
/// \author Bartosz Minch <minch@agh.edu.pl>
/// \date 12.06.2020
///

#pragma once

#include <viskit/graph/Graph.h>
#include <viskit/graph/generate/GraphGenerator.h>
#include <viskit/particles/ParticleSystem.h>

namespace viskit::graph::generate {
class Random final : public GraphGenerator {
    // public construction and destruction methods
public:
    explicit Random(core::System& system);

    // public methods
public:
    void generate(particles::ParticleSystem& ps, graph::Graph& graph, size_t k, bool distancesEqualOne) override;

    void generate(particles::ParticleSystem& ps, graph::Graph& graph, graph::Graph& helperGraph, size_t k, bool distancesEqualOne) override;
};
}