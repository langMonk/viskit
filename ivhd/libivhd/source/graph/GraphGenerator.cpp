///
/// \author Bartosz Minch <minch@agh.edu.pl>
/// \date 12.05.2019
///

#include "graph/GraphGenerator.h"
#include "utils/Math.h"

namespace ivhd::graph
{ 

	GraphGenerator::GraphGenerator(particles::ParticleSystem& ps, Graph& graph, bool useCache)
		: m_ext_particleSystem(ps)
		, m_useCache(useCache)
		, m_graph(graph)
		, m_distancesEqualOne(true)
	{
	}

	/*void GraphGenerator::kNN(size_t nn)
	{
		using dataset = std::vector<std::pair<Point<30>, unsigned int>>;


	}*/

	void GraphGenerator::kNN(size_t nn, size_t fn, size_t rn)
	{
		Neighbors* near = new Neighbors[nn + 1];
		Neighbors* far = new Neighbors[fn + 1];
		Neighbors* rand = new Neighbors[rn + 1];

		auto timer = utils::TimeProfiler(true);
		timer.start();

		// nearest and furthest neighbors
		if (nn || fn)
		{
			for (size_t i = 0; i < m_ext_particleSystem.countAwakeParticles(); i++)
			{
				reset_tmp_dist_matrix(near, std::numeric_limits<float>::max(), nn);
				reset_tmp_dist_matrix(far, -1.0f, fn);

				for (size_t j = 0; j< m_ext_particleSystem.countAwakeParticles(); j++)
				{
					if(i!=j)
					{ 
						auto distance = m_ext_particleSystem.vectorDistance(i, j);
						add_min_dist(near, nn, distance, i, j, true);
						add_max_dist(far, fn, distance, i, j, true);
					}
				}

				add_to_dist_matrix(near, nn);
				add_to_dist_matrix(far, fn);
			}
		}	

		// random neighbors
		if (rn)
		{
			for (size_t i = 0; i < m_ext_particleSystem.countAwakeParticles(); i++)
			{
				reset_tmp_dist_matrix(rand, 0.0f, rn);
				for (int l = 0; l < rn; l++)
				{
					size_t j;
					do
					{
						j = math::randInt(0, m_ext_particleSystem.countAwakeParticles() - 1);
						//check if j is not alread nearest neighbor
						if (j != i)
							for (int m = 0; m < nn; m++)
								if ((near[m].j == j && near[m].i == i) || (near[m].j == i && near[m].i == j))
								{
									j = i;
									break;
								}

						// check if j is not alread furthest neighbor
						if (j != i)
							for (int m = 0; m < fn; m++)
								if ((far[m].j == j && far[m].i == i) || (far[m].j == i && far[m].i == j))
								{
									j = i;
									break;
								}

					} while (i == j);

					auto distance = m_ext_particleSystem.vectorDistance(i, j);
					rand[l].i = i;
					rand[l].j = j;
					rand[l].r = distance;
					rand[l].type = NeighborsType::Random;
				}
				add_to_dist_matrix(rand, rn);
			}
		}
		timer.stop();
		timer.measurementMs();
	}

	void GraphGenerator::reset_tmp_dist_matrix(Neighbors* n, float initval, size_t elems)
	{
		for (int i = 0; i < elems; i++)
			n[i].r = initval;
	}

	void GraphGenerator::add_min_dist(Neighbors* n, size_t elems, float new_r, size_t pi, size_t pj, bool sort)
	{
		if (n[elems - 1].r < new_r) return;

		for (int i = 0; i < elems; i++)
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

	void GraphGenerator::add_max_dist(Neighbors* n, size_t elems, float new_r, size_t pi, size_t pj, bool sort)
	{
		if (n[elems - 1].r > new_r) return;

		for (int i = 0; i < elems; i++)
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

	void GraphGenerator::add_to_dist_matrix(Neighbors* n, size_t elems)
	{
		for (int i = 0; i < elems; i++)
		{
			if (m_distancesEqualOne)
			{
				n->r = 1;
			}

			m_graph.addNeighbors(n[i]);
		}
	}
}
