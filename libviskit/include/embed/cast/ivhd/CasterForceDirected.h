///
/// \author Bartosz Minch <minch@agh.edu.pl>
/// \date 18.03.2020
///

#pragma once

#include "particles/ParticleSystem.h"
#include "embed/cast/ivhd/CasterIVHD.h"


namespace viskit::embed::cast::ivhd
{
	class CasterForceDirected final : public CasterIVHD
	{
		// public construction and destruction methods
	public:
		explicit CasterForceDirected(core::System& system);

		void castParticleSystem(particles::ParticleSystem& ps, Graph& graph) override;
		
		void calculatePositions(particles::ParticleSystem& ps) override;

        void calculateForces(float& energy, particles::ParticleSystem& ps, Graph& graph) override;

	private:
        float m_currentMaxVelocity;

		float m_speedFactor{ 200.0f };

		float m_dtFactor{ 1.0f };

		float m_maxVelocity{ 1000.0f };

		float m_velDump{ 0.95f };

		bool m_autoAdaptStep{true};

        int m_sammonK{1};

        int m_sammonM{2};

        int m_sammonW{0};

        float v_max;
	};
}
