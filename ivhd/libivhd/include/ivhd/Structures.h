///
/// \author Bartosz Minch <minch@agh.edu.pl>
/// \date 18.04.2019
///

#pragma once

#include "math/GlmAdapter.h"

namespace ivhd
{ 
	struct Connection
	{
		size_t pi, pj;
	};


	struct DataPoint
	{
		size_t parent_id;

		float size;
		bool frozen;
		bool removed;
		bool visible;
		bool marked;
		bool outlier;
		int children_cnt;
		int aux;

		math::float3 pos;
	};

	enum class PairDistanceType
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

	struct PairDistance
	{
		PairDistance() : i(0), j(0), r(0), type(PairDistanceType::Near) {};
		PairDistance(long i, long j, float r, PairDistanceType type) : i(i), j(j), r(r), type(type) {};
		long i, j;
		float r;
		PairDistanceType type;

		bool operator== (PairDistance& rhs)
		{
			if (i == rhs.i && j == rhs.j && r == rhs.r && type == rhs.type) { return true; }
			else { return false; }
		}

	};

}