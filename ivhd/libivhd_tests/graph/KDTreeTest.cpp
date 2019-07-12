///
/// \author Bartosz Minch <minch@agh.edu.pl>
/// \date 13.07.2019
///

#include <gtest/gtest.h>
#include <iostream>
#include <mutex>
#include <thread>

#include <core/Core.h>
#include <particles/ParticleSystem.h>
#include <graph/Graph.h>
#include <parse/ParserCsv.h>
#include <graph/GraphGenerator.h>
#include <graph/KDTree.h>
#include <graph/Point.h>
#include "TestUtils.h"

using namespace ivhd;

static int numQueriesProcessed;
static int correctCount;
static std::mutex mutex;
static const int kNumThreads = 8;
bool setDistancesToOne{ true };

static void kNNQueryThread(int start, int end, const graph::KDTree& kd, size_t k, const particles::Dataset& data, graph::Graph& graph, particles::ParticleSystem& ps) {
	for (int i = start; i < end; i++) {
		const auto& p = data[i];
		std::vector<std::pair<float, graph::Point>> pred = kd.kNN(p.first, k);
		{
			std::scoped_lock lock(mutex);

			auto id = p.first.getId();

			for (auto& elem : pred)
			{
				if (setDistancesToOne)
				{
					graph.addNeighbors(graph::Neighbors(id, elem.second.getId(), 1.0f, NeighborsType::Near));
				}
				else
				{
					graph.addNeighbors(graph::Neighbors(id, elem.second.getId(), elem.first, NeighborsType::Near));
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
	graph::GraphGenerator generator{ particleSystem, graph, false };

	auto csvFile = test_utils::resourcesDirectory().string() + "/mnist_7k_pca30.csv";
	parser.loadFile(csvFile, 7000, particleSystem);

	// Part responsible for creating a tree
	auto data = particleSystem.originalCoordinates();

	graph::KDTree kd(data, 30);
	//std::cout << "Finished building KD-Tree!" << std::endl;

	//// Sanity check on the data set
	//bool sanityPass = true;
	//for (int i = 0; i < 1000; i++) {
	//	if (!kd.contains(data[i].first) || kd.kNNValue(data[i].first, 1) != data[i].second) {
	//		sanityPass = false;
	//		break;
	//	}
	//}

	//ASSERT_EQ(sanityPass, true);

	// Evaluate performance on test set
	size_t k = 3; // Number of nearest neighbors
	numQueriesProcessed = 0;
	correctCount = 0;
	int queriesPerThread = particleSystem.countParticles() / kNumThreads;
	std::vector<std::thread> threads;
	
	for (int i = 0; i < kNumThreads; i++) 
	{
		int start = i * queriesPerThread;
		int end = (i == kNumThreads - 1) ? particleSystem.countParticles() : start + queriesPerThread;
		threads.push_back(std::thread(kNNQueryThread, start, end, std::ref(kd), k, std::ref(data), std::ref(graph), std::ref(particleSystem)));
	}

	for (std::thread& t : threads)
	{
		t.join();
	}
}

