///
/// \author Bartosz Minch <minch@agh.edu.pl>
/// \date 17.02.2020
///

#pragma once

#include "embed/cast/Caster.h"
#include "particles/ParticleSystem.h"
#include "embed/cast/ivhd/CasterForceDirected.h"

namespace ivhd::embed::cast::ivhd
{
	class CasterForceDirected : public Caster
	{
		// public construction and destruction methods
	public:
		CasterForceDirected(core::System& system, particles::ParticleSystem& ps);

		// public methods
	public:
		void castParticle(size_t index) override;

		void castParticleSystem() override;

		// private methods
	private:
		void calculateForces(size_t index, float& energy) const;

		// private members
		Graph& m_ext_graph;

		float a_factor { 0.99f };
		float b_factor { 0.0002f };

		float w_random {0.01f};
	};
}
