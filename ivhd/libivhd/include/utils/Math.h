#pragma once

#include <random>

namespace ivhd::math
{ 
	static int randInt(int min, int max)
	{
		std::random_device rd;
		std::mt19937 mt(rd());
		std::uniform_int_distribution<int> dist(min, max);

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