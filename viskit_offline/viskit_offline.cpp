///
/// \author Bartosz Minch <minch@agh.edu.pl> 
/// \date 23.06.2020
///

#include <memory>
#include <iostream>
#include <fstream>
#include <utility>
#include <filesystem>
#include <boost/lexical_cast.hpp>


#include <viskit/viskit/InteractiveVisualizationBuilder.h>
#include <viskit/viskit/IResourceFactory.h>
#include <viskit/viskit/IParticleSystem.h>
#include <viskit/viskit/IGraph.h>
#include <viskit/viskit/IParser.h>
#include <viskit/viskit/ICaster.h>
#include <viskit/viskit/IGraphGenerator.h>
#include <viskit/viskit/IMetric.h>
#include <viskit/viskit/Structures.h>

using Logs = std::pair<viskit::LogLevel, std::string>;
using std::filesystem::current_path;


void performVisualization(std::string dataset_path, const std::string& graph_file_path, const std::string& output_file_path, int iterations, int nn, int rn,
                          bool distancesEqualOne, int l1_steps, viskit::CasterType casterType, viskit::OptimizerType optimizerType)
{
    // initialize logging handler
    auto logsCount = 0;
    std::vector <Logs> logs{};

    auto handler = [&](viskit::LogLevel level, const std::string &message)
    {
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

    // create viskit
    auto viskit = viskit::createViskit(handler);

    // create needed viskit resources
    auto parser = viskit->resourceFactory().createParser(viskit::ParserType::Csv);
    auto particleSystem = viskit->resourceFactory().createParticleSystem();
    auto graph = viskit->resourceFactory().createGraph();
    auto randomGraphGenerator = viskit->resourceFactory().createGraphGenerator(viskit::GraphGeneratorType::Random);

    const auto caster = viskit->resourceFactory().createCaster(
            casterType,
            optimizerType
            );

    const auto casterRandom = viskit->resourceFactory().createCaster(
            viskit::CasterType::Random,
            viskit::OptimizerType::None
            );

    parser->loadFile(std::move(dataset_path), *particleSystem);

    if(graph->loadFromCache(graph_file_path, nn))
    {
        randomGraphGenerator->generate(*particleSystem, *graph, rn, distancesEqualOne);

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

        particleSystem->saveToFile(output_file_path);
    }
}

int main(int argc, char** argv)
{
    const auto dataset_file_path = argv[1];
    const auto graph_file_path = argv[2];
    const auto output_file_path = argv[3];
    const auto iterations = argv[4];
    const auto nn = argv[5];
    const auto rn = argv[6];
    const auto distancesEqualOne = argv[7];
    const auto l1_steps = argv[8];
    std::string caster_name = argv[9];

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
    else if (caster_name == "tsne")
        optimizerType = viskit::OptimizerType::tSNE;
    
    performVisualization(dataset_file_path, graph_file_path, output_file_path, std::stoi(iterations),
                         std::stoi(nn), std::stoi(rn), boost::lexical_cast<bool>(distancesEqualOne), std::stoi(l1_steps), casterType, optimizerType);

    return 0;
}

