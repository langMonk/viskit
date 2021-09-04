///
/// \author Bartosz Minch <minch@agh.edu.pl>
/// \date 30.04.2019
///

#pragma once

#include <libraries/glm/glm/glm.hpp>
#include <iostream>
#include <string>

inline std::ostream& operator<<(std::ostream& stream, const glm::vec2& vector)
{
	return stream << "("
		+ std::to_string(vector.x) + ", "
		+ std::to_string(vector.y) + ")";
}

inline std::ostream& operator<<(std::ostream& stream, const glm::vec3& vector)
{
	return stream << "("
		+ std::to_string(vector.x) + ", "
		+ std::to_string(vector.y) + ", "
		+ std::to_string(vector.z) + ")";
}

inline std::ostream& operator<<(std::ostream& stream, const glm::vec4& vector)
{
	return stream << "("
		+ std::to_string(vector.x) + ", "
		+ std::to_string(vector.y) + ", "
		+ std::to_string(vector.z) + ", "
		+ std::to_string(vector.w) + ")";
}
