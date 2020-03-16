///
/// \author Bartosz Minch <minch@agh.edu.pl>
/// \date 19.02.2020
///

#pragma once

#include "particles/ParticleSystem.h"
#include "embed/cast/ivhd/CasterIVHD.h"

namespace ivhd::embed::cast::ivhd
{
	class CasterNesterov : public CasterIVHD
	{
		// public construction and destruction methods
	public:
		CasterNesterov(core::System& system);

		void calculatePositions(particles::ParticleSystem& ps) override;
		
		void calculateForces(float& energy, particles::ParticleSystem& ps, graph::Graph& graph) override;

	};
}
