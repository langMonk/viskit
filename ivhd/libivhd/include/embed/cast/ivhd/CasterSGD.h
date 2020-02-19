///
/// \author Bartosz Minch <minch@agh.edu.pl>
/// \date 18.02.2020
///
///

#pragma once

#include "embed/cast/Caster.h"
#include "embed/cast/CasterRandom.h"
#include "particles/ParticleSystem.h"

namespace ivhd::embed::cast::ivhd
{
	class CasterSGD : public Caster
	{
	public:
		float c = 0.5f;
		float learningRate = 0.01f;
		float B = 0.2f;
		
		// public construction and destruction methods
	public:
		CasterSGD(core::System& system, particles::ParticleSystem& ps);

		// public methods
	public:
		void castParticle(size_t index) override;

		void castParticleSystem() override;

		void initPos();
		
		// private methods
	private:
		glm::vec4 calculateForces(size_t pairIndex, size_t pi, size_t pj, float& energy) const;

		// private members
	private:
		Graph& m_ext_graph;

		CasterRandom m_randomCaster;
	};
}
