///
/// \author Bartosz Minch <minch@agh.edu.pl>
/// \date 19.02.2020
///

#pragma once

#include "core/System.h"
#include "particles/ParticleSystem.h"
#include "embed/cast/Caster.h"

namespace viskit::embed::cast
{
	class CasterIVHD : public Caster
	{
		// public construction and destruction methods
	public:
		explicit CasterIVHD(core::System& system);

		void castParticleSystem(particles::ParticleSystem& ps, Graph& graph) override;
			
		virtual void calculateForces(float& energy, particles::ParticleSystem& ps, Graph& graph);

		void setFinalizing(bool val) { m_finalizing = val; }

	protected:
		float w_random{ 0.01f };

	    float a_factor{ 0.99f };

		float b_factor{ 0.002f };

		bool m_finalizing{ false };
	};
}