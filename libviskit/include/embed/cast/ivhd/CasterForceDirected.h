///
/// \author Bartosz Minch <minch@agh.edu.pl>
/// \date 18.03.2020
///

#pragma once

#include "particles/ParticleSystem.h"
#include "embed/cast/ivhd/CasterIVHD.h"

namespace viskit::embed::cast::ivhd
{
	class CasterForceDirected final : public CasterIVHD
	{
		// public construction and destruction methods
	public:
		explicit CasterForceDirected(core::System& system);

		void castParticleSystem(particles::ParticleSystem& ps, Graph& graph) override;
		
		void calculatePositions(particles::ParticleSystem& ps) override;

	private:
		float m_speedFactor{ 400.0f };
		
		float m_dtFactor{ 1.0f };

	};
}
