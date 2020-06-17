///
/// \author Bartosz Minch <minch@agh.edu.pl>
/// \date 12.05.2019
///

#pragma once

#include "graph/generate/GraphGenerator.h"
#include "particles/ParticleSystem.h"
#include "graph/Graph.h"

namespace viskit::graph::generate
{
	class BruteForce final : public GraphGenerator
	{
		// public construction and destruction methods
	public:

		explicit BruteForce(core::System& system);

		// public methods
	public:
		void generate(particles::ParticleSystem& ps, graph::Graph& graph, size_t k, bool distancesEqualOne) override;
		
	private:
		static void addMinDist(std::vector<Neighbors>& n, float new_r, size_t pi, size_t pj, bool sort);

	};
}