#include "graph\Graph.h"

namespace ivhd::graph
{
	Graph::Graph(core::System& system)
		: m_ext_system(system)
	{

	}

	Neighbors Graph::getNeighbors(size_t idx)
	{
		if (!m_neighbors.empty())
		{
			return m_neighbors[idx];
		}
	}

	void Graph::addNeighbors(Neighbors neighbors)
	{
		m_neighbors.push_back(neighbors);
	}
}

