///
/// \author Bartosz Minch <minch@agh.edu.pl>
/// \date 10.02.2020
///

#include "facade/FacadeGraph.h"

namespace ivhd::facade
{
	FacadeGraph::FacadeGraph(core::Core& core, graph::Graph& graph)
		: m_ext_core(core)
		, m_ext_graph(graph)
	{
	}

	std::vector<Neighbors> FacadeGraph::getNeighbors(size_t idx)
	{
		try
		{
			if(const auto neighbors = m_ext_graph.getNeighbors(idx))
			{
				return *neighbors;
			}
		}
		catch (std::exception& exception)
		{
			std::string message = "Failed to get the neighbors from the graph: ";
			message += exception.what();
			m_ext_core.logger().logWarning(message);
		}
		return {};
	}

	void FacadeGraph::addNeighbors(size_t index, Neighbors neighbors)
	{
		try
		{
			m_ext_graph.addNeighbors(index, neighbors);
		}
		catch (std::exception& exception)
		{
			std::string message = "Failed to add the neighbor to the graph: ";
			message += exception.what();
			m_ext_core.logger().logWarning(message);
		}
	}

	void FacadeGraph::addNeighbors(size_t index, std::vector<Neighbors> neighbors)
	{
		try
		{
			m_ext_graph.addNeighbors(index, neighbors);
		}
		catch (std::exception& exception)
		{
			std::string message = "Failed to add the neighbors to the graph: ";
			message += exception.what();
			m_ext_core.logger().logWarning(message);
		}
	}

	size_t FacadeGraph::neighborsCount()
	{
		try
		{
			return m_ext_graph.neighborsCount();
		}
		catch (std::exception& exception)
		{
			std::string message = "Failed to get the number of neighbors currently in the graph: ";
			message += exception.what();
			m_ext_core.logger().logWarning(message);
		}
		return 0;
	}

	void FacadeGraph::sort()
	{
		try
		{
			m_ext_graph.sort();
		}
		catch (std::exception& exception)
		{
			std::string message = "Failed to sort the graph: ";
			message += exception.what();
			m_ext_core.logger().logWarning(message);
		}
	}

	void FacadeGraph::dump(std::string filePath, std::string fileName)
	{
		std::ofstream m_file;
		
		try
		{
			m_file.open(filePath + "\\" + fileName + ".txt");
			for (int i = 0; i < m_ext_graph.size(); i++)
			{
				if(const auto neighbors = m_ext_graph.getNeighbors(i))
				{
					for(const auto neighbor : *neighbors)
					{
						if (neighbor.type == NeighborsType::Near)
						{
							m_file << neighbor.i << "," << neighbor.j << "," << neighbor.r << "," << "Near" << std::endl;
						}
						else if (neighbor.type == NeighborsType::Far)
						{
							m_file << neighbor.i << "," << neighbor.j << "," << neighbor.r << "," << "Far" << std::endl;
						}
						else
						{
							m_file << neighbor.i << "," << neighbor.j << "," << neighbor.r << "," << "Random" << std::endl;
						}
					}
				}				
			}

			m_file.close();
		}
		catch (std::exception& exception)
		{
			std::string message = "Failed to dump graph to plain text file: ";
			message += exception.what();
			m_ext_core.logger().logWarning(message);
			m_file.close();
		}
	}
}
