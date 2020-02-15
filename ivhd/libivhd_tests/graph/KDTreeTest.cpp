///
/// \author Bartosz Minch <minch@agh.edu.pl>
/// \date 13.07.2019
///

#include <gtest/gtest.h>
#include <mutex>
#include <thread>
#include <core/Core.h>
#include <particles/ParticleSystem.h>
#include <graph/Graph.h>
#include <parse/ParserCsv.h>
#include <graph/generate/KDTree.h>
#include <ivhd/Structures.h>
#include "TestUtils.h"

using namespace ivhd;

namespace libivhd_test
{
	static int numQueriesProcessed;
	static int correctCount;
	static std::mutex mutex;
	static const int kNumThreads = 8;
	bool setDistancesToOne{ true };

	static void kNNQueryThread(int start, int end, const graph::generate::KDTree& kd, size_t k, const particles::Dataset& data, graph::Graph& graph) {
		for (int i = start; i < end; i++) {
			const auto& p = data[i];
			std::vector<std::pair<float, DataPoint>> pred = kd.kNN(p.first, k);
			{
				std::scoped_lock lock(mutex);

				auto id = p.first.getId();

				for (auto& elem : pred)
				{
					if (setDistancesToOne)
					{
						graph.addNeighbors(ivhd::Neighbors(id, elem.second.getId(), 1.0f, NeighborsType::Near));
					}
					else
					{
						graph.addNeighbors(ivhd::Neighbors(id, elem.second.getId(), elem.first, NeighborsType::Near));
					}
				}
			}
		}
	}

	TEST(KDTree, Generation)
	{
		using Logs = std::pair<ivhd::LogLevel, std::string>;

		std::vector<Logs> logs{};
		size_t count = 0;

		auto handler = [&logs, &count](ivhd::LogLevel level, std::string message)
		{
			logs.push_back(std::make_pair(level, message));
			count++;
		};

		core::Core core{ handler };
		parse::ParserCSV parser{ core.system() };
		graph::Graph graph{ core.system() };
		particles::ParticleSystem particleSystem{ core.system() };

		auto csvFile = test_utils::resourcesDirectory().string() + "/mnist_20_pca30.csv";
		parser.loadFile(csvFile, particleSystem);

		// Part responsible for creating a tree
		auto data = particleSystem.originalCoordinates();

		graph::generate::KDTree kd(data, 30);

		//ASSERT_EQ(sanityPass, true);

		// Evaluate performance on test set
		size_t k = 3; // Number of nearest neighbors
		numQueriesProcessed = 0;
		correctCount = 0;
		size_t queriesPerThread = particleSystem.countParticles() / kNumThreads;
		std::vector<std::thread> threads;

		for (int i = 0; i < kNumThreads; i++)
		{
			int start = i * queriesPerThread;
			int end = (i == kNumThreads - 1) ? particleSystem.countParticles() : start + queriesPerThread;
			threads.push_back(std::thread(kNNQueryThread, start, end, std::ref(kd), k, std::ref(data), std::ref(graph)));
		}

		auto profiler = utils::TimeProfiler(true);
		profiler.start();
		for (std::thread& t : threads)
		{
			t.join();
		}
		profiler.stop();
		profiler.measurementMs();

		graph.sort();

		/*std::ofstream m_file;

		m_file.open("kNN_graph_kdd.txt");
		for (int i = 0; i < graph.neighborsCount(); i++)
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
		}*/
	}
}

//int main(int argc, char** argv) {
//	::testing::InitGoogleTest(&argc, argv);
//	::testing::GTEST_FLAG(filter) = "KDTree*";
//	return RUN_ALL_TESTS();
//}