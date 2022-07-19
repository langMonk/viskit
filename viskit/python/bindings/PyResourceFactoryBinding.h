//
// Created by Bartosz Minch on 02/05/2022.
//

#pragma once

#include <pybind11/pybind11.h>

#include "viskit/facade/FacadeInteractiveVisualization.h"
#include "viskit/facade/FacadeResourceFactory.h"
#include "viskit/viskit/IGraph.h"
#include "viskit/viskit/IGraphGenerator.h"
#include "viskit/viskit/IMetric.h"
#include "viskit/viskit/IParser.h"
#include "viskit/viskit/IParticleSystem.h"
#include "viskit/viskit/IResourceFactory.h"
#include "viskit/viskit/Structures.h"

namespace viskit::python::bindings {
class PyResourceFactoryBinding : public IResourceFactory {

public:
    using IResourceFactory::IResourceFactory;

    std::shared_ptr<viskit::IParser> createParser(viskit::ParserType type) override;

    std::shared_ptr<viskit::IGraphGenerator> createGraphGenerator(viskit::GraphGeneratorType type) override;

    std::shared_ptr<viskit::ICaster> createCaster(viskit::CasterType type, viskit::OptimizerType optimizer) override;

    std::shared_ptr<viskit::IParticleSystem> createParticleSystem() override;

    std::shared_ptr<viskit::IGraph> createGraph() override;

    std::shared_ptr<viskit::IMetric> createMetricCalculator() override;

    void static bind(pybind11::module& m);
};
}