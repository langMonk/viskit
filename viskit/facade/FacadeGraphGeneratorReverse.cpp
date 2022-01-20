///
/// \author Bartosz Minch <minch@agh.edu.pl>
/// \date 23.06.2020
///

#include <viskit/facade/FacadeGraph.h>
#include <viskit/facade/FacadeGraphGeneratorReverse.h>

namespace viskit::facade
{
    FacadeGraphGeneratorReverse::FacadeGraphGeneratorReverse(const std::shared_ptr<core::Core>& core)
            : FacadeGraphGenerator(core)
    {
        m_graphGenerator = std::make_shared<graph::generate::Reverse>(core->system());
    }

    void FacadeGraphGeneratorReverse::generate(IParticleSystem& ps, IGraph& graph, IGraph& helperGraph)
    {
        try
        {
            const auto facadePs = reinterpret_cast<FacadeParticleSystem*>(&ps);
            const auto facadeGraph = reinterpret_cast<FacadeGraph*>(&graph);
            const auto facadeHelperGraph = reinterpret_cast<FacadeGraph*>(&helperGraph);
            dynamic_cast<generate::Reverse*>(m_graphGenerator.get())->
                    generate(facadePs->internalSystem(), facadeGraph->internalGraph(), facadeHelperGraph->internalGraph());
        }
        catch (std::exception& ex)
        {
            m_ext_core->logger().logWarning(&"Failed to cast data using FacadeGraphGeneratorReverse.generateNearestNeighbors. Error message: " [ *ex.what()]);
        }
    }
}
