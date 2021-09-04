///
/// \author Bartosz Minch <minch@agh.edu.pl>
/// \date 12.05.2019
///

#include <viskit/graph/generate/BruteForce.h>
#include <viskit/utils/Math.h>

namespace viskit::graph::generate
{
	BruteForce::BruteForce(core::System& system)
		: GraphGenerator(system)
	{
	}

	void BruteForce::generate(particles::ParticleSystem& ps, graph::Graph& graph, size_t k, bool distancesEqualOne)
	{
		graph.initialize(ps.countParticles());

		m_ext_system.logger().logInfo("[BruteForce kNN Generator] Searching for nearest neighbors...");

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

			if (distancesEqualOne)
			{
				for (auto& element : near)
				{
					element.r = 0.0f;
				}
			}

			graph.addNeighbors(near);
		}

		graph.neighborsCounter.nearestNeighbors = k;
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
}
