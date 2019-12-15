#pragma once

#include <map>
#include <algorithm>
#include <limits>

#include "graph/DataPoint.h"

namespace ivhd::graph
{ 
	class BoundedPQueue 
	{
	public:
		explicit BoundedPQueue(std::size_t maxSize);

		void enqueue(const size_t& value, float priority);
		void enqueuePoint(const DataPoint& value, float priority);

		size_t dequeueMin();
		std::pair<float, DataPoint> dequeuePoint();

		std::size_t size() const;
		std::size_t pointSize() const;
		bool empty() const;
		bool emptyPoints() const;

		std::size_t maxSize() const;

		double best()  const;
		double worst() const;

	private:

		std::multimap<float, size_t> elems;
		std::multimap<float, DataPoint> points;
		std::size_t maximumSize;
	};
}