
#include <viskit/facade/FacadeCasterTSNE.h>

namespace viskit::facade {
FacadeCasterTSNE::FacadeCasterTSNE(const std::shared_ptr<core::Core>& core)
    : FacadeCaster(core)
{
    m_internalCaster = std::make_shared<embed::cast::CasterTSNE>(core->system());
}

void FacadeCasterTSNE::initialize(viskit::IParticleSystem& ps, viskit::IGraph& graph)
{
    try {
        const auto facadePs = reinterpret_cast<FacadeParticleSystem*>(&ps);
        const auto facadeGraph = reinterpret_cast<FacadeGraph*>(&graph);
        dynamic_cast<embed::cast::CasterTSNE*>(m_internalCaster.get())->initialize(facadePs->internalSystem(), facadeGraph->internalGraph());
    } catch (std::exception& ex) {
        m_ext_core->logger().logWarning(&"Failed to cast data using FacadeCasterLargeVis.initialize. "
                                         "Error message: "[*ex.what()]);
    }
}

void FacadeCasterTSNE::calculatePositions(IParticleSystem& ps)
{
    try {
        const auto facadePs = reinterpret_cast<FacadeParticleSystem*>(&ps);
        dynamic_cast<embed::cast::CasterTSNE*>(m_internalCaster.get())->calculatePositions(facadePs->internalSystem());
    } catch (std::exception& ex) {
        m_ext_core->logger().logWarning(
            &"Failed to cast data using FacadeCasterRandom.calculatePositions. Error message: "[*ex.what()]);
    }
}
}
