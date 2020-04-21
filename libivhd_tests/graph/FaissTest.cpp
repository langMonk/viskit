///
/// \author Bartosz Minch <minch@agh.edu.pl>
/// \date 13.07.2019
///

#include <gtest/gtest.h>
#include <core/Core.h>
#include <particles/ParticleSystem.h>
#include <graph/Graph.h>
#include <parse/ParserCSV.h>
#include <graph/generate/Faiss.h>
#include <ivhd/Structures.h>
#include <utils/TimeProfiler.h>
#include "TestUtils.h"

using namespace ivhd;

namespace libivhd_test
{
	TEST(Faiss, Generation)
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
		generate::Faiss generator{ core.system() };
		Graph graph{ core.system() };

		auto csvFile = utils::resourcesDirectory().string() + "/mnist_7k_pca30.csv";
		parser.loadFile(csvFile, particleSystem);

		EXPECT_EQ(particleSystem.countParticles(), 7000);
		EXPECT_EQ(particleSystem.originalCoordinates().size(), 7000);

		auto profiler = ivhd::utils::TimeProfiler(true);
		profiler.start();
		generator.generateNearestNeighbors(particleSystem, graph, 2);
		profiler.stop();
		profiler.measurementMs();

		EXPECT_EQ(graph.size(), 7000); // 7000 elements (size) and every has 2 NN 
		EXPECT_EQ(graph.neighborsCount(), 14000);

		utils::dump(graph, "./", "test_faiss");
	}
}


int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    ::testing::GTEST_FLAG(filter) = "Faiss*";
    return RUN_ALL_TESTS();
}