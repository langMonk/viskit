///
/// \author Bartosz Minch <minch@agh.edu.pl>
/// \date 30.04.2019
///

#pragma once

#include <glm/glm/glm.hpp>
#include <iostream>
#include <string>

namespace ivhd::math
{
	typedef glm::vec2 float2;
	typedef glm::vec3 float3;
	typedef glm::vec4 float4;

	typedef glm::mat2x2 matrix2x2;
	typedef glm::mat3x3 matrix3x3;
	typedef glm::mat4x4 matrix4x4;
}

inline std::ostream& operator<<(std::ostream& stream, const ivhd::math::float2& vector)
{
	return stream << "("
		+ std::to_string(vector.x) + ", "
		+ std::to_string(vector.y) + ")";
}

inline std::ostream& operator<<(std::ostream& stream, const ivhd::math::float3& vector)
{
	return stream << "("
		+ std::to_string(vector.x) + ", "
		+ std::to_string(vector.y) + ", "
		+ std::to_string(vector.z) + ")";
}

inline std::ostream& operator<<(std::ostream& stream, const ivhd::math::float4& vector)
{
	return stream << "("
		+ std::to_string(vector.x) + ", "
		+ std::to_string(vector.y) + ", "
		+ std::to_string(vector.z) + ", "
		+ std::to_string(vector.w) + ")";
}
