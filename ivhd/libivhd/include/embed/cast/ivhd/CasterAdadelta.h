///
/// \author Bartosz Minch <minch@agh.edu.pl>
/// \date 17.02.2020
///

#pragma once

#include "particles/ParticleSystem.h"
#include "embed/cast/ivhd/CasterIVHD.h"

namespace ivhd::embed::cast::ivhd
{
	class CasterAdadelta : public CasterIVHD
	{
		// public construction and destruction methods
	public:
		CasterAdadelta(core::System& system, particles::ParticleSystem& ps);

		void calculatePositions() override;
		
	private:
		std::vector<glm::vec4> decGrad;
		
		std::vector<glm::vec4> decDelta;

		float DECAYING_PARAM{ 0.9f };
		float EPS{ 0.00000001f };
	};
}
