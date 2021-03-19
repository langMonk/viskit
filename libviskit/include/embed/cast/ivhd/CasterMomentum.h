///
/// \author Bartosz Minch <minch@agh.edu.pl>
/// \date 17.02.2020
///

#pragma once

#include "particles/ParticleSystem.h"
#include "embed/cast/ivhd/CasterIVHD.h"

namespace viskit::embed::cast::ivhd
{
	class CasterMomentum final : public CasterIVHD
	{
		// public construction and destruction methods
	public:
		explicit CasterMomentum(core::System& system);

		void calculatePositions(particles::ParticleSystem& ps) override;

	private:
        float a_factor{ 0.99f };

        float b_factor{ 0.002f };
    };
}
