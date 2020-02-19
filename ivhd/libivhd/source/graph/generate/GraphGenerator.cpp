#include "graph/generate/GraphGenerator.h"

namespace ivhd::graph::generate
{ 
	GraphGenerator::GraphGenerator(core::System& system, particles::ParticleSystem& ps, Graph& graph)
		: m_ext_system(system)
		, m_ext_particleSystem(ps)
		, m_ext_graph(graph)
	{
	}

	bool GraphGenerator::alreadyNeighbors(size_t index1, size_t index2) const
	{
		if(const auto neighbors = m_ext_graph.getNeighbors(index1))
		{
			for (const auto neighbor : *neighbors)
			{
				if(neighbor.j == index2)
				{
					return true;
				}
			}
		}
		return false;
	}
}
