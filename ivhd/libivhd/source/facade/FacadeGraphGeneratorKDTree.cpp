#include "facade\FacadeGraphGeneratorKDTree.h"

namespace ivhd::facade
{ 
	void FacadeGraphGeneratorKDTree::kNNQueryThread(int start, int end, bool setDistancesToOne, const graph::generate::KDTree& kd, size_t k, const particles::Dataset& data, graph::Graph& graph) {
		for (int i = start; i < end; i++) {
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
		}
	}

	std::shared_ptr<IGraph> ivhd::facade::FacadeGraphGeneratorKDTree::generate(std::shared_ptr<ivhd::IParticleSystem>& ps)
	{
		// Part responsible for creating a tree
		auto data = ps->originalCoordinates();

		graph::generate::KDTree kd(data, data[0].first.size());

		// Evaluate performance on test set
		size_t k = 3; // Number of nearest neighbors
		static int numQueriesProcessed = 0;
		static int correctCount = 0;
		static const int kNumThreads = 8;
		bool setDistancesToOne{ true };

		size_t queriesPerThread = ps->countParticles() / kNumThreads;
		std::vector<std::thread> threads;

		for (int i = 0; i < kNumThreads; i++)
		{
			int start = i * queriesPerThread;
			int end = (i == kNumThreads - 1) ? ps->countParticles() : start + queriesPerThread;
			threads.push_back(std::thread(kNNQueryThread, start, end, setDistancesToOne, 
					std::ref(kd), k, std::ref(data), std::ref(m_graph)));
		}

		auto profiler = utils::TimeProfiler(true);
		profiler.start();
		for (std::thread& t : threads)
		{
			t.join();
		}
		profiler.stop();
		profiler.measurementMs();

		return std::make_shared<facade::FacadeGraph>();
	}
}
