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
#include <ivhd/Structures.h>
#include <utils/TimeProfiler.h>
#include "TestUtils.h"

using namespace ivhd;

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
		generate::BruteForce generator{ core.system() };
		Graph graph{ core.system() };

		auto csvFile = utils::resourcesDirectory().string() + "/mnist_7k_pca30.csv";
		parser.loadFile(csvFile, particleSystem);

		EXPECT_EQ(particleSystem.countParticles(), 7000);
		EXPECT_EQ(particleSystem.originalCoordinates().size(), 7000);

		auto profiler = ivhd::utils::TimeProfiler(true);
		profiler.start();
		generator.generateNearestNeighbors(particleSystem, graph, 3);
		profiler.stop();
		profiler.measurementMs();

		EXPECT_EQ(graph.size(), 7000); // 7000 elements (size) and every has 3 NN 
		EXPECT_EQ(graph.neighborsCount(), 21000);

		utils::dump(graph, "D:\\Repositories\\ivhd", "test_brute");
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
		generate::BruteForce generator{ core.system() };
		Graph graph{ core.system() };
		
		auto csvFile = utils::resourcesDirectory().string() + "/mnist_7k_pca30.csv";
		parser.loadFile(csvFile, particleSystem);

		EXPECT_EQ(particleSystem.countParticles(), 7000);
		EXPECT_EQ(particleSystem.originalCoordinates().size(), 7000);

		generator.generateNearestNeighbors(particleSystem, graph, 3);
		generator.generateRandomNeighbors(particleSystem, graph, 1);
		

		graph.saveToCache("MNIST7k.graph");
		graph.clear();

		EXPECT_EQ(graph.size(), 0);
		EXPECT_EQ(graph.neighborsCount(), 0);

		graph.loadFromCache("MNIST7k.graph");
		
		EXPECT_EQ(graph.neighborsCount(), 28000);
		EXPECT_EQ(graph.size(), 7000);
	}
}


int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}