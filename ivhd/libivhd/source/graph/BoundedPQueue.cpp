#include "graph/BoundedPQueue.h"

namespace ivhd::graph
{
	BoundedPQueue::BoundedPQueue(std::size_t maxSize)
	{
		maximumSize = maxSize;
	}

	void BoundedPQueue::enqueue(const size_t& value, double priority)
	{
		elems.insert(std::make_pair(priority, value));

		if (size() > maxSize()) {
			typename std::multimap<double, size_t>::iterator last = elems.end();
			--last;
			elems.erase(last);
		}
	}

	size_t BoundedPQueue::dequeueMin()
	{
		size_t result = elems.begin()->second;
		elems.erase(elems.begin());
		return result;
	}

	std::size_t BoundedPQueue::size() const
	{
		return elems.size();
	}

	bool BoundedPQueue::empty() const
	{
		return elems.empty();
	}

	std::size_t BoundedPQueue::maxSize() const
	{
		return maximumSize;
	}

	double BoundedPQueue::best() const
	{
		return empty() ? std::numeric_limits<double>::infinity() : elems.begin()->first;
	}

	double BoundedPQueue::worst() const
	{
		return empty() ? std::numeric_limits<double>::infinity() : elems.rbegin()->first;
	}
}