///
/// \author Bartosz Minch <minch@agh.edu.pl>
/// \date 18.04.2019
///

#pragma once

#include <memory>
#include <map>
#include <iostream>
#include <boost/random.hpp>
#include <glm/glm/gtc/random.hpp>

#include "Caster.h"
#include "particles/ParticleSystem.h"

using Engine = boost::mt19937;
using Dist = boost::uniform_real<float>;

namespace ivhd::embed::cast
{ 
	class CasterRandom : public Caster
	{
		// public construction and destruction methods
	public:
		CasterRandom(core::System& system, particles::ParticleSystem& ps);

		// public methods
	public:
		void castParticle(size_t index) override;

		void castParticleSystem() override;

		int maxEdge() { return m_maxEdge; };
		
		// Helper structures
	private:
		class RandomGenerator
		{
		public:
			RandomGenerator(float min = -0.5f, float max = 0.5f)
				: m_dist(min, max)
			{
			};

			Dist::result_type gen();

		private:
			Engine m_eng;
			Dist m_dist;
		};

		// private methods
	private:
		void internalCastingThread() const;

		// private members
	private:
		int m_maxEdge;

		RandomGenerator* m_gen;
		
	};
}