///
/// \author Bartosz Minch <minch@agh.edu.pl>
/// \date 18.04.2019
///

#pragma once

namespace ivhd::embed::cast
{
	class ICaster
	{
		// public construction and destruction methods
	public:
		virtual void castParticle(size_t index) = 0;

		virtual void castParticleSystem() = 0;

	public:
		virtual ~ICaster() = default;
	};
}
