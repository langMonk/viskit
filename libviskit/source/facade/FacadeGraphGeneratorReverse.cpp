#include <facade/FacadeGraph.h>
#include "facade/FacadeGraphGeneratorReverse.h"

namespace viskit::facade
{
    FacadeGraphGeneratorReverse::FacadeGraphGeneratorReverse(const std::shared_ptr<core::Core>& core)
            : FacadeGraphGenerator(core)
    {
        m_graphGenerator = std::make_shared<graph::generate::Reverse>(core->system());
    }

    void FacadeGraphGeneratorReverse::generate(IParticleSystem& ps, IGraph& graph, size_t k, bool distancesEqualOne)
    {
        try
        {
            const auto facadePs = reinterpret_cast<FacadeParticleSystem*>(&ps);
            const auto facadeGraph = reinterpret_cast<FacadeGraph*>(&graph);
            dynamic_cast<generate::Reverse*>(m_graphGenerator.get())->
                    generate(facadePs->internalSystem(), facadeGraph->internalGraph(), k, distancesEqualOne);
        }
        catch (std::exception& ex)
        {
            m_ext_core->logger().logWarning(&"Failed to cast data using FacadeGraphGeneratorReverse.generateNearestNeighbors. Error message: " [ *ex.what()]);
        }
    }
}
