#pragma once

#include "core/System.h"
#include "ivhd/Structures.h"

namespace ivhd::graph
{
	class Graph
	{
		// public construction and destruction methods
	public:
		Graph(core::System& system);

		// public methods
	public:
		Neighbors getNeighbors(size_t idx);

		void addNeighbors(Neighbors neighbors);

		size_t neighborsCount() { return m_data.size(); }
		size_t neighborsCount() const { return m_data.size(); }

		void sort();
		
		void clear();
		
		size_t size() const;

		bool saveToCache(const std::string& fileName);

		bool loadFromCache(const std::string& fileName);
		
		// private members
	private:
		core::System& m_ext_system;

		std::vector<Neighbors> m_data;
	};
}

