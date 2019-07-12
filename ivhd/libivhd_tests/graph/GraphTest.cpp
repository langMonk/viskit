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
#include "TestUtils.h"

TEST(Graph, Generation)
{
	using Logs = std::pair<ivhd::LogLevel, std::string>;

	std::vector<Logs> logs{};
	size_t count = 0;

	auto handler = [&logs, &count](ivhd::LogLevel level, std::string message)
	{
		logs.push_back(std::make_pair(level, message));
		count++;
	};

	ivhd::core::Core core{ handler };
	ivhd::parse::ParserCSV parser{ core.system() };
	ivhd::graph::Graph graph{ core.system() };
	ivhd::particles::ParticleSystem particleSystem{ core.system() };
	ivhd::graph::GraphGenerator generator{particleSystem, graph, false};

	auto csvFile = test_utils::resourcesDirectory().string() + "/mnist_20_pca30.csv";
	parser.loadFile(csvFile, 20, particleSystem);

	generator.kNN(2, 1, 0);

	size_t kNN_count = graph.neighborsCount();
	EXPECT_EQ(kNN_count, 60); //every point has 3 NN
}

