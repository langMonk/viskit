#include <algorithm>
#include <string>
#include <fstream>

#include "graph/Graph.h"

namespace ivhd::graph
{
	Graph::Graph(core::System& system)
		: m_ext_system(system)
	{

	}

	void Graph::initialize(size_t elements)
	{
		m_data.resize(elements);
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

	void Graph::addNeighbors(Neighbors neighbor)
	{
		m_data[neighbor.i].emplace_back(neighbor);
	}
	
	void Graph::addNeighbors(const std::vector<Neighbors>& neighbors)
	{
		for(const auto& neighbor : neighbors)
		{
			m_data[neighbor.i].emplace_back(neighbor);
		}
	}

    size_t Graph::overallNeighborsCount()
	{
		size_t size {0};
		for(const auto& neighbors : m_data)
		{
			size += neighbors.size();
		}
		return size;
	}

	struct dist_compare
	{
		bool operator() (const Neighbors& distElem1, const Neighbors& distElem2) const
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
		auto const numberOfElements = m_data.size();
		auto const numberOfNeighbors = m_data[0].size();

		const auto from = numberOfNeighbors * numberOfElements;

		// sort graph (for every index)
		for (auto neighbors : m_data)
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

		// remove duplicates
		for (size_t i = 0; i < numberOfElements; i++)
		{
			for (size_t j = 1; j < numberOfNeighbors; j++)
			{
				if (m_data[i][j].i == m_data[i][j-1].i && m_data[i][j].j == m_data[i][j-1].j)
					m_data[i][j].type = NeighborsType::ToRemove;
			}
		}

		const auto to = m_data[0].size() * m_data.size();
		m_ext_system.logger().logInfo("Sorted and size reduced: " + std::to_string(from) + "-->" + std::to_string(to));

		// calculate min and max distance
		float maxd;
		float mind = maxd = m_data[0][0].r;
		for (size_t i = 0; i < numberOfElements; i++)
		{
			for (size_t j = 1; j < numberOfNeighbors; j++)
			{
				if (mind > m_data[i][j].r)
					mind = m_data[i][j].r;
				if (maxd < m_data[i][j].r)
					maxd = m_data[i][j].r;
			}
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
		m_ext_system.logger().logInfo("[Graph] Saving graph to cache...");

		std::ofstream file(fileName, std::ios::out | std::ios::binary);

		if (!file.good()) {
			m_ext_system.logger().logError("[Graph] File to save graph couldn't be created!");
			return false;
		}

		long testNum = 0x01020304;
		file.write(reinterpret_cast<char*>(&testNum), sizeof(long));
		
		auto graphSize = size();
		file.write(reinterpret_cast<char*>(&graphSize), sizeof(long));

		auto graphNeighborsCount = overallNeighborsCount() - neighborsCounter.randomNeighbors * size();
		file.write(reinterpret_cast<char*>(&graphNeighborsCount), sizeof(long));

		for (auto& neighbors : m_data)
		{
			for (auto& neighbor : neighbors)
			{
				if(neighbor.type!=NeighborsType::Random)
				{
					file.write(reinterpret_cast<char*>(&neighbor), sizeof(Neighbors));
				}
			}
		}

		file.close();

		m_ext_system.logger().logInfo("[Graph] Finished.");

		return true;
	}

	bool Graph::loadFromCache(const std::string& fileName)
	{
		m_ext_system.logger().logInfo("[Graph] Loading graph from cache...");

		std::ifstream file(fileName, std::ios::in | std::ios::binary);

		if (!file.good()) {
			m_ext_system.logger().logError("[Graph] File to read graph couldn't be opened!");
			return false;
		}

		auto testNum = 0;
		file.read(reinterpret_cast<char*>(&testNum), sizeof(long));
		assert(testNum == 0x01020304);
		
		auto graphSize = 0;
		file.read(reinterpret_cast<char*>(&graphSize), sizeof(long));
		m_data.resize(graphSize);

		auto graphNeighborsCount = 0;
		file.read(reinterpret_cast<char*>(&graphNeighborsCount), sizeof(long));

		neighborsCounter.nearestNeighbors = graphNeighborsCount / graphSize;

		for (auto& element : m_data) { element.resize(neighborsCounter.nearestNeighbors); }
		
		for (auto i = 0; i < graphSize; i++)
		{
			for (auto j = 0; j < neighborsCounter.nearestNeighbors; j++)
			{
				file.read(reinterpret_cast<char*>(&m_data[i][j]), sizeof(Neighbors));
			}
		}

		file.close();

		m_ext_system.logger().logInfo("[Graph] Finished.");
		
		return true;
	}
}

