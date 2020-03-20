#include "facade/FacadeGraphGeneratorKDTree.h"

#include <utility>

namespace ivhd::facade
{

	FacadeGraphGeneratorKDTree::FacadeGraphGeneratorKDTree(std::shared_ptr<core::Core> core)
		: FacadeGraphGenerator(std::move(core))
	{
	}
	
	void FacadeGraphGeneratorKDTree::kNNQueryThread(int start, int end, bool setDistancesToOne, const graph::generate::KDTree& kd, size_t k, const particles::Dataset& data, graph::Graph& graph) {
		/*for (int i = start; i < end; i++) {
			const auto& p = data[i];
			std::vector<std::pair<float, graph::DataPoint>> pred = kd.kNN(p.first, k);
			{
				std::scoped_lock lock(m_generationMutex);

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
		}*/
	}

	// void FacadeGraphGeneratorKDTree::generate(size_t nearestNeighbors, size_t furthestNeighbors, size_t randomNeighbors, bool distancesEqualOne)
	// {
		// Part responsible for creating a tree
	//	auto data = m_ext_particleSystem.originalCoordinates();

	//	graph::generate::KDTree kd(data, data[0].first.size());

	//	// Evaluate performance on test set
	//	size_t k = 3; // Number of nearest neighbors
	//	static int numQueriesProcessed = 0;
	//	static int correctCount = 0;
	//	static const int kNumThreads = 8;
	//	bool setDistancesToOne{ true };

	//	size_t queriesPerThread = m_ext_particleSystem.countParticles() / kNumThreads;
	//	std::vector<std::thread> threads;

	//	for (int i = 0; i < kNumThreads; i++)
	//	{
	//		int start = i * queriesPerThread;
	//		int end = (i == kNumThreads - 1) ? m_ext_particleSystem.countParticles() : start + queriesPerThread;
	//		threads.push_back(std::thread(kNNQueryThread, start, end, setDistancesToOne, 
	//				std::ref(kd), k, std::ref(data), std::ref(m_graph)));
	//	}

	//	auto profiler = utils::TimeProfiler(true);
	//	profiler.start();
	//	for (std::thread& t : threads)
	//	{
	//		t.join();
	//	}
	//	profiler.stop();
	//	profiler.measurementMs();
	// }
}
