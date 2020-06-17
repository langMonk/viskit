///
/// \author Bartosz Minch <minch@agh.edu.pl>
/// \date 13.07.2019
///

#include <gtest/gtest.h>
#include <core/Core.h>
#include <particles/ParticleSystem.h>
#include <graph/Graph.h>
#include <parse/ParserCSV.h>
#include <graph/generate/BruteForce.h>
#include <graph/generate/Random.h>
#include <viskit/Structures.h>
#include <utils/TimeProfiler.h>
#include "TestUtils.h"

using namespace viskit;

void saveToPlainText(Graph& graph)
{
	std::ofstream m_file;
	m_file.open("kNN_graph.txt");
	
	for (auto i = 0; i < graph.size(); i++)
	{
		if (const auto neighbors = graph.getNeighbors(i))
		{
			for (const auto neighbor : *neighbors)
			{
				if (neighbor.type == NeighborsType::Near)
				{
					m_file << neighbor.i << "," << neighbor.j << "," << neighbor.r << "," << "Near" << std::endl;
				}
				else if (neighbor.type == NeighborsType::Far)
				{
					m_file << neighbor.i << "," << neighbor.j << "," << neighbor.r << "," << "Far" << std::endl;
				}
				else
				{
					m_file << neighbor.i << "," << neighbor.j << "," << neighbor.r << "," << "Random" << std::endl;
				}
			}
		}
	}
}

namespace libivhd_test
{
	TEST(Graph, Generation)
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

		auto profiler = viskit::utils::TimeProfiler(true);
		profiler.start();
		nearestGenerator.generate(particleSystem, graph, 2, true);
		randomGenerator.generate(particleSystem, graph, 1, true);
		profiler.stop();
		profiler.measurementMs();

		EXPECT_EQ(graph.size(), 7000);
		EXPECT_EQ(graph.overallNeighborsCount(), 21000); // 7000 elements (size) and every has 3 NN

		utils::dump(graph, "./", "test_brute");
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