///
/// \author Bartosz Minch <minch@agh.edu.pl>
/// \date 28.04.2019
///

#include <viskit/facade/FacadeCasterAdadelta.h>
#include <viskit/facade/FacadeCasterAdam.h>
#include <viskit/facade/FacadeCasterForceDirected.h>
#include <viskit/facade/FacadeCasterLargeVis.h>
#include <viskit/facade/FacadeCasterMomentum.h>
#include <viskit/facade/FacadeCasterNesterov.h>
#include <viskit/facade/FacadeCasterRandom.h>
#include <viskit/facade/FacadeCasterTSNE.h>
#include <viskit/facade/FacadeGraphGeneratorBruteForce.h>
#include <viskit/facade/FacadeGraphGeneratorKDTree.h>
#include <viskit/facade/FacadeGraphGeneratorRandom.h>
#include <viskit/facade/FacadeGraphGeneratorReverse.h>
#include <viskit/facade/FacadeInteractiveVisualization.h>
#include <viskit/facade/FacadeParserCSV.h>
#include <viskit/facade/FacadeResourceFactory.h>
#include <viskit/facade/metrics/FacadeKnnMetric.h>
#include <viskit/facade/FacadeCasterUMAP.h>
#include <viskit/facade/FacadeCasterSGD.h>

namespace viskit::facade {
FacadeResourceFactory::FacadeResourceFactory(FacadeInteractiveVisualization& ivhd)
    : m_ext_viskit(ivhd)
{
}

std::shared_ptr<IParser> FacadeResourceFactory::createParser(const ParserType type)
{
    if (type == ParserType::Csv) {
        return std::make_shared<FacadeParserCSV>(m_ext_viskit.core());
    }

    return nullptr;
}

std::shared_ptr<IGraphGenerator> FacadeResourceFactory::createGraphGenerator(const GraphGeneratorType type)
{
    std::shared_ptr<IGraphGenerator> generator = nullptr;

    if (type == GraphGeneratorType::KDTreeBased) {
        generator = std::make_shared<FacadeGraphGeneratorKDTree>(m_ext_viskit.core());
    } else if (type == GraphGeneratorType::BruteForce) {
        generator = std::make_shared<FacadeGraphGeneratorBruteForce>(m_ext_viskit.core());
    } else if (type == GraphGeneratorType::Random) {
        generator = std::make_shared<FacadeGraphGeneratorRandom>(m_ext_viskit.core());
    } else if (type == GraphGeneratorType::Reverse) {
        generator = std::make_shared<FacadeGraphGeneratorReverse>(m_ext_viskit.core());
    }

    return generator;
}

std::shared_ptr<ICaster> FacadeResourceFactory::createCaster(const CasterType type, const OptimizerType optimizer)
{
    std::shared_ptr<ICaster> caster = nullptr;

    if (type == CasterType::Random) {
        caster = std::make_shared<FacadeCasterRandom>(m_ext_viskit.core());
    } else if (type == CasterType::IVHD && optimizer == OptimizerType::Momentum) {
        caster = std::make_shared<FacadeCasterMomentum>(m_ext_viskit.core());
    } else if (type == CasterType::IVHD && optimizer == OptimizerType::ForceDirected) {
        caster = std::make_shared<FacadeCasterForceDirected>(m_ext_viskit.core());
    } else if (type == CasterType::IVHD && optimizer == OptimizerType::Adadelta) {
        caster = std::make_shared<FacadeCasterAdadelta>(m_ext_viskit.core());
    } else if (type == CasterType::IVHD && optimizer == OptimizerType::Adam) {
        caster = std::make_shared<FacadeCasterAdam>(m_ext_viskit.core());
    } else if (type == CasterType::IVHD && optimizer == OptimizerType::Nesterov) {
        caster = std::make_shared<FacadeCasterNesterov>(m_ext_viskit.core());
    } else if (type == CasterType::UMAP) {
        caster = std::make_shared<FacadeCasterUMAP>(m_ext_viskit.core());
    } else if (type == CasterType::LargeVis) {
        caster = std::make_shared<FacadeCasterLargeVis>(m_ext_viskit.core());
    } else if (type == CasterType::IVHD && optimizer == OptimizerType::tSNE) {
        caster = std::make_shared<FacadeCasterTSNE>(m_ext_viskit.core());
    } else if (type == CasterType::IVHD && optimizer == OptimizerType::SGD) {
        caster = std::make_shared<FacadeCasterSGD>(m_ext_viskit.core());
    }

    return caster;
}

std::shared_ptr<IParticleSystem> FacadeResourceFactory::createParticleSystem()
{
    return std::make_shared<FacadeParticleSystem>(m_ext_viskit.core());
}

std::shared_ptr<IGraph> FacadeResourceFactory::createGraph()
{
    return std::make_shared<FacadeGraph>(m_ext_viskit.core());
}

std::shared_ptr<IMetric> FacadeResourceFactory::createMetricCalculator()
{
    return std::make_shared<metrics::FacadeKnnMetric>(m_ext_viskit.core());
}
}
