///
/// \author Bartosz Minch <minch@agh.edu.pl>
/// \date 18.04.2019
///

#pragma once

#include "math/GlmAdapter.h"

namespace ivhd::core
{ 
	struct Connection
	{
		long pi, pj;
	};


	struct Particle
	{
		std::string name;

		long parent_id;
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
}