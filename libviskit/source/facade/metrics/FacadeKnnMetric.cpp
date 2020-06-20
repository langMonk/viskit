///
/// \author Bartosz Minch <minch@agh.edu.pl> 
/// \date 17.06.2020
///

#include "facade/metrics/FacadeKnnMetric.h"

#include <utility>

#include "facade/FacadeParticleSystem.h"
#include "graph/Graph.h"
#include "graph/generate/BruteForce.h"
#include "graph/generate/GraphGenerator.h"
#include "viskit/Structures.h"
#include "math/glm_adapter.h"

#ifdef USE_CUDA
#include "graph/generate/Faiss.h"
#endif

namespace viskit::facade::metrics
{
    FacadeKnnMetric::FacadeKnnMetric(std::shared_ptr<core::Core> core)
        : m_ext_core(std::move(core))
    {

    }


    float FacadeKnnMetric::calculate(viskit::IParticleSystem& ps, int k)
    {
        auto metricValue = 0.0f;
        try
        {
            const auto facadePs = reinterpret_cast<FacadeParticleSystem*>(&ps);
            Graph internalGraph = buildInternalGraph(facadePs->internalSystem(), k);
            auto labels = ps.labels();

            for (size_t i = 0; i < ps.countParticles(); i++)
            {
                if (const auto neighbors = internalGraph.getNeighbors(i))
                {

                    for (const auto neighbor : *neighbors)
                    {
                        if (labels[neighbor.i] == labels[neighbor.j])
                        {
                            metricValue++;
                        }
                    }
                }
            }
        }
        catch (std::exception& ex)
        {
            m_ext_core->logger().logWarning(&"Failed to calculate kNN metric. Error message: " [ *ex.what()]);
        }


        return metricValue / static_cast<float>(ps.countParticles() * k);
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


#ifdef USE_CUDA
        generate::Faiss generator{m_ext_core->system()};
#else
        generate::BruteForce generator{m_ext_core->system()};
#endif

        generator.generate(dataPoints, internalGraph, k, true);

        return internalGraph;
    }
}