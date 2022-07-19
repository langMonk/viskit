///
/// \author Bartosz Minch <minch@agh.edu.pl>
/// \date 18.05.2010
///

#pragma once

#include <random>

namespace viskit::math {
static size_t randInt(size_t min, size_t max)
{
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<size_t> dist(min, max);

    return dist(mt);
}

static float randFloat(float min, float max)
{
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<float> dist(min, max);

    return dist(mt);
}
}