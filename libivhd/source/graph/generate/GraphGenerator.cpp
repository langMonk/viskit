#include "graph/generate/GraphGenerator.h"

namespace ivhd::graph::generate
{ 
	GraphGenerator::GraphGenerator(core::System& system)
		: m_ext_system(system)
	{
	}

	bool GraphGenerator::alreadyNeighbors(size_t index1, size_t index2, Graph& graph)
	{
		if(const auto neighbors = graph.getNeighbors(index1))
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
