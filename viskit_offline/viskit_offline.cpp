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

void dropVisualizationToTxtFile(const std::shared_ptr<viskit::IParticleSystem>& ps)
{
    auto positions = ps->positions();
    auto labels = ps->labels();

    std::ofstream file("./visualization.txt");
    for(auto i = 0; i < ps->countParticles(); i++)
    {
        file << positions[i].x << " " << positions[i].y << " " << labels[i] << std::endl;
    }
    file.close();
}

void performVisualization(std::string dataset_path, int iterations, int nn, int rn)
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

    const auto casterForceDirected = viskit->resourceFactory().createCaster(
            viskit::CasterType::IVHD,
            viskit::OptimizerType::ForceDirected
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
    casterForceDirected->initialize(*particleSystem, *graph);

    int i = 0;
    viskit->subscribeOnCastingStepFinish([&i]
    {
     if (i % 200==0) { std::cout << "Step: " << i << std::endl; }
     i++;
    });

    // perform casting for N steps
    for (auto j = 0; j < iterations; j++)
    {
        viskit->computeCastingStep(*particleSystem, *graph, *casterForceDirected);
    }

    casterForceDirected->finalize();
    // perform casting for 200 steps
//    for (auto j = 0; j < 200; j++)
//    {
//        viskit->computeCastingStep(*particleSystem, *graph, *casterForceDirected);
//    }

    calculateMetrics(*viskit, particleSystem);
    dropVisualizationToTxtFile(particleSystem);
}

int main(int argc, char** argv)
{
    const auto dataset_file_path = argv[1];
    const auto iterations = argv[2];
    const auto nn = argv[3];
    const auto rn = argv[4];

    performVisualization(dataset_file_path, std::stoi(iterations), std::stoi(nn), std::stoi(rn));

    return 0;
}

