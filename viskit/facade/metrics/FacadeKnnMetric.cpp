///
/// \author Bartosz Minch <minch@agh.edu.pl> 
/// \date 17.06.2020
///

#include <utility>
#include <viskit/facade/metrics/FacadeKnnMetric.h>
#include <viskit/facade/FacadeParticleSystem.h>
#include <viskit/graph/Graph.h>
#include <viskit/graph/generate/BruteForce.h>
#include <viskit/graph/generate/GraphGenerator.h>
#include <viskit/viskit/Structures.h>
#include <viskit/math/glm_adapter.h>

namespace viskit::facade::metrics
{
    FacadeKnnMetric::FacadeKnnMetric(std::shared_ptr<core::Core> core)
        : m_ext_core(std::move(core))
    {

    }


    float FacadeKnnMetric::calculate(viskit::IParticleSystem& ps, int k)
    {
        auto metricValue = 0;
        try
        {
            const auto facadePs = reinterpret_cast<FacadeParticleSystem*>(&ps);
            Graph internalGraph = buildInternalGraph(facadePs->internalSystem(), k);
            auto labels = ps.labels();

            for (size_t i = 0; i < ps.countParticles(); i++)
            {
                if (const auto neighbors = internalGraph.getNeighbors(i))
                {
                    auto count = std::count_if(neighbors->begin(), neighbors->end(), [&](Neighbors neighbor)
                    {
                        return labels[neighbor.j] == labels[i];
                    });

                    metricValue += count;
                }
            }
        }
        catch (std::exception& ex)
        {
            m_ext_core->logger().logWarning(&"Failed to calculate kNN metric. Error message: " [ *ex.what()]);
        }

        auto value  = static_cast<float>(metricValue) / static_cast<float>(ps.countParticles() * k);

        m_ext_core->logger().logInfo("kNN Metric value: " + std::to_string(value));
        return value;
    }

    Graph FacadeKnnMetric::buildInternalGraph(particles::ParticleSystem &ps, int k)
    {
        // create internal (for metric calculation) graph
        Graph internalGraph{m_ext_core->system()};
        std::vector<std::pair<DataPoint, particles::DataPointLabel>> dataPoints;

        // add 2-D data points to internal vector
        auto positions = ps.calculationData()->m_pos;
        auto labels = ps.labels();

        for(auto i = 0; i < positions.size(); i++)
        {
            std::vector<float> coords;
            coords.push_back(positions[i].x);
            coords.push_back(positions[i].y);

            dataPoints.emplace_back(std::make_pair(viskit::DataPoint(coords, i), labels[i]));
        }

        generate::BruteForce generator{m_ext_core->system()};

        generator.generate(ps, internalGraph, k, true);

        return internalGraph;
    }
}