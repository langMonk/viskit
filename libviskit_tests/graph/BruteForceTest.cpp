///
/// \author Bartosz Minch <minch@agh.edu.pl>
/// \date 13.07.2019
///

#include <gtest/gtest.h>

#include <graph/generate/BruteForce.h>
#include <graph/generate/Random.h>
#include <viskit/Structures.h>
#include <utils/TimeProfiler.h>

#include "TestUtils.h"
#include "ViskitTest.h"

namespace viskit_test
{
    class BruteForceTest : public ViskitTest {};

	TEST_F(BruteForceTest, Generation)
	{
		generate::BruteForce nearestGenerator{ core->system() };
		generate::Random randomGenerator{ core->system() };

		auto csvFile = utils::resourcesDirectory().string() + "/mnist_7k_pca30.csv";
		parser->loadFile(csvFile, *particleSystem);

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

		utils::dump(*graph, "./", "test_brute");
	}

	TEST(Graph, SaveLoad)
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
		generate::Random randomGenerator{ core.system() };
		Graph graph{ core.system() };
		
		auto csvFile = utils::resourcesDirectory().string() + "/mnist_7k_pca30.csv";
		parser.loadFile(csvFile, particleSystem);

		EXPECT_EQ(particleSystem.countParticles(), 7000);
		EXPECT_EQ(particleSystem.originalCoordinates().size(), 7000);

		nearestGenerator.generate(particleSystem, graph, 2, true);
        randomGenerator.generate(particleSystem, graph, 1, true);
		
		graph.saveToCache("MNIST7k.knn");
		graph.clear();

		EXPECT_EQ(graph.size(), 0);
		EXPECT_EQ(graph.overallNeighborsCount(), 0);

		graph.loadFromCache("MNIST7k.knn");
		
		// we are loading only nearest neighbors from cache (random must be generated if needed)
		EXPECT_EQ(graph.overallNeighborsCount(), 14000);
		EXPECT_EQ(graph.size(), 7000);
	}
}