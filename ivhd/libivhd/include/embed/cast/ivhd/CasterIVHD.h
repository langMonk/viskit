///
/// \author Bartosz Minch <minch@agh.edu.pl>
/// \date 19.02.2020
///

#pragma once

#include "core/System.h"
#include "particles/ParticleSystem.h"
#include "embed/cast/Caster.h"

namespace ivhd::embed::cast
{
	class CasterIVHD : public Caster
	{
		// public construction and destruction methods
	public:
		CasterIVHD(core::System& system, particles::ParticleSystem& ps, Graph& graph);
		virtual ~CasterIVHD() = default;

		CasterIVHD(const CasterIVHD&) = delete;
		CasterIVHD& operator=(const CasterIVHD&) = delete;

		void castParticle(size_t index) override;

		void castParticleSystem() override;
		
		// protected methods
	protected:
		virtual void calculateForces(float& energy);;

		virtual void calculatePositions();;

		float w_random{ 0.01f };
		
		float a_factor{ 0.99f };

		float b_factor{ 0.002f };
	};
}