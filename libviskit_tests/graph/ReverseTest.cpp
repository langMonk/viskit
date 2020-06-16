///
/// \author Bartosz Minch <minch@agh.edu.pl>
/// \date 13.06.2020
///

#include <gtest/gtest.h>
#include <core/Core.h>
#include <particles/ParticleSystem.h>
#include <graph/Graph.h>
#include <parse/ParserCSV.h>
#include <graph/generate/BruteForce.h>
#include <graph/generate/Reverse.h>
#include <ivhd/Structures.h>
#include <utils/TimeProfiler.h>
#include "TestUtils.h"

using namespace ivhd;

namespace libivhd_test
{
    TEST(Reverse, Generation)
    {
        using Logs = std::pair<LogLevel, std::string>;

        std::vector<Logs> logs{};
        size_t count = 0;

        auto handler = [&logs, &count](LogLevel level, const std::string& message)
        {
            logs.emplace_back(level, message);
            count++;
        };

        core::Core core{ handler };
        parse::ParserCSV parser{ core.system() };
        particles::ParticleSystem particleSystem{ core.system() };
        generate::BruteForce nearestGenerator{ core.system() };
        generate::Reverse reverseGenerator{ core.system() };
        Graph graph{ core.system() };

        auto csvFile = utils::resourcesDirectory().string() + "/mnist_7k_pca30.csv";
        parser.loadFile(csvFile, particleSystem);

        EXPECT_EQ(particleSystem.countParticles(), 7000);
        EXPECT_EQ(particleSystem.originalCoordinates().size(), 7000);

        auto profiler = ivhd::utils::TimeProfiler(true);
        profiler.start();
        nearestGenerator.generate(particleSystem, graph, 2, true);
        reverseGenerator.generate(particleSystem, graph, 1, true);
        profiler.stop();
        profiler.measurementMs();

        EXPECT_EQ(graph.size(), 7000); // 7000 elements (size) and every has 3 NN
        EXPECT_EQ(graph.overallNeighborsCount(), 19669);

        utils::dump(graph, "./", "test_reverse");
    }
}