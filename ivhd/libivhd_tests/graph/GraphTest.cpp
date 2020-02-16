///
/// \author Bartosz Minch <minch@agh.edu.pl>
/// \date 13.07.2019
///

#include <gtest/gtest.h>
#include <core/Core.h>
#include <particles/ParticleSystem.h>
#include <graph/Graph.h>
#include <parse/ParserCsv.h>
#include <graph/generate/BruteForce.h>
#include <graph/DataPoint.h>
#include <ivhd/Structures.h>
#include <utils/TimeProfiler.h>
#include "TestUtils.h"

using namespace ivhd;

void saveToPlainText(Graph& graph)
{
	std::ofstream m_file;
	m_file.open("kNN_graph.txt");

	const auto kNN_count = graph.neighborsCount();
	
	for (auto i = 0; i < kNN_count; i++)
	{
		const auto neighbors = graph.getNeighbors(i);
		if (neighbors.type == NeighborsType::Near)
		{
			m_file << neighbors.i << "," << neighbors.j << "," << neighbors.r << "," << "Near" << std::endl;
		}
		else if (neighbors.type == NeighborsType::Far)
		{
			m_file << neighbors.i << "," << neighbors.j << "," << neighbors.r << "," << "Far" << std::endl;
		}
		else
		{
			m_file << neighbors.i << "," << neighbors.j << "," << neighbors.r << "," << "Random" << std::endl;
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
		generate::BruteForce generator{ core.system(), particleSystem };

		auto csvFile = test_utils::resourcesDirectory().string() + "/mnist_7k_pca30.csv";
		parser.loadFile(csvFile, particleSystem);

		EXPECT_EQ(particleSystem.countParticles(), 7000);
		EXPECT_EQ(particleSystem.originalCoordinates().size(), 7000);

		auto profiler = utils::TimeProfiler(true);
		profiler.start();
		generator.generate(3, 0, 0);
		profiler.stop();
		profiler.measurementMs();

		auto graph = particleSystem.neighbourhoodGraph();
		auto kNN_count = graph.neighborsCount();

		EXPECT_EQ(kNN_count, 21000); //every point has 3 NN
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
		generate::BruteForce generator{ core.system(), particleSystem };

		auto csvFile = test_utils::resourcesDirectory().string() + "/mnist_7k_pca30.csv";
		parser.loadFile(csvFile, particleSystem);

		EXPECT_EQ(particleSystem.countParticles(), 7000);
		EXPECT_EQ(particleSystem.originalCoordinates().size(), 7000);

		generator.generate(3, 0, 0);

		auto graph = particleSystem.neighbourhoodGraph();
		graph.saveToCache("MNIST7k");
		graph.clear();

		EXPECT_EQ(graph.size(), 0);

		graph.loadFromCache("MNIST7k");
		
		EXPECT_EQ(graph.size(), 21000);
	}
}
