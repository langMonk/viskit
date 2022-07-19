///
/// \author Bartosz Minch <minch@agh.edu.pl>
/// \date 10.02.2020
///

#pragma once

#include <viskit/facade/FacadeGraphGenerator.h>
#include <viskit/facade/FacadeParticleSystem.h>
#include <viskit/viskit/IGraphGenerator.h>

namespace viskit::facade {
/// <summary>
/// Implementation of IGraphGenerator interface.
/// </summary>
class FacadeGraphGenerator : public IGraphGenerator {
public:
    explicit FacadeGraphGenerator(std::shared_ptr<core::Core> core);
    ~FacadeGraphGenerator() = default;

    FacadeGraphGenerator(const FacadeGraphGenerator&) = delete;
    FacadeGraphGenerator(FacadeGraphGenerator&&) = delete;

    FacadeGraphGenerator& operator=(const FacadeGraphGenerator&) = delete;
    FacadeGraphGenerator& operator=(FacadeGraphGenerator&&) = delete;

    void generate(IParticleSystem& ps, IGraph& graph, IGraph& helperGraph) override {};
    void generate(IParticleSystem& ps, IGraph& graph, IGraph& helperGraph, size_t k, bool distancesEqualOne) override {};
    void generate(IParticleSystem& ps, IGraph& graph, size_t k, bool distancesEqualOne) override {};

protected:
    std::shared_ptr<core::Core> m_ext_core;
};
}