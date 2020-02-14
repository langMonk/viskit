///
/// \author Bartosz Minch <minch@agh.edu.pl>
/// \date 18.04.2019
///

#pragma once

#include <ivhd/Math.h>

namespace ivhd
{ 
	struct Connection
	{
		size_t pi, pj;
	};

	enum class NeighborsType
	{ 
		Near, 
		Far, 
		Random, 
		Reverse,
		ToRemove
	};

	enum class ParserType
	{
		Csv
	};

	enum class GraphGeneratorType
	{
		BruteForce,
		KDTreeBased,
		FAISS,
		Approx
	};

	enum class CasterType
	{
		Mds,
		DpdMds,
		LargeVis,
		tSNE,
		Random
	};

	class Neighbors
	{
	public:
		Neighbors() : i(0), j(0), r(0), type(NeighborsType::Near) {};
		Neighbors(size_t i, size_t j) : i(i), j(j), r(0), type(NeighborsType::Near) {};
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
}