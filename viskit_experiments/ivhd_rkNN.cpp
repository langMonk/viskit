///
/// \author Bartosz Minch <minch@agh.edu.pl> 
/// \date 23.06.2020
///

#include <memory>
#include <iostream>
#include <thread>

#include <InteractiveVisualizationBuilder.h>
#include <IResourceFactory.h>
#include <IParticleSystem.h>
#include <IGraph.h>
#include <IParser.h>
#include <ICaster.h>
#include <IGraphGenerator.h>
#include <IMetric.h>
#include <Structures.h>

using Logs = std::pair<viskit::LogLevel, std::string>;

void calculateMetrics(viskit::IInteractiveVisualization& viskit, viskit::IParticleSystem& particleSystem)
{
    // create and calculate metric
    const auto metricCalculator = viskit.resourceFactory().createMetricCalculator();
    std::cout << "k = 2: " << metricCalculator->calculate(particleSystem, 2) << std::endl;
    std::cout << "k = 10: " << metricCalculator->calculate(particleSystem, 10) << std::endl;
    std::cout << "k = 100: " << metricCalculator->calculate(particleSystem, 100) << std::endl;
}

int main()
{
    // initialize logging handler
    auto logsCount = 0;
    std::vector <Logs> logs{};

    auto handler = [&](viskit::LogLevel level, const std::string &message)
    {
        logs.emplace_back(level, message);
        logsCount++;
    };

    // create viskit
    auto viskit = viskit::createVisKit(handler);

    // create parser
    auto parser = viskit->resourceFactory().createParser(viskit::ParserType::Csv);

    // create particle system, graph
    auto particleSystem = viskit->resourceFactory().createParticleSystem();
    auto graph = viskit->resourceFactory().createGraph();

    // create random RN and reverse NN generator
    auto randomGenerator = viskit->resourceFactory().createGraphGenerator(viskit::GraphGeneratorType::Random);
    auto reverseGenerator = viskit->resourceFactory().createGraphGenerator(viskit::GraphGeneratorType::Reverse);

    // create caster
    const auto casterForceDirected = viskit->resourceFactory().createCaster(viskit::CasterType::IVHD, viskit::OptimizerType::ForceDirected);
    const auto casterRandom = viskit->resourceFactory().createCaster(viskit::CasterType::Random, viskit::OptimizerType::None);

    // load dataset to specified particle system
    parser->loadFile("/home/bartek/Repositories/mnist.csv", *particleSystem);

    // load graph from specified file and generate 1 random neighbor
    graph->loadFromCache("/home/bartek/Repositories/mnist.knn");
    randomGenerator->generate(*particleSystem, *graph, 1, true);
    reverseGenerator->generate(*particleSystem, *graph, 1, true);

    // set random positions
    casterRandom->calculatePositions(*particleSystem);

    // initialize and subscribe to on casting step finished
    casterForceDirected->initialize(*particleSystem, *graph);

    int i = 0;
    viskit->subscribeOnCastingStepFinish([&i]
    {
        if (i % 200==0) { std::cout << "Step: " << i << std::endl; }
        i++;
    });

    // perform casting for 2000 steps
    for (auto j = 0; j < 6000; j++)
    {
        viskit->computeCastingStep(*particleSystem, *graph, *casterForceDirected);
    }

    casterForceDirected->finalize();
    // perform casting for 150 steps
    for (auto j = 0; j < 200; j++)
    {
        viskit->computeCastingStep(*particleSystem, *graph, *casterForceDirected);
    }

    const auto metricCalculator = viskit->resourceFactory().createMetricCalculator();
    std::cout << "k = 2: " << metricCalculator->calculate(*particleSystem, 2) << std::endl;
    std::cout << "k = 10: " << metricCalculator->calculate(*particleSystem, 10) << std::endl;
    std::cout << "k = 100: " << metricCalculator->calculate(*particleSystem, 100) << std::endl;

    // calculateMetrics(*viskit, *particleSystem);

    return 0;
}

