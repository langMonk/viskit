///
/// \author Bartosz Minch <minch@agh.edu.pl>
/// \date 17.02.2020
///

#include <viskit/embed/cast/ivhd/CasterAdadelta.h>

namespace viskit::embed::cast::ivhd
{
	CasterAdadelta::CasterAdadelta(const core::System& system)
		: CasterIVHD(system)
	{
		
	}

	void CasterAdadelta::calculatePositions(particles::ParticleSystem& ps)
	{
		decGrad.resize(ps.countParticles(), glm::vec4{ 0.0f });
		decDelta.resize(ps.countParticles(), glm::vec4{ 0.0f });
			
		auto& positions = ps.calculationData()->m_pos;
		auto& forces = ps.calculationData()->m_force;
		
		for (auto i = 0; i < ps.countParticles(); i++)
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
		
		
		ps.increaseStep();
	}

}
