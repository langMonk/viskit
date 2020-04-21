#include "graph/generate/GraphGenerator.h"
#include "utils/Math.h"

namespace ivhd::graph::generate
{ 
	GraphGenerator::GraphGenerator(core::System& system)
		: m_ext_system(system)
	{
	}

	void GraphGenerator::generateRandomNeighbors(particles::ParticleSystem& ps, graph::Graph& graph, size_t k, bool distancesEqualOne)
	{
		m_ext_system.logger().logInfo("[kNN Generator] Searching for random neighbors...");

		for (size_t i = 0; i < ps.countParticles(); i++)
		{
			for (auto random = 0; random < k; random++)
			{
				while (true)
				{
					const auto j = math::randInt(0, ps.countParticles());
					if (j != i)
					{
						if (!alreadyNeighbors(i, j, graph))
						{
							auto distance = 1.0f;
							if (!distancesEqualOne)
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

		graph.randomNeighborsCount(k);
		auto count = graph.neighborsCount();
		m_ext_system.logger().logInfo("[kNN Generator] Neighbors in graph: " + std::to_string(count));
		m_ext_system.logger().logInfo("[kNN Generator] Finished.");
	}

	bool GraphGenerator::alreadyNeighbors(size_t index1, size_t index2, Graph& graph)
	{
		if(const auto neighbors = graph.getNeighbors(index1))
		{
			for (const auto neighbor : *neighbors)
			{
				if(neighbor.j == index2)
				{
					return true;
				}
			}
		}
		return false;
	}


}
