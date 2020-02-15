///
/// \author Bartosz Minch <minch@agh.edu.pl>
/// \date 10.02.2020
///

#pragma once

#include "particles/ParticleSystem.h"

namespace ivhd::graph::generate
{
	class IGraphGenerator
	{
		// public construction and destruction methods
	public:
		virtual void generate(size_t nearestNeighbors, size_t furthestNeighbors, size_t randomNeighbors) = 0;
		
		virtual void useCache(bool useCache) = 0;
		
	};
}