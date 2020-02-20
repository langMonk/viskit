///
/// \author Bartosz Minch <minch@agh.edu.pl>
/// \date 17.02.2020
///

#pragma once

#include "particles/ParticleSystem.h"
#include "embed/cast/ivhd/CasterIVHD.h"

namespace ivhd::embed::cast::ivhd
{
	class CasterForceDirected : public CasterIVHD
	{
		// public construction and destruction methods
	public:
		CasterForceDirected(core::System& system, particles::ParticleSystem& ps);

		void calculatePositions() override;
		
	};
}
