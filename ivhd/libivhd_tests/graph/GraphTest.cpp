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

namespace libivhd_test
{
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
		generate::BruteForce generator{ particleSystem };

		auto csvFile = test_utils::resourcesDirectory().string() + "/mnist_7k_pca30.csv";
		parser.loadFile(csvFile, particleSystem);

		EXPECT_EQ(particleSystem.countParticles(), 7000);
		EXPECT_EQ(particleSystem.originalCoordinates().size(), 7000);

		auto profiler = utils::TimeProfiler(true);
		profiler.start();
		generator.generate(3, 0, 0);
		profiler.stop();
		profiler.measurementMs();

		std::ofstream m_file;
		m_file.open("kNN_graph.txt");

		auto graph = particleSystem.neighbourhoodGraph();
		size_t kNN_count = graph.neighborsCount();
		for (int i = 0; i < kNN_count; i++)
		{
			auto neighbors = graph.getNeighbors(i);
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
		
		EXPECT_EQ(kNN_count, 21000); //every point has 3 NN
	}
}
