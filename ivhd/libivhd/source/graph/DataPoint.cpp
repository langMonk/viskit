#include "graph/DataPoint.h"

namespace ivhd::graph
{
	size_t DataPoint::m_currentId = 0;

	DataPoint::DataPoint(size_t size)
		: N(size)
		, m_id(m_currentId++)
	{
		coords = new float[size];
	}

	DataPoint::DataPoint(std::vector<float> vec)
		: N(vec.size())
		, m_id(m_currentId++)
	{
		coords = new float[N]; 
		std::copy(vec.begin(), vec.end(), coords);
	}

	std::size_t DataPoint::size() const
	{
		return N;
	}

	float& DataPoint::operator[] (std::size_t index)
	{
		return coords[index];
	}

	float DataPoint::operator[] (std::size_t index) const
	{
		return coords[index];
	}

	typename DataPoint::iterator DataPoint::begin()
	{
		return coords;
	}

	typename DataPoint::const_iterator DataPoint::begin() const
	{
		return coords;
	}

	typename DataPoint::iterator DataPoint::end()
	{
		return begin() + size();
	}

	typename DataPoint::const_iterator DataPoint::end() const
	{
		return begin() + size();
	}
}