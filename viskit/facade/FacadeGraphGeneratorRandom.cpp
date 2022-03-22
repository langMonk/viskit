///
/// \author Bartosz Minch <minch@agh.edu.pl>
/// \date 10.06.2020
///

#include <viskit/facade/FacadeGraph.h>
#include <viskit/facade/FacadeGraphGeneratorRandom.h>

namespace viskit::facade {
FacadeGraphGeneratorRandom::FacadeGraphGeneratorRandom(const std::shared_ptr<core::Core>& core)
    : FacadeGraphGenerator(core)
    , m_graphGenerator(std::make_shared<generate::Random>(core->system()))
{
}

void FacadeGraphGeneratorRandom::generate(IParticleSystem& ps, IGraph& graph, size_t k, bool distancesEqualOne)
{
    try {
        const auto facadePs = reinterpret_cast<FacadeParticleSystem*>(&ps);
        const auto facadeGraph = reinterpret_cast<FacadeGraph*>(&graph);
        dynamic_cast<generate::Random*>(m_graphGenerator.get())->generate(facadePs->internalSystem(), facadeGraph->internalGraph(), k, distancesEqualOne);
    } catch (std::exception& ex) {
        m_ext_core->logger().logWarning(&"Failed to cast data using GpuFacadeGraphGeneratorFaiss.generateNearestNeighbors. Error message: "[*ex.what()]);
    }
}

void FacadeGraphGeneratorRandom::generate(IParticleSystem& ps, IGraph& graph, IGraph& helperGraph, size_t k, bool distancesEqualOne)
{
    try {
        const auto facadePs = reinterpret_cast<FacadeParticleSystem*>(&ps);
        const auto facadeGraph = reinterpret_cast<FacadeGraph*>(&graph);
        const auto facadeHelperGraph = reinterpret_cast<FacadeGraph*>(&helperGraph);
        dynamic_cast<generate::Random*>(m_graphGenerator.get())->generate(facadePs->internalSystem(), facadeGraph->internalGraph(), facadeHelperGraph->internalGraph(), k, distancesEqualOne);
    } catch (std::exception& ex) {
        m_ext_core->logger().logWarning(&"Failed to cast data using GpuFacadeGraphGeneratorFaiss.generateNearestNeighbors. Error message: "[*ex.what()]);
    }
}
}
