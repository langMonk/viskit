///
/// \author Bartosz Minch <minch@agh.edu.pl>
/// \date 12.05.2019
///

#include "graph/generate/BruteForce.h"
#include "utils/Math.h"

namespace ivhd::graph::generate
{
	BruteForce::BruteForce(core::System& system, particles::ParticleSystem& ps)
		: GraphGenerator(system, ps, ps.neighbourhoodGraph())
	{
	}

	void BruteForce::generate(size_t nearestNeighbors, size_t furthestNeighbors, size_t randomNeighbors, bool distancesEqualOne)
	{
		m_ext_graph.generate(m_ext_particleSystem.countParticles());
		
		m_distancesEqualOne = distancesEqualOne;

		//// if there is cached graph for this dataset, then just load it and return from this method
		//auto path = m_ext_particleSystem.datasetInfo().path + m_ext_particleSystem.datasetInfo().fileName;
		//if (m_ext_graph.loadFromCache(path))
		//{
		//	m_ext_system.logger().logInfo("[BruteForce Generator] kNN Graph loaded from cache.");
		//	return;
		//}

		m_ext_system.logger().logInfo("[BruteForce Generator] Generating kNN Graph...");

		std::vector<Neighbors> near(nearestNeighbors);
		std::vector<Neighbors> far(furthestNeighbors);
		std::vector<Neighbors> rand(randomNeighbors);

		if (nearestNeighbors || furthestNeighbors)
		{
			for (size_t i = 0; i < m_ext_particleSystem.countAwakeParticles(); i++)
			{
				std::generate(near.begin(), near.end(), []()->Neighbors
				{
					Neighbors neighbors;
					neighbors.r = std::numeric_limits<float>::max();
					return neighbors;
				});
				
				std::generate(far.begin(), far.end(), []()->Neighbors
				{
					Neighbors neighbors;
					neighbors.r = -1.0f;
					return neighbors;
				});

				for (size_t j = 0; j < m_ext_particleSystem.countAwakeParticles(); j++)
				{
					if (i != j)
					{
						const auto distance = m_ext_particleSystem.vectorDistance(i, j);
						if (nearestNeighbors) addMinDist(near, distance, i, j, true);
						if (furthestNeighbors) addMaxDist(far, distance, i, j, true);
					}
				}

				if (m_distancesEqualOne)
				{
					for(auto& element : near)
					{
						element.r = 1.0f;
					}
					for (auto& element : far)
					{
						element.r = 1.0f;
					}
				}

				m_ext_graph.addNeighbors(near);
				m_ext_graph.addNeighbors(far);
			}
		}

		if (randomNeighbors)
		{
			for (size_t i = 0; i < m_ext_particleSystem.countAwakeParticles(); i++)
			{
				std::generate(rand.begin(), rand.end(), []()->Neighbors
				{
					Neighbors neighbors;
					neighbors.r = 0.0f;;
					return neighbors;
				});
				
				for (auto random = 0; random < randomNeighbors; random++)
				{
					while(true)
					{
						const auto j = math::randInt(0, m_ext_particleSystem.countAwakeParticles());
						if (j != i)
						{
							if(!alreadyNeighbors(i ,j))
							{
								auto distance = 1.0f;
								if (!m_distancesEqualOne)
								{
									distance = m_ext_particleSystem.vectorDistance(i, j);
								}
								
								m_ext_graph.addNeighbors(Neighbors{ i, j, distance, NeighborsType::Random });
								break;
							}
						}
					}
				}
			}
		}

		//m_ext_graph.saveToCache(path);
		m_ext_system.logger().logInfo("[BruteForce Generator] Finished. Graph cached.");
	}

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
