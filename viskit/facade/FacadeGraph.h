///
/// \author Bartosz Minch <minch@agh.edu.pl>
/// \date 10.02.2020
///

#pragma once

#include <viskit/graph/Graph.h>
#include <viskit/core/Core.h>
#include <viskit/viskit/IGraph.h>

namespace viskit::facade
{
	/// <summary>
	/// Implementation of IGraph interface.
	/// </summary>
	class FacadeGraph : public IGraph
	{
		// public construction and destruction methods
	public:

		explicit FacadeGraph(const std::shared_ptr<core::Core>& core);

		FacadeGraph(const FacadeGraph&) = delete;
		FacadeGraph(FacadeGraph&&) = delete;

		FacadeGraph& operator=(const FacadeGraph&) = delete;
		FacadeGraph& operator=(FacadeGraph&&) = delete;

		[[nodiscard]] graph::Graph& internalGraph() const { return *m_internalGraph; }

	public:
	    void initialize(size_t size) override;

		std::vector<Neighbors> getNeighbors(size_t idx) override;
	
		void addNeighbors(Neighbors neighbor) override;
		
		void addNeighbors(std::vector<Neighbors> neighbors) override;

		size_t overallNeighborsCount() override;

		NeighborsCounter neighborsCounter()override;

		size_t size() override;

		void sort() override;

		bool saveToCache(const std::string& fileName) override;

		bool loadFromCache(const std::string &fileName, size_t nearestNeighborsCountToRead) override;
		
		void dump(std::string filePath, std::string fileName) override;

		// private members
	private:
		std::shared_ptr<core::Core> m_ext_core;

		std::shared_ptr<graph::Graph> m_internalGraph;
		
	};
}