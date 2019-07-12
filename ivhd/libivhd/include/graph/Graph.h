#pragma once

#include <algorithm>
#include <string>

#include "core/System.h"
#include "ivhd/Structures.h"

namespace ivhd::graph
{
	// Helper class for maintaining structure of Graph
	class Neighbors
	{
	public:
		Neighbors() : i(0), j(0), r(0), type(NeighborsType::Near) {};
		Neighbors(size_t i, size_t j, float r, NeighborsType type) : i(i), j(j), r(r), type(type) {};
		size_t i, j;
		float r;
		NeighborsType type;

		bool operator== (Neighbors& rhs)
		{
			if (i == rhs.i && j == rhs.j && r == rhs.r && type == rhs.type) { return true; }
			else { return false; }
		}

	};

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

		void sort();

		// private members
	private:
		core::System& m_ext_system;

		std::vector<Neighbors> m_data;
	};
}

