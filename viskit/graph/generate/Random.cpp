///
/// \author Bartosz Minch <minch@agh.edu.pl>
/// \date 12.06.2020
///

#include <viskit/graph/generate/Random.h>
#include <viskit/utils/Math.h>

namespace viskit::graph::generate
{
    Random::Random(core::System &system) : GraphGenerator(system)
    {

    }

    void Random::generate(particles::ParticleSystem& ps, graph::Graph& graph, size_t k, bool distancesEqualOne)
    {
        m_ext_system.logger().logInfo("[kNN Generator] Determining random neighbors...");

        for (size_t i = 0; i < ps.countParticles(); i++)
        {
            for (auto random = 0; random < k; random++)
            {
                while (true)
                {
                    const auto j = math::randInt(0, ps.countParticles()-1);
                    if (j != i)
                    {
                        if (!alreadyNeighbors(i, j, graph))
                        {
                            auto distance = 1.0f;
                            if (!distancesEqualOne)
                            {
                                distance = ps.vectorDistance(i, j);
                            }

                            graph.addNeighbors(Neighbors{ i, j, distance, NeighborsType::Random });
                            break;
                        }
                    }
                }
            }
        }

        graph.neighborsCounter.randomNeighbors = k;
        m_ext_system.logger().logInfo("[kNN Generator] Finished.");
        m_ext_system.logger().logInfo("[kNN Generator] Neighbors in graph: " + std::to_string(graph.overallNeighborsCount()));
    }
}