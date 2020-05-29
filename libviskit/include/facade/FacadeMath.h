///
/// \author Bartosz Minch <minch@agh.edu.pl>
/// \date 17.05.2019
///

#pragma once

#include "ivhd/Math.h"
#include "math/glm_adapter.h"

namespace ivhd::facade
{
	inline vec3 toVec3(const glm::vec3& vector)
	{
		return vec3(vector.x, vector.y, vector.z);
	}

	inline glm::vec3 toFloat3(const vec3& vector)
	{
		return glm::vec3(vector.x, vector.y, vector.z);
	}
}
