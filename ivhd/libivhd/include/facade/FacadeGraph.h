///
/// \author Bartosz Minch <minch@agh.edu.pl>
/// \date 10.02.2020
///

#pragma once

#include "graph/Graph.h"
#include "core/Core.h"
#include "facade/FacadeGraph.h"
#include "ivhd/IGraph.h"

namespace ivhd::facade
{
	/// <summary>
	/// Implementation of IGraph interface.
	/// </summary>
	class FacadeGraph : public IGraph
	{
		// public construction and destruction methods
	public:

		explicit FacadeGraph(core::Core& core, graph::Graph& graph);
		~FacadeGraph() = default;

		FacadeGraph(const FacadeGraph&) = delete;
		FacadeGraph(FacadeGraph&&) = delete;

		FacadeGraph& operator=(const FacadeGraph&) = delete;
		FacadeGraph& operator=(FacadeGraph&&) = delete;

	public:
		std::vector<Neighbors> getNeighbors(size_t idx) override;
	
		void addNeighbors(size_t index, Neighbors neighbor) override;
		
		void addNeighbors(size_t index, std::vector<Neighbors> neighbors) override;

		size_t neighborsCount() override;

		void sort() override;
		
		void dump(std::string filePath, std::string fileName) override;

		// private members
	private:
		core::Core& m_ext_core;
		
		graph::Graph& m_ext_graph;

	};
}