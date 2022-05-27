///
/// \author Bartosz Minch <minch@agh.edu.pl>
/// \date 23.06.2020
///

#include <boost/lexical_cast.hpp>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <utility>

#include <viskit/viskit/ICaster.h>
#include <viskit/viskit/IGraph.h>
#include <viskit/viskit/IGraphGenerator.h>
#include <viskit/viskit/IMetric.h>
#include <viskit/viskit/IParser.h>
#include <viskit/viskit/IParticleSystem.h>
#include <viskit/viskit/IResourceFactory.h>
#include <viskit/viskit/InteractiveVisualizationBuilder.h>
#include <viskit/viskit/Structures.h>

using Logs = std::pair<viskit::LogLevel, std::string>;
using std::filesystem::current_path;

void performVisualization(const std::string& datasetFilePath,
    const std::string& labelsFilePath,
    const std::string& graphFilePath,
    const std::string& outputFilePath,
    int iterations,
    int nearestNeighborsCount,
    int randomNeighborsCount,
    bool binaryDistances,
    int reverseNeighborsSteps,
    int reverseNeighborsCount,
    int l1Steps,
    viskit::CasterType casterType,
    viskit::OptimizerType optimizerType)
{
    auto logsCount = 0;
    std::vector<Logs> logs {};

    auto handler = [&](viskit::LogLevel level, const std::string& message) {
        logs.emplace_back(level, message);
        switch (level) {

        case viskit::LogLevel::Debug:
            std::cout << "[Debug] " << message << std::endl;
            break;
        case viskit::LogLevel::Info:
            std::cout << "[Info] " << message << std::endl;
            break;
        case viskit::LogLevel::Warning:
            std::cout << "[Warning] " << message << std::endl;
            break;
        case viskit::LogLevel::Error:
            std::cout << "[Error] " << message << std::endl;
            break;
        }
        logsCount++;
    };

    auto viskit = viskit::createViskit(handler);
    auto parser = viskit->resourceFactory().createParser(viskit::ParserType::Csv);
    auto particleSystem = viskit->resourceFactory().createParticleSystem();
    auto graph = viskit->resourceFactory().createGraph();
    auto graphHelper = viskit->resourceFactory().createGraph();
    auto randomGraphGenerator = viskit->resourceFactory().createGraphGenerator(
        viskit::GraphGeneratorType::Random);
    const auto caster = viskit->resourceFactory().createCaster(casterType, optimizerType);
    const auto casterRandom = viskit->resourceFactory().createCaster(
        viskit::CasterType::Random, viskit::OptimizerType::None);

    try {
        parser->loadFile(datasetFilePath, labelsFilePath, *particleSystem);
    }
    catch (std::exception& ex) {
        return;
    }

    graph->loadNearestNeighborsFromCache(graphFilePath, nearestNeighborsCount, binaryDistances);

    if (reverseNeighborsCount > 0) {
        graphHelper->loadNearestNeighborsFromCache(graphFilePath,
            reverseNeighborsCount, binaryDistances);
    }

    randomGraphGenerator->generate(*particleSystem, *graph, randomNeighborsCount, binaryDistances);
    casterRandom->calculatePositions(*particleSystem);

    caster->initialize(*particleSystem, *graph);
    int i = 0;
    viskit->subscribeOnCastingStepFinish([&i] {
        if (i % 100 == 0) {
            std::cout << "Step: " << i << std::endl;
        }
        i++;
    });

    //    viskit->subscribeOnCastingStepFinish([&i, &randomGraphGenerator, &particleSystem, &graph, &graphHelper, &randomNeighborsCount, &binaryDistances]  {
    //        if (i % 100 == 0) {
    //            std::cout << "Step: " << i << std::endl;
    //        }
    //        if (i % 50 == 0)
    //        {
    //            graph->removeRandomNeighbors();
    //
    //            randomNeighborsCount > 0 ?
    //            randomGraphGenerator->generate(*particleSystem, *graph, *graphHelper, randomNeighborsCount, binaryDistances)
    //            : randomGraphGenerator->generate(*particleSystem, *graph, randomNeighborsCount, binaryDistances);
    //        }
    //        i++;
    //    });

    for (auto j = 0; j < iterations; j++) {
        viskit->computeCastingStep(*particleSystem, *graph, *caster);
    }

    if (reverseNeighborsSteps > 0) {
        auto reverseGraphGenerator = viskit->resourceFactory().createGraphGenerator(
            viskit::GraphGeneratorType::Reverse);
        reverseGraphGenerator->generate(*particleSystem, *graph, *graphHelper);
        graph->removeRandomNeighbors();
        randomGraphGenerator->generate(*particleSystem, *graph, *graphHelper, randomNeighborsCount, binaryDistances);
        for (auto j = 0; j < reverseNeighborsSteps; j++) {
            viskit->computeCastingStep(*particleSystem, *graph, *caster);
        }
    }

    caster->finalize();
    for (auto j = 0; j < l1Steps; j++) {
        viskit->computeCastingStep(*particleSystem, *graph, *caster);
    }

    particleSystem->saveToFile(outputFilePath, *graph);
}

int main([[maybe_unused]] int argc, char** argv)
{
    std::string datasetFilePath;
    std::string labelsFilePath;
    std::string graphFilePath;
    std::string outputFilePath;
    int iterations;
    int nearestNeighborsCount;
    int randomNeighborsCount;
    int binaryDistances;
    int reverseNeighborsSteps;
    int reverseNeighborsCount;
    int l1Steps;
    std::string caster_name;

    switch (argc) {
    case 5:
        datasetFilePath = argv[1];
        labelsFilePath = argv[2];
        graphFilePath = argv[3];
        outputFilePath = argv[4];
        iterations = 2500;
        nearestNeighborsCount = 2;
        randomNeighborsCount = 1;
        binaryDistances = true;
        reverseNeighborsSteps = 0;
        reverseNeighborsCount = 0;
        l1Steps = 0;
        caster_name = "force-directed";
        break;

    case 1:
    case 2:
    case 3:
    case 4:
        throw std::invalid_argument("Invalid argument number. At least 4 paths are required: dataset, labels, graph, output or all 12 parameters");

    case 13:
        datasetFilePath = argv[1];
        labelsFilePath = argv[2];
        graphFilePath = argv[3];
        outputFilePath = argv[4];
        iterations = std::stoi(argv[5]);
        nearestNeighborsCount = std::stoi(argv[6]);
        randomNeighborsCount = std::stoi(argv[7]);
        binaryDistances = boost::lexical_cast<bool>(argv[8]);
        reverseNeighborsSteps = std::stoi(argv[9]);
        reverseNeighborsCount = std::stoi(argv[10]);
        l1Steps = std::stoi(argv[11]);
        caster_name = argv[12];
        break;

    default:
        throw std::invalid_argument("Invalid argument number. At least 4 paths are required: dataset, labels, graph, output or all 12 parameters");
    }

    viskit::CasterType casterType = viskit::CasterType::IVHD;
    viskit::OptimizerType optimizerType = viskit::OptimizerType::None;

    if (caster_name == "adadelta")
        optimizerType = viskit::OptimizerType::Adadelta;
    else if (caster_name == "adam")
        optimizerType = viskit::OptimizerType::Adam;
    else if (caster_name == "force-directed")
        optimizerType = viskit::OptimizerType::ForceDirected;
    else if (caster_name == "momentum")
        optimizerType = viskit::OptimizerType::Momentum;
    else if (caster_name == "nesterov")
        optimizerType = viskit::OptimizerType::Nesterov;
    else if (caster_name == "random")
        casterType = viskit::CasterType::Random;
    else if (caster_name == "largevis")
        casterType = viskit::CasterType::LargeVis;
    else if (caster_name == "t-sne")
        optimizerType = viskit::OptimizerType::tSNE;

    performVisualization(datasetFilePath, labelsFilePath, graphFilePath, outputFilePath,
        iterations, nearestNeighborsCount,
        randomNeighborsCount,
        binaryDistances,
        reverseNeighborsSteps, reverseNeighborsCount, l1Steps,
        casterType, optimizerType);

    return 0;
}

// Example usage:
// viskit_offline "./datasets/mnist_data.csv" "./labels/mnist_labels.csv" "./graphs/mnist.bin" ./visualization.txt 2500 2 1 1 0 0 0 "force-directed"
// viskit_offline "./datasets/mnist_data.csv" "./labels/mnist_labels.csv" "./graphs/mnist.bin" ./visualization.txt