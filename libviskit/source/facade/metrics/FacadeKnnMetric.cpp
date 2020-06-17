///
/// \author Bartosz Minch <minch@agh.edu.pl> 
/// \date 17.06.2020
///

#include "facade/metrics/FacadeKnnMetric.h"
#include "facade/FacadeParticleSystem.h"
#include "graph/Graph.h"

namespace viskit::facade::metrics
{
    FacadeKnnMetric::FacadeKnnMetric(const std::shared_ptr<core::Core>& core)
        : m_ext_core(core)
    {

    }


    float FacadeKnnMetric::calculate(viskit::IParticleSystem& ps)
    {
        auto metricValue = 0.0f;
        try
        {
            const auto facadePs = reinterpret_cast<FacadeParticleSystem*>(&ps);
            Graph internalGraph = buildInternalGraph(facadePs->internalSystem());

            // TODO: Actual metric calculation

        }
        catch (std::exception& ex)
        {
            m_ext_core->logger().logWarning(&"Failed to calculate kNN metric. Error message: " [ *ex.what()]);
        }


        return metricValue;
    }

    Graph FacadeKnnMetric::buildInternalGraph(particles::ParticleSystem &ps)
    {
        Graph internalGraph = Graph(m_ext_core->system());

#ifdef USE_CUDA

#else

#endif

        return internalGraph;
    }
}