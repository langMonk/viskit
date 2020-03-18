///
/// \author Bartosz Minch <minch@agh.edu.pl>
/// \date 18.04.2019
///

#pragma once

#include "core/System.h"
#include "particles/ParticleSystem.h"

namespace ivhd::graph::generate
{
	class GraphGenerator
	{
		// public construction and destruction methods
	public:
		explicit GraphGenerator(core::System& system);
		virtual ~GraphGenerator() = default;

		GraphGenerator(const GraphGenerator&) = delete;
		GraphGenerator& operator=(const GraphGenerator&) = delete;

		virtual void generateRandomNeighbors(particles::ParticleSystem& ps, graph::Graph& graph, size_t k = 0, bool distancesEqualOne = true) {};

		virtual void generateNearestNeighbors(particles::ParticleSystem& ps, graph::Graph& graph, size_t k = 0, bool distancesEqualOne = true) {};

	protected:
		static bool alreadyNeighbors(size_t index1, size_t index2, Graph& graph);
		
	protected:
		core::System& m_ext_system;
	};
}
