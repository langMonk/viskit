//
// Created by Jakub Perzylo on 23/04/2022.
//

#pragma once

#include <viskit/embed/cast/umap/CasterUMAP.h>
#include <viskit/facade/FacadeCaster.h>
#include <viskit/viskit/IParticleSystem.h>

namespace viskit::facade {
/// <summary>
/// Implementation of ICaster interface.
/// </summary>
class FacadeCasterUMAP : public FacadeCaster {
    // public construction and destruction methods
public:
    explicit FacadeCasterUMAP(std::shared_ptr<core::Core> core);
    ~FacadeCasterUMAP() override = default;

    FacadeCasterUMAP(const FacadeCasterUMAP&) = delete;
    FacadeCasterUMAP(FacadeCasterUMAP&&) = delete;

    FacadeCasterUMAP& operator=(const FacadeCasterUMAP&) = delete;
    FacadeCasterUMAP& operator=(FacadeCasterUMAP&&) = delete;

    void initialize(viskit::IParticleSystem& ps, viskit::IGraph& graph) override
    {
        const auto facadePs = reinterpret_cast<FacadeParticleSystem*>(&ps);
        const auto facadeGraph = reinterpret_cast<FacadeGraph*>(&graph);
        auto caster = dynamic_cast<embed::cast::umap::CasterUMAP*>(m_internalCaster.get());
        caster->set_num_neighbours(15)
            .set_total_iterations(500)
            .initialize(facadePs->internalSystem(), facadeGraph->internalGraph());
    }

    // public methods
public:
    void calculatePositions(IParticleSystem& ps) override;

    void calculateForces(IParticleSystem& ps, IGraph& graph) override;

    CasterType type() override { return CasterType::UMAP; }

    OptimizerType optimizerType() override { return OptimizerType::None; }
};
}
