///
/// \author Bartosz Minch <minch@agh.edu.pl>
/// \date 15.07.2019
///

#pragma once

#include <viskit/embed/cast/Caster.h>
#include <viskit/particles/ParticleSystem.h>

namespace viskit::embed::cast::ivhd
{
	struct SammonParameters
	{
		SammonParameters() : k(1), m(2), w(0) {};
		int k, m, w;
	};

	struct distanceKernelParameters
	{
		distanceKernelParameters() : near(1.0f), random(0.01f), far(1.0f), reversed(-0.85f) {};
		float near, random, far, reversed;
	};

	class CasterMDS : public Caster
	{
		// public construction and destruction methods
	public:
		CasterMDS(const core::System& system, particles::ParticleSystem& ps);

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
		Graph& m_ext_graph;
		
		int maxVelocity{ 1000 };
		float dumpVelocity{ 0.95f };
	};
}