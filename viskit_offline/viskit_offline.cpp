///
/// \author Bartosz Minch <minch@agh.edu.pl> 
/// \date 23.06.2020
///

#include <memory>
#include <iostream>
#include <thread>
#include <fstream>
#include <utility>

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

void calculateMetrics(viskit::IInteractiveVisualization& viskit, const std::shared_ptr<viskit::IParticleSystem>& particleSystem)
{
    // create and calculate metric
    auto metricCalculator = viskit.resourceFactory().createMetricCalculator();
    std::cout << "k = 5: " << metricCalculator->calculate(*particleSystem, 5) << std::endl;
    std::cout << "k = 15: " << metricCalculator->calculate(*particleSystem, 15) << std::endl;
    std::cout << "k = 50: " << metricCalculator->calculate(*particleSystem, 50) << std::endl;
    std::cout << "k = 100: " << metricCalculator->calculate(*particleSystem, 100) << std::endl;
}

void performVisualization(std::string dataset_path, const std::string& output_path, int iterations, int nn, int rn,
                          int l1_steps, viskit::CasterType casterType, viskit::OptimizerType optimizerType)
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

    // create needed viskit resources
    auto parser = viskit->resourceFactory().createParser(viskit::ParserType::Csv);
    auto particleSystem = viskit->resourceFactory().createParticleSystem();
    auto graph = viskit->resourceFactory().createGraph();
    auto nearestGenerator = viskit->resourceFactory().createGraphGenerator(viskit::GraphGeneratorType::Faiss);
    auto randomGenerator = viskit->resourceFactory().createGraphGenerator(viskit::GraphGeneratorType::Random);

    const auto caster = viskit->resourceFactory().createCaster(
            casterType,
            optimizerType
    );

    const auto casterRandom = viskit->resourceFactory().createCaster(
            viskit::CasterType::Random,
            viskit::OptimizerType::None
            );

    parser->loadFile(std::move(dataset_path), *particleSystem);

    nearestGenerator->generate(*particleSystem, *graph, nn, true);
    randomGenerator->generate(*particleSystem, *graph, rn, true);

    // set random positions
    casterRandom->calculatePositions(*particleSystem);

    // initialize and subscribe to on casting step finished
    caster->initialize(*particleSystem, *graph);

    int i = 0;
    viskit->subscribeOnCastingStepFinish([&i, iterations]
    {
     if (i * 100 % iterations==0) { std::cout << "Step: " << i << std::endl; }
     i++;
    });

    // perform casting for N steps
    for (auto j = 0; j < iterations; j++)
    {
        viskit->computeCastingStep(*particleSystem, *graph, *caster);
    }

    // perform casting for l1_steps steps
    caster->finalize();
    for (auto j = 0; j < l1_steps; j++)
    {
        viskit->computeCastingStep(*particleSystem, *graph, *caster);
    }

    calculateMetrics(*viskit, particleSystem);
    particleSystem->saveToFile(output_path + "/visualization.txt");
}

int main(int argc, char** argv)
{
    const auto dataset_file_path = argv[1];
    const auto output_file_path = argv[2];
    const auto iterations = argv[3];
    const auto nn = argv[4];
    const auto rn = argv[5];
    const auto l1_steps = argv[6];

    //one of: adadelta, adam, forcedirected, momentum, nesterov, largevis, random
    std::string caster_name = argv[7];

    viskit::CasterType casterType = viskit::CasterType::IVHD;
    viskit::OptimizerType optimizerType = viskit::OptimizerType::None;

    if (caster_name == "adadelta")
        optimizerType = viskit::OptimizerType::Adadelta;
    else if (caster_name == "adam")
        optimizerType = viskit::OptimizerType::Adam;
    else if (caster_name == "forcedirected")
        optimizerType = viskit::OptimizerType::ForceDirected;
    else if (caster_name == "momentum")
        optimizerType = viskit::OptimizerType::Momentum;
    else if (caster_name == "nesterov")
        optimizerType = viskit::OptimizerType::Nesterov;
    else if (caster_name == "random")
        casterType = viskit::CasterType::Random;
    else if (caster_name == "largevis")
        casterType = viskit::CasterType::LargeVis;
    
    
    performVisualization(dataset_file_path, output_file_path, std::stoi(iterations),
                         std::stoi(nn), std::stoi(rn), std::stoi(l1_steps), casterType, optimizerType);

    return 0;
}

