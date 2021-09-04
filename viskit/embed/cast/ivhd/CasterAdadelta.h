///
/// \author Bartosz Minch <minch@agh.edu.pl>
/// \date 17.02.2020
///

#pragma once

#include <viskit/particles/ParticleSystem.h>
#include <viskit/embed/cast/ivhd/CasterIVHD.h>

namespace viskit::embed::cast::ivhd
{
	class CasterAdadelta final : public CasterIVHD
	{
		// public construction and destruction methods
	public:
		explicit CasterAdadelta(core::System& system);

		void calculatePositions(particles::ParticleSystem& ps) override;
		
	private:
		std::vector<glm::vec4> decGrad;
		
		std::vector<glm::vec4> decDelta;

		float DECAYING_PARAM{ 0.9f };
		float EPS{ 0.00000001f };
	};
}
