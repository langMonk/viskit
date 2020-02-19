///
/// \author Bartosz Minch <minch@agh.edu.pl>
/// \date 18.04.2019
///

#pragma once

#include <cassert>
#include <vector>

namespace ivhd
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
		DataPoint(size_t size) : m_id(m_currentId++), N(size)
		{
			coords = new float[size];
		}
		
		DataPoint(std::vector<float> vec) : m_id(m_currentId++), N(vec.size())
		{
			coords = new float[N];
			std::copy(vec.begin(), vec.end(), coords);
		}

		// public methods
	public:
		std::size_t size() const { return N; };

		float& operator[](std::size_t index) { return coords[index]; };
		float operator[](std::size_t index) const { return coords[index]; };

		iterator begin() { return coords; };
		iterator end() { return begin() + size(); }
		const_iterator begin() const { return coords; };
		const_iterator end() const { return begin() + size(); };

		DataPointId getId() { return m_id; }
		DataPointId getId() const { return m_id; }

		// private members
	private:
		DataPointId m_id;
		size_t N;
		float* coords;
		inline static size_t m_currentId {0};

	};

	inline float Distance(const DataPoint& one, const DataPoint& two)
	{
		assert(one.size() == two.size());
		float result = 0.0;
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
		SGD,
		ForceDirected,
		Adadelta ,
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

		bool operator== (Neighbors& rhs) const
		{
			if (i == rhs.i && j == rhs.j && r == rhs.r && type == rhs.type) { return true; }
			else { return false; }
		}

	};
}