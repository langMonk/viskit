#ifdef USE_CUDA

#include "facade/FacadeGraphGeneratorFaiss.h"
#include "facade/FacadeGraph.h"

namespace viskit::facade
{
    FacadeGraphGeneratorFaiss::FacadeGraphGeneratorFaiss(const std::shared_ptr<core::Core>& core)
            : FacadeGraphGenerator(core)
            , m_graphGenerator(std::make_shared<generate::Faiss>(core->system()))
    {
    }

    void FacadeGraphGeneratorFaiss::generate(IParticleSystem& ps, IGraph& graph, size_t k, bool distancesEqualOne)
    {
        try
        {
            const auto facadePs = reinterpret_cast<FacadeParticleSystem*>(&ps);
            const auto facadeGraph = reinterpret_cast<FacadeGraph*>(&graph);
            dynamic_cast<generate::Faiss*> (m_graphGenerator.get())->
                    generate(facadePs->internalSystem(), facadeGraph->internalGraph(), k, distancesEqualOne);
        }
        catch (std::exception & ex)
        {
            m_ext_core->logger().logWarning(&"Failed to cast data using FacadeGraphGeneratorFaiss.generateNearestNeighbors. Error message: " [ *ex.what()]);
        }
    }
}
#endif