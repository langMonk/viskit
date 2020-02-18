///
/// \author Bartosz Minch <minch@agh.edu.pl>
/// \date 17.02.2020
///

#pragma once

#include "Caster.h"
#include "particles/ParticleSystem.h"
#include "CasterMDS.h"

namespace ivhd::embed::cast
{
	class CasterAB : public Caster
	{
		// public construction and destruction methods
	public:
		CasterAB(core::System& system, particles::ParticleSystem& ps);

		// public methods
	public:
		void castParticle(size_t index) override;

		void castParticleSystem() override;

		// private methods
	private:
		glm::vec4 calculateForces(size_t pairIndex, size_t pi, size_t pj, float& energy) const;

		// private members
	private:
		SammonParameters m_sammonParameters;
		distanceKernelParameters m_distanceKernelParameters;
		graph::Graph& m_ext_graph;

		float a_factor { 0.990545f };
		float b_factor { 0.000200945f };
	};
}
