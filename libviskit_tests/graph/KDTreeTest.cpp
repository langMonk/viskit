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
#include <parse/ParserCSV.h>
#include <graph/generate/KDTree.h>
#include <ivhd/Structures.h>
#include "TestUtils.h"
#include "utils/Math.h"
#include "utils/TimeProfiler.h"

using namespace ivhd;

namespace libivhd_test
{
	static int numQueriesProcessed;
	static int correctCount;
	static std::mutex mutex;
	static const int kNumThreads = 8;
	bool setDistancesToOne{ true };

	bool alreadyNeighbors(size_t index1, size_t index2, Graph& graph)
	{
		if (const auto neighbors = graph.getNeighbors(index1))
		{
			for (const auto neighbor : *neighbors)
			{
				if (neighbor.j == index2)
				{
					return true;
				}
			}
		}
		return false;
	}
	
	static void kNNQueryThread(const size_t start, const size_t end, const generate::KDTree& kd, size_t k, size_t k_r, particles::ParticleSystem& ps, Graph& graph) 
	{
		for (size_t i = start; i < end; i++)
		{
			const auto& p = ps.originalCoordinates()[i];
			std::vector<std::pair<float, DataPoint>> pred = kd.kNN(p.first, k);
			{
				std::scoped_lock lock(mutex);

				for (auto& elem : pred)
				{
					if (setDistancesToOne)
					{
						graph.addNeighbors(ivhd::Neighbors(i,elem.second.getId(), 1.0f, NeighborsType::Near));
					}
					else
					{
						graph.addNeighbors(ivhd::Neighbors(i, elem.second.getId(), elem.first, NeighborsType::Near));
					}
				}
			}
		}

		for (size_t i = start; i < end; i++)
		{
			for (auto random = 0; random < k_r; random++)
			{
				while (true)
				{
					const auto j = math::randInt(0, ps.countAwakeParticles());
					if (j != i)
					{
						if (!alreadyNeighbors(i, j, graph))
						{
							auto distance = 1.0f;
							if (!setDistancesToOne)
							{
								distance = ps.vectorDistance(i, j);
							}

							graph.addNeighbors(Neighbors{ i, j, distance, NeighborsType::Random });
							break;
						}
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

		auto handler = [&logs, &count](LogLevel level, const std::string& message)
		{
			logs.emplace_back(level, message);
			count++;
		};

		core::Core core{ handler };
		parse::ParserCSV parser{ core.system() };
		Graph graph{ core.system() };
		particles::ParticleSystem particleSystem{ core.system() };

		auto csvFile = utils::resourcesDirectory().string() + "/mnist_7k_pca30.csv";
		parser.loadFile(csvFile, particleSystem);

		graph.initialize(particleSystem.countParticles());
		
		// Part responsible for creating a tree
		auto data = particleSystem.originalCoordinates();

		generate::KDTree kd(data, 30);

		// Evaluate performance on test set
		size_t k = 3; // Number of nearest neighbors
		size_t k_r = 1; // Number of nearest neighbors
		numQueriesProcessed = 0;
		correctCount = 0;
		size_t queriesPerThread = particleSystem.countParticles() / kNumThreads;
		std::vector<std::thread> threads;

		for (auto i = 0; i < kNumThreads; i++)
		{
			size_t start = i * queriesPerThread;
			size_t end = (i == kNumThreads - 1) ? particleSystem.countParticles() : start + queriesPerThread;
			threads.emplace_back(kNNQueryThread, start, end, std::ref(kd), k, k_r, std::ref(particleSystem), std::ref(graph));
		}

		auto profiler = ivhd::utils::TimeProfiler(true);
		profiler.start();
		for (auto& t : threads)
		{
			t.join();
		}
		profiler.stop();
		profiler.measurementMs();

		graph.sort();

		utils::dump(graph, "./", "test_kd");
	}
}
