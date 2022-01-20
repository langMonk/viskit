///
/// \author Bartosz Minch <minch@agh.edu.pl>
/// \date 12.05.2019
///

#include <viskit/facade/FacadeCasterRandom.h>

namespace viskit::facade {
FacadeCasterRandom::FacadeCasterRandom(const std::shared_ptr<core::Core>& core)
    : FacadeCaster(core)
{
    m_internalCaster = std::make_shared<embed::cast::CasterRandom>(core->system());
}

void FacadeCasterRandom::calculatePositions(IParticleSystem& ps)
{
    try {
        const auto facadePs = reinterpret_cast<FacadeParticleSystem*>(&ps);
        dynamic_cast<embed::cast::CasterRandom*>(m_internalCaster.get())->calculatePositions(facadePs->internalSystem());
    } catch (std::exception& ex) {
        m_ext_core->logger().logWarning(&"Failed to cast data using FacadeCasterRandom.calculatePositions. Error message: "[*ex.what()]);
    }
}
}
