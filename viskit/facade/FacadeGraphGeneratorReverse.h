///
/// \author Bartosz Minch <minch@agh.edu.pl> 
/// \date 23.06.2020
///

#pragma once

#include <viskit/facade/FacadeGraphGenerator.h>
#include <viskit/facade/FacadeParticleSystem.h>
#include <viskit/graph/generate/Reverse.h>

namespace viskit::facade
{
    /// <summary>
    /// Implementation of IGraphGenerator interface.
    /// </summary>
    class FacadeGraphGeneratorReverse : public FacadeGraphGenerator
    {
    public:
        explicit FacadeGraphGeneratorReverse(const std::shared_ptr<core::Core>& core);

        void generate(IParticleSystem& ps, IGraph& graph, IGraph& helperGraph) override;

    private:
        std::shared_ptr<generate::Reverse> m_graphGenerator {nullptr};

    };
}