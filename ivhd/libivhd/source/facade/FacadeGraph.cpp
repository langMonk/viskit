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

	Neighbors FacadeGraph::getNeighbors(size_t idx)
	{
		try
		{
			return m_ext_graph.getNeighbors(idx);
		}
		catch (std::exception& exception)
		{
			std::string message = "Failed to get the neighbors from the graph: ";
			message += exception.what();
			m_ext_core.logger().logWarning(message);
		}
	}

	void FacadeGraph::addNeighbors(Neighbors neighbors)
	{
		try
		{
			m_ext_graph.addNeighbors(neighbors);
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
			for (int i = 0; i < m_ext_graph.neighborsCount(); i++)
			{
				auto neighbors = m_ext_graph.getNeighbors(i);
				if (neighbors.type == NeighborsType::Near)
				{
					m_file << neighbors.i << "," << neighbors.j << "," << neighbors.r << "," << "Near" << std::endl;
				}
				else if (neighbors.type == NeighborsType::Far)
				{
					m_file << neighbors.i << "," << neighbors.j << "," << neighbors.r << "," << "Far" << std::endl;
				}
				else
				{
					m_file << neighbors.i << "," << neighbors.j << "," << neighbors.r << "," << "Random" << std::endl;
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
