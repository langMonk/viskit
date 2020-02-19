#include <algorithm>
#include <string>

#include "graph\Graph.h"

namespace ivhd::graph
{
	Graph::Graph(core::System& system)
		: m_ext_system(system)
	{

	}

	std::optional<std::vector<Neighbors>> Graph::getNeighbors(size_t index)
	{
		if (!m_data.empty())
		{
			return m_data[index];
		}
		else
		{
			m_ext_system.logger().logError("There is no neighbor item with passed index.");
			return {};
		}
	}

	void Graph::addNeighbor(size_t index, Neighbors neighbors)
	{
		m_data[index].emplace_back(neighbors);
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
		auto numberOfElements = m_data.size();
		auto numberOfNeighbors = m_data[0].size();

		size_t from = numberOfNeighbors * numberOfElements;
		for (const auto neighbors : m_data)
		{
			std::sort(neighbors.begin(), neighbors.end(), dist_compare());
		}

		// mark duplicates 
		for (auto neighbors : m_data)
		{
			neighbors.erase(std::remove_if(neighbors.begin(), neighbors.end(), [](Neighbors elem)
			{
				return elem.type == NeighborsType::ToRemove;
			}
			), neighbors.end());
		}

		for (int i = 0; i < numberOfElements; i++)
		{
			for (int j = 1; j < numberOfNeighbors; j++)
			{
				if (m_data[i][j].i == m_data[i][j-1].i && m_data[i][j].j == m_data[i][j-1].j)
					m_data[i][j].type = NeighborsType::ToRemove;
			}
		}

		// remove 
		for (auto neighbors : m_data)
		{
			neighbors.erase(std::remove_if(neighbors.begin(), neighbors.end(), [](Neighbors elem)
			{
				return elem.type == NeighborsType::ToRemove;
			}
			), neighbors.end());
		}

		size_t to = m_data[0].size() * m_data.size();
		m_ext_system.logger().logInfo("Sorted and size reduced: " + std::to_string(from) + "-->" + std::to_string(to));

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

	void Graph::clear()
	{
		m_data.clear();
	}

	size_t Graph::size() const
	{
		return m_data.size();
	}

	bool Graph::saveToCache(const std::string& fileName)
	{
		std::ofstream file(fileName + ".graph", std::ios::out | std::ios::binary);

		if (!file) {
			m_ext_system.logger().logError("[Graph] File to save graph couldn't be created!");
			return false;
		}

		auto graphSize = m_data.size();
		file.write(reinterpret_cast<char*>(&graphSize), sizeof(size_t));
		
		for (auto& i : m_data)
		{
			file.write(reinterpret_cast<char*>(&i), sizeof(Neighbors));
		}

		file.close();

		if (!file.good()) {
			m_ext_system.logger().logError("[Graph] Error occurred while saving graph to file.");
			return false;
		}

		return true;
	}

	bool Graph::loadFromCache(const std::string& fileName)
	{
		std::ifstream file(fileName + ".graph", std::ios::in | std::ios::binary);

		if (!file) {
			m_ext_system.logger().logError("[Graph] File to read graph couldn't be opened!");
			return false;
		}

		auto length = 0;
		file.read(reinterpret_cast<char*>(&length), sizeof(size_t));
		m_data.resize(length);
		
		for (auto i = 0; i < length; i++)
		{
			file.read(reinterpret_cast<char*>(&m_data[i]), sizeof(Neighbors));
		}

		file.close();

		if (!file.good()) {
			m_ext_system.logger().logError("[Graph] Error occurred while saving graph to file.");
			return false;
		}

		return true;
	}
}

