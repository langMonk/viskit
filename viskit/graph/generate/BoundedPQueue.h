///
/// \author Bartosz Minch <minch@agh.edu.pl>
/// \date 12.05.2019
///

#pragma once

#include <map>
#include <limits>

#include <viskit/viskit/DataPoint.h>

namespace viskit::graph::generate
{ 
	class BoundedPQueue 
	{
	public:
		explicit BoundedPQueue(std::size_t maxSize);

		void enqueue(const size_t& value, float priority);
		void enqueuePoint(const DataPoint& value, float priority);

		size_t dequeueMin();
		std::pair<float, DataPoint> dequeuePoint();

		[[nodiscard]] std::size_t size() const;
		[[nodiscard]] std::size_t pointSize() const;
		[[nodiscard]] bool empty() const;
		[[nodiscard]] bool emptyPoints() const;

        [[nodiscard]] std::size_t maxSize() const;

        [[nodiscard]] double best()  const;
        [[nodiscard]] double worst() const;

	private:

		std::multimap<float, size_t> elems;
		std::multimap<float, DataPoint> points;
		std::size_t maximumSize;
	};
}