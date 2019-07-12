#include "graph\Graph.h"

namespace ivhd::graph
{
	Graph::Graph(core::System& system)
		: m_ext_system(system)
	{

	}

	Neighbors Graph::getNeighbors(size_t idx)
	{
		if (!m_data.empty())
		{
			return m_data[idx];
		}
	}

	void Graph::addNeighbors(Neighbors neighbors)
	{
		m_data.push_back(neighbors);
	}

	struct dist_compare
	{
		bool operator() (const Neighbors& distElem1, const Neighbors& distElem2)
		{
			if (distElem1.i != distElem2.i)
			{
				return distElem1.i < distElem2.i;
			}
			return (distElem1.j < distElem2.j);
		}
	};

	void Graph::sort()
	{
		size_t from = m_data.size();
		std::sort(m_data.begin(), m_data.end(), dist_compare());

		// mark duplicates 
		for (int i = 1; i < m_data.size(); i++)
			if (m_data[i].i == m_data[i-1].i && m_data[i].j == m_data[i-1].j)
				m_data[i].type = NeighborsType::ToRemove;

		// remove 
		m_data.erase(std::remove_if(m_data.begin(), m_data.end(), [](Neighbors elem)
		{
			return elem.type == NeighborsType::ToRemove;
		}
		), m_data.end());

		m_ext_system.logger().logInfo("Sorted and size reduced: " + std::to_string(from) + "-->" + std::to_string(m_data.size()));

		// calculate min and max distance
		float mind, maxd;
		mind = maxd = m_data[0].r;
		for (int i = 1; i < m_data.size(); i++)
		{
			if (mind > m_data[i].r)
				mind = m_data[i].r;
			if (maxd < m_data[i].r)
				maxd = m_data[i].r;
		}

		m_ext_system.logger().logInfo("Min distance: " + std::to_string(mind) + ", max distance: " + std::to_string(maxd));
	}
}

