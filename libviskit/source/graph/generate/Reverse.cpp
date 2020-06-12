#include "graph/generate/Reverse.h"
#include "utils/Math.h"

namespace ivhd::graph::generate
{
    Reverse::Reverse(core::System &system) : GraphGenerator(system)
    {

    }

    void Reverse::generate(particles::ParticleSystem &ps, graph::Graph &graph, size_t k, bool distancesEqualOne)
    {
        m_ext_system.logger().logInfo("[rkNN Generator] Determining reverse nearest neighbors...");

        for (size_t i = 0; i < ps.countParticles(); i++)
        {
            if (const auto neighbors = graph.getNeighbors(i))
            {
                for (const auto neighbor : *neighbors)
                {

                }
            }
        }

        graph.randomNeighborsCount(k);
        m_ext_system.logger().logInfo("[rkNN Generator] Finished.");
        m_ext_system.logger().logInfo("[rkNN Generator] Neighbors in graph: " + std::to_string(graph.neighborsCount()));
    }

    bool Reverse::validateIfReverseNeighbor(size_t index1, size_t index2)
    {
        return true;
    }
}