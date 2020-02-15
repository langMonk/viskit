///
/// \author Bartosz Minch <minch@agh.edu.pl>
/// \date 12.05.2019
///

#pragma once

#include "IGraphGenerator.h"
#include "particles/ParticleSystem.h"
#include "graph/Graph.h"
#include "graph/generate/KDTree.h"

namespace ivhd::graph::generate
{
	class BruteForce : public IGraphGenerator
	{
		// public construction and destruction methods
	public:

		BruteForce(particles::ParticleSystem& ps);

		// public methods
	public:
		void generate(size_t nearestNeighbors, size_t furthestNeighbors, size_t randomNeighbors) override;

		void useCache(bool useCache) override;
		
	private:
		void add_min_dist(Neighbors* n, size_t elems, float new_r, size_t pi, size_t pj, bool sort);
		void add_max_dist(Neighbors* n, size_t elems, float new_r, size_t pi, size_t pj, bool sort);
		void add_to_dist_matrix(Neighbors* n, size_t elems);
		void reset_tmp_dist_matrix(Neighbors* n, float initval, size_t elems);

		// private members
	private:
		particles::ParticleSystem& m_ext_particleSystem;
		
		bool m_distancesEqualOne;

		graph::Graph* m_graph;

		bool m_useCache {false};
	};
}