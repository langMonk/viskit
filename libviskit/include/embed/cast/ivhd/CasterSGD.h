///
/// \author Bartosz Minch <minch@agh.edu.pl>
/// \date 19.02.2020
///

#pragma once

#include "particles/ParticleSystem.h"
#include "embed/cast/ivhd/CasterIVHD.h"

namespace ivhd::embed::cast::ivhd
{
	class CasterSGD final : public CasterIVHD
	{
		// public construction and destruction methods
	public:
		explicit CasterSGD(core::System& system);

		void calculatePositions(particles::ParticleSystem& ps) override;
	};
}
