///
/// \author Bartosz Minch <minch@agh.edu.pl>
/// \date 18.02.2020
///
///

#pragma once

#include <optional>

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
		std::optional<std::vector<Neighbors>> getNeighbors(size_t index);

		void addNeighbor(size_t index, Neighbors neighbors);

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

		std::vector<std::vector<Neighbors>> m_data;
	};
}

