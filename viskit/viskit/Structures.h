///
/// \author Bartosz Minch <minch@agh.edu.pl>
/// \date 18.04.2019
///

#pragma once

#include <cassert>
#include <vector>
#include <string>

namespace viskit
{


    struct NeighborsCounter
    {
        size_t nearestNeighbors, reverseNeighbors, randomNeighbors;
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
		Random,
		Faiss,
		Reverse,
	};

	enum class OptimizerType
	{
		None,
		SGD,
		ForceDirected,
		Momentum,
		Adadelta,
		Adam,
		Nesterov,
		tSNE
	};
	
	enum class CasterType
	{
		IVHD,
		LargeVis,
		tSNE,
		Random
	};

    enum class MetricType { Euclidean, Cosine };

    struct DatasetInfo
    {
        std::string path;
        std::string fileName;
        size_t count{};
        size_t dimensionality{};
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

		bool operator== (Neighbors& rhs) const
		{
            return i == rhs.i && j == rhs.j && r == rhs.r && type == rhs.type;
		}

	};
}