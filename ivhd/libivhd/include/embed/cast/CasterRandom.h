///
/// \author Bartosz Minch <minch@agh.edu.pl>
/// \date 18.04.2019
///

#pragma once

#include <boost/random.hpp>

#include "Caster.h"
#include "particles/ParticleSystem.h"

using Engine = boost::mt19937;
using Dist = boost::uniform_real<float>;

namespace ivhd::embed::cast
{ 
	class CasterRandom final : public Caster
	{
		// public construction and destruction methods
	public:
		explicit CasterRandom(core::System& system);

		// public methods
	public:		
		void calculatePositions(particles::ParticleSystem& ps) override;

		[[nodiscard]] int maxEdge() const { return m_maxEdge; };
		
		// Helper structures
	private:
		class RandomGenerator
		{
		public:
			explicit RandomGenerator(float min = -0.5f, float max = 0.5f)
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
		void internalCastingThread(particles::ParticleSystem& ps) const;

		// private members
	private:
		int m_maxEdge;

		RandomGenerator* m_gen;
		
	};
}