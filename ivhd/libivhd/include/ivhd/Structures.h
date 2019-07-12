///
/// \author Bartosz Minch <minch@agh.edu.pl>
/// \date 18.04.2019
///

#pragma once

#include <ivhd/Math.h>

namespace ivhd
{ 
	struct Connection
	{
		size_t pi, pj;
	};

	enum class NeighborsType
	{ 
		Near, 
		Far, 
		Random, 
		Reverse,
		ToRemove
	};

	enum class ParserType
	{
		Csv
	};

	enum class CasterType
	{
		Mds,
		DpdMds,
		LargeVis,
		tSNE,
		Random
	};
}