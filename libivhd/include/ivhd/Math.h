///
/// \author Bartosz Minch <minch@agh.edu.pl>
/// \date 13.05.2019
///

#pragma once

namespace ivhd
{
	struct vec3
	{

		// public construction methods
	public:

		vec3(float x = 0.0f, float y = 0.0f, float z = 0.0f)
			: x{ x }, y{ y }, z{ z }
		{
		}

		// public values
	public:

		float x;
		float y;
		float z;

	};

	struct vec4
	{

		// public construction methods
	public:

		vec4(float x = 0.0f, float y = 0.0f, float z = 0.0f, float w = 0.0f)
			: x{ x }, y{ y }, z{ z }, w{ w }
		{
		}

		// public values
	public:

		float x;
		float y;
		float z;
		float w;

	};
}