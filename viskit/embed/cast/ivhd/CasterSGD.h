///
/// \author Bartosz Minch <minch@agh.edu.pl>
/// \date 19.02.2020
///

#pragma once

#include <viskit/particles/ParticleSystem.h>
#include <viskit/embed/cast/ivhd/CasterIVHD.h>

namespace viskit::embed::cast::ivhd
{
	class CasterSGD final : public CasterIVHD
	{
		// public construction and destruction methods
	public:
		explicit CasterSGD(const core::System& system);

		void calculatePositions(particles::ParticleSystem& ps) override;
	};
}
