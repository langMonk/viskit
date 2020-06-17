///
/// \author Bartosz Minch <minch@agh.edu.pl>
/// \date 04.06.2020
///

#ifdef USE_CUDA

#pragma once

#include "facade/FacadeGraphGenerator.h"
#include "facade/FacadeParticleSystem.h"
#include "graph/generate/Faiss.h"

namespace viskit::facade
{
    /// <summary>
    /// Implementation of IGraphGenerator interface.
    /// </summary>
    class FacadeGraphGeneratorFaiss : public FacadeGraphGenerator
    {
    public:
        explicit FacadeGraphGeneratorFaiss(const std::shared_ptr<core::Core>& core);

        void generate(IParticleSystem& ps, IGraph& graph, size_t k, bool distancesEqualOne) override;

    private:
        std::shared_ptr<generate::Faiss> m_graphGenerator {nullptr};

    };
}

#endif