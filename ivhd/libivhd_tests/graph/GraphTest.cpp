///
/// \author Bartosz Minch <minch@agh.edu.pl>
/// \date 13.07.2019
///

#include <gtest/gtest.h>
#include <iostream>
#include <core/Core.h>
#include <particles/ParticleSystem.h>
#include <graph/Graph.h>
#include <parse/ParserCsv.h>
#include <graph/GraphGenerator.h>
#include <graph/KDTree.h>
#include <graph/Point.h>
#include <ivhd/Structures.h>
#include <utils/TimeProfiler.h>
#include "TestUtils.h"

using namespace ivhd;

TEST(Graph, Generation)
{
	using Logs = std::pair<LogLevel, std::string>;

	std::vector<Logs> logs{};
	size_t count = 0;

	auto handler = [&logs, &count](LogLevel level, std::string message)
	{
		logs.push_back(std::make_pair(level, message));
		count++;
	};

	core::Core core{ handler };
	parse::ParserCSV parser{ core.system() };
	particles::ParticleSystem particleSystem{ core.system() };
	graph::GraphGenerator generator{particleSystem, false};

	auto graph = particleSystem.neighbourhoodGraph();

	auto csvFile = test_utils::resourcesDirectory().string() + "/mnist_7k_pca30.csv";
	parser.loadFile(csvFile, 7000, particleSystem);
	
	auto profiler = utils::TimeProfiler(true);
	profiler.start();
	generator.bruteForceKNN(3, 0, 0);
	profiler.stop();
	profiler.measurementMs();

	std::ofstream m_file;
	m_file.open("kNN_graph.txt");
	for (int i = 0; i < graph->neighborsCount(); i++)
	{
		auto neighbors = graph->getNeighbors(i);
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

	size_t kNN_count = graph->neighborsCount();
	EXPECT_EQ(kNN_count, 21000); //every point has 3 NN
}

