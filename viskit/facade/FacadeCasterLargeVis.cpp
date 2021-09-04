///
/// \author tomsia
/// \date 27.05.2021
///


#include <viskit/facade/FacadeCasterLargeVis.h>

namespace viskit::facade
{
    FacadeCasterLargeVis::FacadeCasterLargeVis(const std::shared_ptr<core::Core>& core)
            : FacadeCaster(core)
    {
        m_internalCaster = std::make_shared<embed::cast::CasterLargeVis>(core->system());
    }

    void FacadeCasterLargeVis::initialize(viskit::IParticleSystem &ps, viskit::IGraph &graph)
    {
        try
        {
            const auto facadePs = reinterpret_cast<FacadeParticleSystem*>(&ps);
            const auto facadeGraph = reinterpret_cast<FacadeGraph*>(&graph);
            dynamic_cast<embed::cast::CasterLargeVis*>(m_internalCaster.get())->initialize(facadePs->internalSystem(), facadeGraph->internalGraph());
        }
        catch (std::exception & ex)
        {
            m_ext_core->logger().logWarning(&"Failed to cast data using FacadeCasterLargeVis.initialize. "
                                             "Error message: " [ *ex.what()]);
        }
    }

    void FacadeCasterLargeVis::calculatePositions(IParticleSystem& ps)
    {
        try
        {
            const auto facadePs = reinterpret_cast<FacadeParticleSystem*>(&ps);
            dynamic_cast<embed::cast::CasterLargeVis*>(m_internalCaster.get())->calculatePositions(facadePs->internalSystem());
        }
        catch (std::exception & ex)
        {
            m_ext_core->logger().logWarning(&"Failed to cast data using FacadeCasterLargeVis.calculatePositions. "
                                             "Error message: " [ *ex.what()]);
        }
    }
}
