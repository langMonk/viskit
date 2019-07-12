#include "graph/Point.h"

namespace ivhd::graph
{
	size_t Point::m_currentId = 0;

	Point::Point(size_t size) 
		: N(size)
		, m_id(m_currentId++)
	{
		coords = new float[size];
	}

	Point::Point(std::vector<float> vec) 
		: N(vec.size())
		, m_id(m_currentId++)
	{
		coords = new float[N]; 
		std::copy(vec.begin(), vec.end(), coords);
	}

	std::size_t Point::size() const
	{
		return N;
	}

	float& Point::operator[] (std::size_t index)
	{
		return coords[index];
	}

	float Point::operator[] (std::size_t index) const
	{
		return coords[index];
	}

	typename Point::iterator Point::begin()
	{
		return coords;
	}

	typename Point::const_iterator Point::begin() const
	{
		return coords;
	}

	typename Point::iterator Point::end()
	{
		return begin() + size();
	}

	typename Point::const_iterator Point::end() const
	{
		return begin() + size();
	}
}