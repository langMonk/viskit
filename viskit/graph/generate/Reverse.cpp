///
/// \author Bartosz Minch <minch@agh.edu.pl>
/// \date 12.06.2020
///

#include <viskit/graph/generate/Reverse.h>
#include <viskit/utils/Math.h>

namespace viskit::graph::generate {
Reverse::Reverse(core::System& system)
    : GraphGenerator(system)
{
}

void Reverse::generate(particles::ParticleSystem& ps, graph::Graph& graph, graph::Graph& helperGraph)
{
    assert(graph.neighborsCounter.nearestNeighbors > 0);

    m_ext_system.logger().logInfo("[Reverse Neighbors Generator] Determining reverse nearest neighbors...");
    for (size_t x = 0; x < ps.countParticles(); x++) {
        if (const auto xParticleNeighbors = graph.getNearestNeighborsIndexes(x)) {
            std::vector<Neighbors> neighborsToRemove;
            for (const auto xParticleNeighbor : *xParticleNeighbors) {
                if (const auto xPrimeParticleNeighbors = helperGraph.getNearestNeighborsIndexes(xParticleNeighbor)) {
                    if (std::count(xPrimeParticleNeighbors->begin(), xPrimeParticleNeighbors->end(), x)) {
                        neighborsToRemove.emplace_back(Neighbors(xParticleNeighbor, x));
                    }
                }
            }

            if (neighborsToRemove.empty()) {
                std::vector<size_t> to_remove;
                const auto rand = std::sample(xParticleNeighbors->begin(), xParticleNeighbors->end(), std::back_inserter(to_remove), 1, std::mt19937 { std::random_device {}() });
                for (auto i : to_remove) {
                    graph.removeNeighbors(x, i);
                }
            } else if (neighborsToRemove.size() < graph.neighborsCounter.nearestNeighbors) {
                for (const auto neighbor : neighborsToRemove) {
                    graph.removeNeighbors(x, neighbor.i);
                }
            }
        }
    }

    m_ext_system.logger().logInfo("[Reverse Neighbors Generator] Finished.");
    m_ext_system.logger().logInfo("[Reverse Neighbors Generator] Neighbors in graph: " + std::to_string(graph.overallNeighborsCount()));
}
}