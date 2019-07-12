#pragma once

#include <cmath>
#include <algorithm>
#include <cassert>

namespace ivhd::graph
{
	class Point
	{
		// sub-types
	public:
		using iterator = float*;
		using const_iterator = const float*;

		// construction and destruction methods
	public: 
		Point(size_t size);

		// public methods
	public:
		std::size_t size() const;

		float& operator[](std::size_t index);
		float operator[](std::size_t index) const;

		iterator begin();
		iterator end();
		const_iterator begin() const;
		const_iterator end() const;

		// private members
	private:
		size_t N;
		float* coords;
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