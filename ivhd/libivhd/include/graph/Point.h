#pragma once

#include <cmath>
#include <algorithm>
#include <cassert>
#include <vector>

namespace ivhd::graph
{
	using PointId = size_t;

	class Point
	{
		// sub-types
	public:
		using iterator = float*;
		using const_iterator = const float*;

		// construction and destruction methods
	public: 
		Point(size_t size);
		Point(std::vector<float> vec);

		// public methods
	public:
		std::size_t size() const;

		float& operator[](std::size_t index);
		float operator[](std::size_t index) const;

		iterator begin();
		iterator end();
		const_iterator begin() const;
		const_iterator end() const;

		PointId getId() { return m_id; }
		PointId getId() const { return m_id; }

		// private members
	private:
		PointId m_id;
		size_t N;
		float* coords;
		static size_t m_currentId;

	};

	inline float Distance(const Point& one, const Point& two) 
	{
		assert(one.size() == two.size());
		float result = 0.0;
		for (std::size_t i = 0; i < one.size(); ++i)
			result += (one[i] - two[i]) * (one[i] - two[i]);
		return result;
	}

	inline bool operator==(const Point& one, const Point& two)
	{
		assert(one.size() == two.size());
		return std::equal(one.begin(), one.end(), two.begin());
	}

	inline bool operator!=(const Point& one, const Point& two)
	{
		assert(one.size() == two.size());
		return !(one == two);
	}
}