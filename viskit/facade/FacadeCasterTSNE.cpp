///
/// \author Tomasz Załęski
/// \date 25.05.2021
///

#include <viskit/facade/FacadeCasterTSNE.h>

using namespace std::literals::string_literals;

namespace viskit::facade
{
	FacadeCasterTSNE::FacadeCasterTSNE(std::shared_ptr<core::Core> core)
		: FacadeCaster(core)
	{
		m_internalCaster = std::make_shared<embed::cast::ivhd::CasterTSNE>(core->system());
	}

	void FacadeCasterTSNE::calculatePositions(IParticleSystem& ps)
	{
		try
		{
			const auto facadePs = reinterpret_cast<FacadeParticleSystem*>(&ps);
			dynamic_cast<embed::cast::ivhd::CasterTSNE*>(m_internalCaster.get())->calculatePositions(facadePs->internalSystem());
		}
		catch (std::exception& ex)
		{
			m_ext_core->logger().logWarning("Failed to cast data using FacadeCasterTSNE.calculatePositions. Error message: "s + ex.what());
		}
	}

    void FacadeCasterTSNE::calculateForces(IParticleSystem& ps, IGraph& graph)
    {
        try
        {
            auto facadePs = reinterpret_cast<FacadeParticleSystem*>(&ps);
            auto facadeGraph = reinterpret_cast<FacadeGraph*>(&graph);
            auto energy = 0.1f;
            size_t interactions = 0;
            dynamic_cast<embed::cast::ivhd::CasterTSNE*>(m_internalCaster.get())->calculateForces(energy, facadePs->internalSystem(), facadeGraph->internalGraph(), interactions);
        }
        catch (std::exception & ex)
        {
            m_ext_core->logger().logWarning("Failed to cast data using FacadeCasterTSNE.calculateForces. Error message: "s + ex.what());
        }
    }
}
