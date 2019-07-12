#pragma once

#include <map>
#include <algorithm>
#include <limits>

namespace ivhd::graph
{ 
	class BoundedPQueue 
	{
	public:
		explicit BoundedPQueue(std::size_t maxSize);

		void enqueue(const size_t& value, double priority);

		size_t dequeueMin();

		std::size_t size() const;
		bool empty() const;

		std::size_t maxSize() const;

		double best()  const;
		double worst() const;

	private:

		std::multimap<double, size_t> elems;
		std::size_t maximumSize;
	};
}