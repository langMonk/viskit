///
/// \author Bartosz Minch <minch@agh.edu.pl>
/// \date 12.05.2019
///

#include <viskit/graph/generate/BoundedPQueue.h>

namespace viskit::graph::generate {
BoundedPQueue::BoundedPQueue(std::size_t maxSize)
{
    maximumSize = maxSize;
}

void BoundedPQueue::enqueue(const size_t& value, float priority)
{
    elems.insert(std::make_pair(priority, value));

    if (size() > maxSize()) {
        auto last = elems.end();
        --last;
        elems.erase(last);
    }
}

void BoundedPQueue::enqueuePoint(const DataPoint& value, float priority)
{
    points.insert(std::make_pair(priority, value));

    if (pointSize() > maxSize()) {
        auto last = points.end();
        --last;
        points.erase(last);
    }
}

size_t BoundedPQueue::dequeueMin()
{
    size_t result = elems.begin()->second;
    elems.erase(elems.begin());
    return result;
}

std::pair<float, DataPoint> BoundedPQueue::dequeuePoint()
{
    auto result = std::make_pair(points.begin()->first, points.begin()->second);
    points.erase(points.begin());
    return result;
}

std::size_t BoundedPQueue::size() const
{
    return elems.size();
}

std::size_t BoundedPQueue::pointSize() const
{
    return points.size();
}

bool BoundedPQueue::empty() const
{
    return elems.empty();
}

bool BoundedPQueue::emptyPoints() const
{
    return points.empty();
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