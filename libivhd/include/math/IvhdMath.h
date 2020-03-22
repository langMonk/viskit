///
/// \author Bartosz Minch <minch@agh.edu.pl>
/// \date 18.08.2019
///

#pragma once

namespace ivhd::math
{
	template<class T = size_t>
	constexpr T threads = T(4);

	template<class T = float>
	constexpr T pi = T(3.14159265358979323846);

	template<class T = float>
	constexpr T e = T(2.71828182845904523536);
}