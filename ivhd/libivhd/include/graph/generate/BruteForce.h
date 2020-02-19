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

		BruteForce(core::System& system, particles::ParticleSystem& ps);

		// public methods
	public:
		void generate(size_t nearestNeighbors, size_t furthestNeighbors, size_t randomNeighbors, bool distancesEqualOne) override;
		
	private:
		static void addMinDist(std::vector<Neighbors>& n, float new_r, size_t pi, size_t pj, bool sort);
		static void addMaxDist(std::vector<Neighbors>& n, float new_r, size_t pi, size_t pj, bool sort);

		// private members
	private:
		bool m_distancesEqualOne {true};

		Graph* m_graph;
	};
}