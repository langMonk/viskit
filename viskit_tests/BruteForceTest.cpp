///
/// \author Bartosz Minch <minch@agh.edu.pl>
/// \date 13.07.2019
///

#include <gtest/gtest.h>

#include <viskit/graph/generate/BruteForce.h>
#include <viskit/graph/generate/Random.h>
#include <viskit/viskit/Structures.h>
#include <viskit/utils/TimeProfiler.h>

#include <viskit_tests/TestUtils.h>
#include <viskit_tests/ViskitTest.h>

using Logs = std::pair<LogLevel, std::string>;

TEST(BruteForceTest, Generation)
{
    std::vector<Logs> logs;
    auto logsCount = 0;
    auto handler = [&](viskit::LogLevel level, const std::string &message)
    {
        logs.emplace_back(level, message);
        logsCount++;
    };

    std::shared_ptr<core::Core> core = std::make_shared<core::Core>(handler);
    std::shared_ptr<particles::ParticleSystem> particleSystem = std::make_shared<particles::ParticleSystem>(core->system());
    std::shared_ptr<parse::ParserCSV> parser = std::make_shared<parse::ParserCSV>(core->system());
    std::shared_ptr<Graph> graph = std::make_shared<Graph>(core->system());

    generate::BruteForce nearestGenerator{ core->system() };
    generate::Random randomGenerator{ core->system() };

    auto csvFile = resourcesDirectory().string() + "/mnist_7k_pca30.csv";
    parser->loadFile(csvFile, "", *particleSystem);

    EXPECT_EQ(particleSystem->countParticles(), 7000);
    EXPECT_EQ(particleSystem->originalCoordinates().size(), 7000);

    auto profiler = viskit::utils::TimeProfiler(true);
    profiler.start();
    nearestGenerator.generate(*particleSystem, *graph, 2, true);
    randomGenerator.generate(*particleSystem, *graph, 1, true);
    profiler.stop();
    profiler.measurementMs();

    EXPECT_EQ(graph->size(), 7000);
    EXPECT_EQ(graph->overallNeighborsCount(), 21000); // 7000 elements (size) and every has 3 NN

    dump(*graph, "./", "test_brute");
}
