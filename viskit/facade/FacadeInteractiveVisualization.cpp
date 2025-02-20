///
/// \author Bartosz Minch <minch@agh.edu.pl>
/// \date 18.04.2019
///

#include <vector>
#include <viskit/facade/FacadeInteractiveVisualization.h>

namespace viskit::facade {
FacadeInteractiveVisualization::FacadeInteractiveVisualization(const LogHandler& logHandler)
    : m_core(std::make_shared<core::Core>(logHandler))
{
}

std::shared_ptr<core::Core> FacadeInteractiveVisualization::core() const
{
    return m_core;
}

void FacadeInteractiveVisualization::subscribeOnCastingStepFinish(CasterEventHandler handler)
{
    m_onCastingStepFinished = handler;
}

void FacadeInteractiveVisualization::computeCastingStep(IParticleSystem& ps, IGraph& graph, ICaster& caster)
{
    caster.step(ps, graph);
    m_onCastingStepFinished();
}

std::vector<std::pair<float, float>> FacadeInteractiveVisualization::calculateBoundingBox()
{
    std::vector<std::pair<float, float>> vec;
    const auto pair = std::pair<float, float>(0.0f, 0.0f);
    vec.push_back(pair);
    return vec;
}

IResourceFactory& FacadeInteractiveVisualization::resourceFactory()
{
    return m_resourceFactory;
}
}
