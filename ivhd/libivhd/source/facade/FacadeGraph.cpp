///
/// \author Bartosz Minch <minch@agh.edu.pl>
/// \date 10.02.2020
///

#include "facade/FacadeGraph.h"

namespace ivhd::facade
{
	FacadeGraph::FacadeGraph(std::shared_ptr<ivhd::graph::Graph> graph)
		: m_ext_internalGraph(graph)
	{
	}

	Neighbors FacadeGraph::getNeighbors(size_t idx)
	{
		if (m_ext_internalGraph != nullptr)
		{
			return m_ext_internalGraph->getNeighbors(idx);
		}
	}

	void FacadeGraph::addNeighbors(Neighbors neighbors)
	{
		if (m_ext_internalGraph != nullptr)
		{
			m_ext_internalGraph->addNeighbors(neighbors);
		}
	}

	size_t FacadeGraph::neighborsCount()
	{
		if (m_ext_internalGraph != nullptr)
		{
			m_ext_internalGraph->neighborsCount();
		}
	}

	void FacadeGraph::sort()
	{
		if (m_ext_internalGraph != nullptr)
		{
			m_ext_internalGraph->sort();
		}
	}
}
