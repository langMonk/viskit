///
/// \author Bartosz Minch <minch@agh.edu.pl>
/// \date 18.04.2019
///

#pragma once

#include <viskit/core/System.h>
#include <viskit/particles/ParticleSystem.h>

namespace viskit::graph::generate
{
	class GraphGenerator
	{
		// public construction and destruction methods
	public:
		explicit GraphGenerator(core::System& system);
		virtual ~GraphGenerator() = default;

		GraphGenerator(const GraphGenerator&) = delete;
		GraphGenerator& operator=(const GraphGenerator&) = delete;

		virtual void generate(particles::ParticleSystem& ps, graph::Graph& graph, size_t k, bool distancesEqualOne) {};

		virtual void generate(std::vector<std::pair<viskit::DataPoint, particles::DataPointLabel>> points,
		        graph::Graph& graph, size_t k, bool distancesEqualOne) {};

	protected:
        [[maybe_unused]] static bool alreadyNeighbors(size_t index1, size_t index2, Graph& graph);
		
	protected:
		core::System& m_ext_system;
	};
}
