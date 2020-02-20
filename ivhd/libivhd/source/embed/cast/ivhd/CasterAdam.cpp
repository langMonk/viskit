#include "embed/cast/ivhd/CasterAdam.h"

namespace ivhd::embed::cast::ivhd
{
	CasterAdam::CasterAdam(core::System& system, particles::ParticleSystem& ps)
		: CasterIVHD(system, ps, ps.neighbourhoodGraph())
	{

	}

	void CasterAdam::calculatePositions()
	{
		decGrad.resize(m_ext_particleSystem.countParticles(), glm::vec4{ 0.0f });
		decDelta.resize(m_ext_particleSystem.countParticles(), glm::vec4{ 0.0f });

		auto& positions = m_ext_particleSystem.calculationData()->m_pos;
		auto& forces = m_ext_particleSystem.calculationData()->m_force;

		const auto it = m_ext_particleSystem.step();

		for (auto i = 0; i < m_ext_particleSystem.countParticles(); i++)
		{
			decGrad[i].x = decGrad[i].x * B2 + (1.0f - powf(B2, static_cast<float>(it))) * forces[i].x * forces[i].x;
			decGrad[i].y = decGrad[i].y * B2 + (1.0f - powf(B2, static_cast<float>(it))) * forces[i].y * forces[i].y;

			decDelta[i].x = decDelta[i].x * B1 + (1.0f - powf(B1, static_cast<float>(it))) * forces[i].x;
			decDelta[i].y = decDelta[i].y * B1 + (1.0f - powf(B1, static_cast<float>(it))) * forces[i].y;

			const auto deltax = LEARNING_RATE * (decDelta[i].x / (1.0f - B1)) / (EPS + sqrtf(decGrad[i].x / (1.0f - B2)));
			const auto deltay = LEARNING_RATE * (decDelta[i].y / (1.0f - B1)) / (EPS + sqrtf(decGrad[i].y / (1.0f - B2)));

			positions[i].x += deltax;
			positions[i].y += deltay;
		}


		m_ext_particleSystem.increaseStep();
	}

}
