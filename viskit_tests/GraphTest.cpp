///
/// \author Bartosz Minch <minch@agh.edu.pl>
/// \date 13.09.2021
///

#include <gtest/gtest.h>

#include <viskit/viskit/Structures.h>
#include <viskit_tests/TestUtils.h>
#include <viskit_tests/ViskitTest.h>

using Logs = std::pair<LogLevel, std::string>;

TEST(Graph, SaveLoad) {
    std::vector<Logs> logs{};
    size_t count = 0;

    auto handler = [&logs, &count](LogLevel level, const std::string &message) {
        logs.emplace_back(level, message);
        count++;
    };

    core::Core core{handler};
    parse::ParserCSV parser{core.system()};
    particles::ParticleSystem particleSystem{core.system()};
    Graph graph{core.system()};

    auto csvFile = resourcesDirectory().string() + "/mnist_7k_pca30.csv";
    auto graphFile = resourcesDirectory().string() + "/mnist_7k_graph.bin";
    parser.loadFile(csvFile, particleSystem);

    EXPECT_EQ(particleSystem.countParticles(), 7000);
    EXPECT_EQ(particleSystem.originalCoordinates().size(), 7000);

    graph.loadFromCache(graphFile, 3);
    EXPECT_EQ(graph.overallNeighborsCount(), 21000);

    graph.clear();
}
