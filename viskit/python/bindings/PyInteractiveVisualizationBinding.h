//
// Created by Bartosz Minch on 02/05/2022.
//

#pragma once

#include "viskit/viskit/IInteractiveVisualization.h"

namespace viskit::python::bindings
{
    class PyInteractiveVisualizationBinding: public IInteractiveVisualization {
    public:
        using IInteractiveVisualization::IInteractiveVisualization;

        viskit::IResourceFactory& resourceFactory() override;

        void computeCastingStep(viskit::IParticleSystem& ps, viskit::IGraph& graph, viskit::ICaster& caster) override;

        typedef std::vector<std::pair<float, float>> vector_of_pairs;

        std::vector<std::pair<float, float>> calculateBoundingBox() override;

        void subscribeOnCastingStepFinish(viskit::IInteractiveVisualization::CasterEventHandler handler) override;

        void static bind(pybind11::module &m);
    };
}
