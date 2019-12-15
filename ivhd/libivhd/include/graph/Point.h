#pragma once

#include <cmath>
#include <algorithm>
#include <cassert>
#include <vector>

namespace ivhd::graph
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
		DataPoint(size_t size);
		DataPoint(std::vector<float> vec);

		// public methods
	public:
		std::size_t size() const;

		float& operator[](std::size_t index);
		float operator[](std::size_t index) const;

		iterator begin();
		iterator end();
		const_iterator begin() const;
		const_iterator end() const;

		DataPointId getId() { return m_id; }
		DataPointId getId() const { return m_id; }

		// private members
	private:
		DataPointId m_id;
		size_t N;
		float* coords;
		static size_t m_currentId;

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
}