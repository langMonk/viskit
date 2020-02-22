///
/// \author Bartosz Minch <minch@agh.edu.pl>
/// \date 12.05.2019
///

#include "graph/generate/BruteForce.h"
#include "utils/Math.h"

namespace ivhd::graph::generate
{
	BruteForce::BruteForce(core::System& system)
		: GraphGenerator(system)
	{
	}

	void BruteForce::generateRandomNeighbors(particles::ParticleSystem& ps, graph::Graph& graph, size_t k, bool distancesEqualOne)
	{
		std::vector<Neighbors> rand(k);

		for (size_t i = 0; i < ps.countAwakeParticles(); i++)
		{
			std::generate(rand.begin(), rand.end(), []()->Neighbors
			{
				Neighbors neighbors;
				neighbors.r = 0.0f;;
				return neighbors;
			});

			for (auto random = 0; random < k; random++)
			{
				while (true)
				{
					const auto j = math::randInt(0, ps.countAwakeParticles());
					if (j != i)
					{
						if (!alreadyNeighbors(i, j, graph))
						{
							auto distance = 1.0f;
							if (!m_distancesEqualOne)
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

	void BruteForce::generateNearestNeighbors(particles::ParticleSystem& ps, graph::Graph& graph, size_t k, bool distancesEqualOne)
	{
		graph.initialize(ps.countParticles());
		m_distancesEqualOne = distancesEqualOne;

		m_ext_system.logger().logInfo("[BruteForce Generator] Generating kNN Graph...");

		std::vector<Neighbors> near(k);


		for (size_t i = 0; i < ps.countAwakeParticles(); i++)
		{
			std::generate(near.begin(), near.end(), []()->Neighbors
			{
				Neighbors neighbors;
				neighbors.r = std::numeric_limits<float>::max();
				return neighbors;
			});

			for (size_t j = 0; j < ps.countAwakeParticles(); j++)
			{
				if (i != j)
				{
					const auto distance = ps.vectorDistance(i, j);
					addMinDist(near, distance, i, j, true);
				}
			}

			if (m_distancesEqualOne)
			{
				for (auto& element : near)
				{
					element.r = 1.0f;
				}
			}

			graph.addNeighbors(near);
		}
	}

	//void BruteForce::generate(size_t nearestNeighbors, size_t furthestNeighbors, size_t randomNeighbors, bool distancesEqualOne)
	//{
	//	// if there is cached graph for this dataset, then just load it and return from this method
	//	auto path = m_ext_particleSystem.datasetInfo().path + m_ext_particleSystem.datasetInfo().fileName;
	//	if (m_ext_graph.loadFromCache(path))
	//	{
	//		m_ext_system.logger().logInfo("[BruteForce Generator] kNN Graph loaded from cache.");
	//		return;
	//	}

	//	if (randomNeighbors)
	//	{
	//		
	//	}

	//	m_ext_graph.saveToCache(path);
	//	m_ext_system.logger().logInfo("[BruteForce Generator] Finished. Graph cached.");
	//}

	void BruteForce::addMinDist(std::vector<Neighbors>& n, float new_r, size_t pi, size_t pj, bool sort)
	{
		auto const elems = n.size();
		if (n[elems - 1].r < new_r) return;

		for (auto i = 0; i < elems; i++)
		{
			if (n[i].r >= new_r)
			{
				for (size_t j = elems - 1; j > i; j--)
					n[j] = n[j - 1];

				n[i].r = new_r;
				n[i].i = pi;
				n[i].j = pj;
				n[i].type = NeighborsType::Near;

				return;
			}
		}
	}

	void BruteForce::addMaxDist(std::vector<Neighbors>& n, float new_r, size_t pi, size_t pj, bool sort)
	{
		auto const elems = n.size();
		if (n[elems - 1].r > new_r) return;

		for (auto i = 0; i < elems; i++)
		{
			if (n[i].r <= new_r)
			{
				for (size_t j = elems - 1; j > i; j--)
					n[j] = n[j - 1];
				n[i].r = new_r;
				if (!sort || pi < pj)
				{
					n[i].i = pi;
					n[i].j = pj;
				}
				else
				{
					n[i].i = pj;
					n[i].j = pi;
				}
				n[i].type = NeighborsType::Far;

				return;
			}
		}
	}
}
