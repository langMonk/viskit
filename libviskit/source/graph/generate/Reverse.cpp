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
            auto reverseNeighbors = validateReverseNeighbors(graph, ps.countParticles(), k, i);
            if (!reverseNeighbors->empty())
            {
                for (auto const reverseNeighbor : *reverseNeighbors)
                {
                    auto distance = 1.0f;
                    if (!distancesEqualOne)
                    {
                        distance = reverseNeighbor.r;
                    }
                    graph.addNeighbors(
                            Neighbors(reverseNeighbor.j, reverseNeighbor.i, distance, NeighborsType::Reverse));
                }
            }
        }

        graph.neighborsCounter.reverseNeighbors = k;
        m_ext_system.logger().logInfo("[rkNN Generator] Finished.");
        m_ext_system.logger().logInfo("[rkNN Generator] Neighbors in graph: " + std::to_string(graph.overallNeighborsCount()));
    }

    std::optional<std::vector<Neighbors>> Reverse::validateReverseNeighbors(graph::Graph &graph, size_t count, size_t k, size_t index)
    {
        std::vector<Neighbors> reverseNeighbors{};

        auto k_max = 0;
        for (size_t i = 0; i < count; i++)
        {
            if(i == index) { continue; }

            if (const auto neighbors = graph.getNeighbors(i))
            {
                for (const auto neighbor : *neighbors)
                {
                    if (neighbor.j == index)
                    {
                        reverseNeighbors.emplace_back(neighbor);
                        k_max++;
                    }

                    if(k_max >= k) { break; }
                }
            }

            if(k_max >= k) { break; }
        }

        return reverseNeighbors;
    }
}