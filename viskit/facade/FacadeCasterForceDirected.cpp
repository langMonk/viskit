///
/// \author Bartosz Minch <minch@agh.edu.pl>
/// \date 18.03.2020
///

#include <viskit/facade/FacadeCasterForceDirected.h>

namespace viskit::facade {
FacadeCasterForceDirected::FacadeCasterForceDirected(const std::shared_ptr<core::Core>& core)
    : FacadeCaster(core)
{
    m_internalCaster = std::make_shared<embed::cast::ivhd::CasterForceDirected>(core->system());
}

void FacadeCasterForceDirected::calculatePositions(IParticleSystem& ps)
{
    try {
        const auto facadePs = reinterpret_cast<FacadeParticleSystem*>(&ps);
        dynamic_cast<embed::cast::ivhd::CasterForceDirected*>(m_internalCaster.get())->calculatePositions(facadePs->internalSystem());
    } catch (std::exception& ex) {
        m_ext_core->logger().logWarning(&"Failed to cast data using FacadeCasterForceDirected.calculatePositions. "
                                         "Error message: "[*ex.what()]);
    }
}

void FacadeCasterForceDirected::calculateForces(IParticleSystem& ps, IGraph& graph)
{
    try {
        const auto facadePs = reinterpret_cast<FacadeParticleSystem*>(&ps);
        const auto facadeGraph = reinterpret_cast<FacadeGraph*>(&graph);
        auto energy = 0.1f;
        size_t interactions = 0;
        dynamic_cast<embed::cast::ivhd::CasterForceDirected*>(m_internalCaster.get())->calculateForces(energy, facadePs->internalSystem(), facadeGraph->internalGraph(), interactions);
    } catch (std::exception& ex) {
        m_ext_core->logger().logWarning(&"Failed to cast data using FacadeCasterForceDirected.calculateForces. "
                                         "Error message: "[*ex.what()]);
    }
}

void FacadeCasterForceDirected::finalize()
{
    try {
        dynamic_cast<embed::cast::ivhd::CasterForceDirected*>(m_internalCaster.get())->setFinalizing(true);
    } catch (std::exception& ex) {
        m_ext_core->logger().logWarning(&"Failed to finalize FacadeCasterForceDirected.finalize(). "
                                         "Error message: "[*ex.what()]);
    }
}
}