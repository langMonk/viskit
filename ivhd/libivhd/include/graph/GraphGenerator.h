///
/// \author Bartosz Minch <minch@agh.edu.pl>
/// \date 12.05.2019
///

#pragma once

#include <limits>
#include "particles/ParticleSystem.h"
#include "graph/Graph.h"
#include "graph/KDTree.h"

namespace ivhd::graph
{
	class GraphGenerator 
	{
		// public construction and destruction methods
	public:

		GraphGenerator(particles::ParticleSystem& ps, Graph& graph, bool useCache);

		// public methods
	public:
		void bruteForceKNN(size_t nn, size_t fn, size_t rn);

		void rkNN();

	private:
		void add_min_dist(Neighbors* n, size_t elems, float new_r, size_t pi, size_t pj, bool sort);
		void add_max_dist(Neighbors* n, size_t elems, float new_r, size_t pi, size_t pj, bool sort);
		void add_to_dist_matrix(Neighbors* n, size_t elems);
		void reset_tmp_dist_matrix(Neighbors* n, float initval, size_t elems);

		// private members
	private:
		particles::ParticleSystem& m_ext_particleSystem;
		
		bool m_distancesEqualOne;

		graph::Graph& m_graph;

		bool m_useCache;
	};
}