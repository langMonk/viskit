#include "embed/cast/ivhd/CasterAdadelta.h"

namespace ivhd::embed::cast::ivhd
{
	CasterAdadelta::CasterAdadelta(core::System& system, particles::ParticleSystem& ps)
		: CasterIVHD(system, ps, ps.neighbourhoodGraph())
	{
		
	}

	void CasterAdadelta::calculatePositions()
	{
		decGrad.resize(m_ext_particleSystem.countParticles(), glm::vec4{ 0.0f });
		decDelta.resize(m_ext_particleSystem.countParticles(), glm::vec4{ 0.0f });
			
		auto& positions = m_ext_particleSystem.calculationData()->m_pos;
		auto& forces = m_ext_particleSystem.calculationData()->m_force;
		
		for (auto i = 0; i < m_ext_particleSystem.countParticles(); i++)
		{
			decGrad[i].x = decGrad[i].x * DECAYING_PARAM + (1.0f - DECAYING_PARAM) * forces[i].x * forces[i].x;
			decGrad[i].y = decGrad[i].y * DECAYING_PARAM + (1.0f - DECAYING_PARAM) * forces[i].y * forces[i].y;

			const auto deltax = forces[i].x / sqrtf(EPS + decGrad[i].x) * sqrtf(EPS + decDelta[i].x);
			const auto deltay = forces[i].y / sqrtf(EPS + decGrad[i].y) * sqrtf(EPS + decDelta[i].y);

			positions[i].x += deltax;
			positions[i].y += deltay;

			decDelta[i].x = decDelta[i].x * DECAYING_PARAM + (1.0f - DECAYING_PARAM) * deltax * deltax;
			decDelta[i].y = decDelta[i].y * DECAYING_PARAM + (1.0f - DECAYING_PARAM) * deltay * deltay;
		}
		
		
		m_ext_particleSystem.increaseStep();
	}

}
