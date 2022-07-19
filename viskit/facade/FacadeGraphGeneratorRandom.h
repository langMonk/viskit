///
/// \author Bartosz Minch <minch@agh.edu.pl>
/// \date 10.06.2020
///

#pragma once

#include <viskit/facade/FacadeGraphGenerator.h>
#include <viskit/facade/FacadeParticleSystem.h>
#include <viskit/graph/generate/Random.h>

namespace viskit::facade {
/// <summary>
/// Implementation of IGraphGenerator interface.
/// </summary>
class FacadeGraphGeneratorRandom : public FacadeGraphGenerator {
public:
    explicit FacadeGraphGeneratorRandom(const std::shared_ptr<core::Core>& core);

    void generate(IParticleSystem& ps, IGraph& graph, size_t k, bool distancesEqualOne) override;

    void generate(IParticleSystem& ps, IGraph& graph, IGraph& graphHelper, size_t k, bool distancesEqualOne) override;

private:
    std::shared_ptr<generate::Random> m_graphGenerator { nullptr };
};
}