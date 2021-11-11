///
/// \author Bartosz Minch <minch@agh.edu.pl>
/// \date 19.02.2020
///

#pragma once

#include <viskit/core/System.h>
#include <viskit/particles/ParticleSystem.h>
#include <viskit/embed/cast/Caster.h>

namespace viskit::embed::cast
{
	class CasterIVHD : public Caster
	{
		// public construction and destruction methods
	public:
		explicit CasterIVHD(const core::System& system);

		void castParticleSystem(particles::ParticleSystem& ps, Graph& graph) override;
			
		virtual void calculateForces(float& energy, particles::ParticleSystem& ps, Graph& graph, size_t& interactions);

		void setFinalizing(bool val) { m_finalizing = val; }

	protected:
        float w_random{ 0.01f };

        float w_near{ 1.0f };

        float w_reverse{ 1.0f };

		bool m_finalizing{ false };
	};
}