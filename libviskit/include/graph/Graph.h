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
		explicit Graph(core::System& system);

		// public methods
	public:
		void initialize(size_t elements);
		
		std::optional<std::vector<Neighbors>> getNeighbors(size_t index);

		void addNeighbors(const std::vector<Neighbors>& neighbors);
		
		void addNeighbors(Neighbors neighbor);

		size_t overallNeighborsCount();

		void sort();
		
		void clear();

		[[nodiscard]] size_t size() const;

		bool saveToCache(const std::string& fileName);

		bool loadFromCache(const std::string& fileName);

        NeighborsCounter neighborsCounter{0,0,0};

		// private members
	private:
		core::System& m_ext_system;

		std::vector<std::vector<Neighbors>> m_data;

	};
}

