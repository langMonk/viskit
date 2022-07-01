//
// Created by Jakub Perzylo on 23/04/2022.
//

#include "FacadeCasterUMAP.h"

using namespace std::literals::string_literals;

namespace viskit::facade {
    FacadeCasterUMAP::FacadeCasterUMAP(std::shared_ptr<core::Core> core)
            : FacadeCaster(core)
    {
        m_internalCaster = std::make_shared<embed::cast::umap::CasterUMAP>(core->system());
    }

    void FacadeCasterUMAP::calculatePositions(IParticleSystem& ps)
    {
        try {
            const auto facadePs = reinterpret_cast<FacadeParticleSystem*>(&ps);
            dynamic_cast<embed::cast::umap::CasterUMAP*>(m_internalCaster.get())->calculatePositions(facadePs->internalSystem());
        } catch (std::exception& ex) {
            m_ext_core->logger().logWarning("Failed to cast data using FacadeCasterUMAP.calculatePositions. Error message: "s + ex.what());
        }
    }

    void FacadeCasterUMAP::calculateForces(IParticleSystem& ps, IGraph& graph) { }
}
