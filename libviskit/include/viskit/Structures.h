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
	using DataPointId = size_t;

	class DataPoint
	{
		// sub-types
	public:
		using iterator = float*;
		using const_iterator = const float*;

		// construction and destruction methods
	public:
		DataPoint(size_t size, DataPointId id) : m_id(id), N(size)
		{
			coords = new float[size];
		}
		
		DataPoint(std::vector<float> vec, DataPointId id) : m_id(id), N(vec.size())
		{
			coords = new float[N];
			std::copy(vec.begin(), vec.end(), coords);
		}

		// public methods
	public:
		[[nodiscard]] std::size_t size() const { return N; };

		float& operator[](std::size_t index) 
		{ 
			return coords[index];
		};

		float operator[](std::size_t index) const { return coords[index]; };

		iterator begin() { return coords; };
		iterator end() { return begin() + size(); }
		[[nodiscard]] const_iterator begin() const { return coords; };
		[[nodiscard]] const_iterator end() const { return begin() + size(); };

		[[nodiscard]] DataPointId getId() const { return m_id; }

		// private members
	private:
		DataPointId m_id;
		size_t N;
		float* coords;
	};

	inline float Distance(const DataPoint& one, const DataPoint& two)
	{
		assert(one.size() == two.size());
		auto result = 0.0f;
		for (std::size_t i = 0; i < one.size(); ++i)
			result += (one[i] - two[i]) * (one[i] - two[i]);
		return result;
	}

	inline bool operator==(const DataPoint& one, const DataPoint& two)
	{
		assert(one.size() == two.size());
		return std::equal(one.begin(), one.end(), two.begin());
	}

	inline bool operator!=(const DataPoint& one, const DataPoint& two)
	{
		assert(one.size() == two.size());
		return !(one == two);
	}

    struct NeighborsCounter
    {
        int nearestNeighbors, reverseNeighbors, randomNeighbors;
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