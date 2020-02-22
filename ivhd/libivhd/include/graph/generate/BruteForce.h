///
/// \author Bartosz Minch <minch@agh.edu.pl>
/// \date 12.05.2019
///

#pragma once

#include "graph/generate/GraphGenerator.h"
#include "particles/ParticleSystem.h"
#include "graph/Graph.h"
#include "graph/generate/KDTree.h"

namespace ivhd::graph::generate
{
	class BruteForce : public GraphGenerator
	{
		// public construction and destruction methods
	public:

		BruteForce(core::System& system);

		// public methods
	public:
		void generateRandomNeighbors(particles::ParticleSystem& ps, graph::Graph& graph, size_t k = 0, bool distancesEqualOne = true);

		void generateNearestNeighbors(particles::ParticleSystem& ps, graph::Graph& graph, size_t k = 0, bool distancesEqualOne = true);
		
	private:
		static void addMinDist(std::vector<Neighbors>& n, float new_r, size_t pi, size_t pj, bool sort);
		static void addMaxDist(std::vector<Neighbors>& n, float new_r, size_t pi, size_t pj, bool sort);

		// private members
	private:
		bool m_distancesEqualOne {true};
	};
}