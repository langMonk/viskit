///
/// \author Bartosz Minch <minch@agh.edu.pl>
/// \date 19.02.2020
///

#pragma once

#include <viskit/particles/ParticleSystem.h>
#include <viskit/embed/cast/ivhd/CasterIVHD.h>

namespace viskit::embed::cast::ivhd
{
	class CasterAdam final : public CasterIVHD
	{
		// public construction and destruction methods
	public:
		explicit CasterAdam(const core::System& system);

		void calculatePositions(particles::ParticleSystem& ps) override;

	private:
		std::vector<glm::vec4> decGrad;

		std::vector<glm::vec4> decDelta;

		float B1{ 0.9f };
		
		float B2{ 0.999f };
		
		float EPS{ 0.00000001f };
		
		float LEARNING_RATE{ 0.002f };
	};
}
