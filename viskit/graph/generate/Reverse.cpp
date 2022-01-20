///
/// \author Bartosz Minch <minch@agh.edu.pl>
/// \date 12.06.2020
///

#include <viskit/graph/generate/Reverse.h>
#include <viskit/utils/Math.h>

namespace viskit::graph::generate
{
    Reverse::Reverse(core::System &system) : GraphGenerator(system)
    {

    }

    void Reverse::generate(particles::ParticleSystem &ps, graph::Graph &graph, graph::Graph &helperGraph)
    {
        assert(graph.neighborsCounter.nearestNeighbors > 0);

        m_ext_system.logger().logInfo("[Reverse Neighbors Generator] Determining reverse nearest neighbors...");
        for (size_t x = 0; x < ps.countParticles(); x++)
        {
            if (const auto xParticleNeighbors = graph.getNeighborsIndexes(x))
            {
                for (auto const xParticleNeighbor : *xParticleNeighbors)
                {
                    if (const auto xPrimeParticleNeighbors = helperGraph.getNeighborsIndexes(xParticleNeighbor))
                    {
                        auto it = std::find_if_not(xPrimeParticleNeighbors->begin(), xPrimeParticleNeighbors->end(), [&x] (size_t index) { return index == x; } );
                        if (it != xPrimeParticleNeighbors->end())
                        {
                            graph.removeNeighbors(x, xParticleNeighbor);
                        }
                    }
                }
            }
        }

        m_ext_system.logger().logInfo("[Reverse Neighbors Generator] Finished.");
        m_ext_system.logger().logInfo("[Reverse Neighbors Generator] Neighbors in graph: " + std::to_string(graph.overallNeighborsCount()));
    }
}