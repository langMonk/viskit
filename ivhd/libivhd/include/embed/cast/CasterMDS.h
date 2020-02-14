///
/// \author Bartosz Minch <minch@agh.edu.pl>
/// \date 15.07.2019
///

#pragma once

#include <memory>
#include <map>
#include <iostream>

#include "Caster.h"
#include "graph/Graph.h"
#include "particles/ParticleSystem.h"

namespace ivhd::embed::cast
{
	struct SammonParameters
	{
		SammonParameters() : k(1), m(2), w(0) {};
		int k, m, w;
	};

	struct distanceKernelParameters
	{
		distanceKernelParameters() : near(1.0f), random(0.01f), far(0.0f), reversed(-0.85f) {};
		float near, random, far, reversed;
	};

	class CasterMDS : public Caster
	{
		// public construction and destruction methods
	public:
		CasterMDS(core::System& system, graph::Graph& graph);

		// public methods
	public:
		void cast(particles::ParticleSystem& ps);

		// private methods
	private:
		glm::vec4 calculateForces(long pair_indx, long pi, long pj, float& energy, particles::ParticleSystem& ps);

		// private members
	private:
		SammonParameters m_sammonParameters;
		distanceKernelParameters m_distanceKernelParameters;
		Graph m_graph;

		int maxVelocity{ 1000 };
		float dumpVelocity{ 0.95f };
	};
}