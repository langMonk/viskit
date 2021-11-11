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

    void Reverse::generate(particles::ParticleSystem &ps, graph::Graph &graph, size_t k, bool distancesEqualOne)
    {
        assert(graph.neighborsCounter.nearestNeighbors > 0);

        m_ext_system.logger().logInfo("[rkNN Generator] Determining reverse nearest neighbors...");
        for (size_t i = 0; i < ps.countParticles(); i++)
        {
            if (const auto currentParticleNeighborsIndexes = graph.getNeighborsIndexes(i))
            {
                for (const auto currentParticleNeighborIndex : *currentParticleNeighborsIndexes)
                {
                    if (const auto neighborParticleNeighborsIndexes = graph.getNeighborsIndexes(currentParticleNeighborIndex))
                    {
                        if (std::count(neighborParticleNeighborsIndexes->begin(),
                                   neighborParticleNeighborsIndexes->end(),
                                   currentParticleNeighborIndex))
                        {
                            break;
                        }
                        else
                        {
                            graph.addNeighbors(Neighbors(i, currentParticleNeighborIndex, 0.0f, NeighborsType::Reverse));
                        }
                    }
                }
            }
        }

        graph.neighborsCounter.reverseNeighbors = k;
        m_ext_system.logger().logInfo("[rkNN Generator] Finished.");
        m_ext_system.logger().logInfo("[rkNN Generator] Neighbors in graph: " + std::to_string(graph.overallNeighborsCount()));
    }
}