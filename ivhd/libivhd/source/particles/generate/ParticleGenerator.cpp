#include "particles/generate/particleGenerator.h"
#include <assert.h>
#include <algorithm>
#include <glm/glm/gtc/random.hpp>

namespace ivhd::particles::generate
{
	const float M_PI = 3.14159265f;

	void BoxPosGen::generate(double dt, ParticleData* data, size_t startId, size_t endId)
	{
		glm::vec4 posMin{ m_pos.x - m_maxStartPosOffset.x, m_pos.y - m_maxStartPosOffset.y, m_pos.z - m_maxStartPosOffset.z, 1.0 };
		glm::vec4 posMax{ m_pos.x + m_maxStartPosOffset.x, m_pos.y + m_maxStartPosOffset.y, m_pos.z + m_maxStartPosOffset.z, 1.0 };

		for (size_t i = startId; i < endId; ++i)
		{
			data->m_pos[i] = glm::linearRand(posMin, posMax);
		}
	}

	void RoundPosGen::generate(double dt, ParticleData* data, size_t startId, size_t endId)
	{
		for (size_t i = startId; i < endId; ++i)
		{
			double ang = glm::linearRand(0.0, M_PI * 2.0);
			data->m_pos[i] = m_center + glm::vec4(m_radX * sin(ang), m_radY * cos(ang), 0.0, 1.0);
		}
	}

	void BasicVelGen::generate(double dt, ParticleData* data, size_t startId, size_t endId)
	{
		for (size_t i = startId; i < endId; ++i)
		{
			data->m_vel[i] = glm::linearRand(m_minStartVel, m_maxStartVel);
		}
	}

	void SphereVelGen::generate(double dt, ParticleData* data, size_t startId, size_t endId)
	{
		float phi, theta, v, r;
		for (size_t i = startId; i < endId; ++i)
		{
			phi = glm::linearRand(-M_PI, M_PI);
			theta = glm::linearRand(-M_PI, M_PI);
			v = glm::linearRand(m_minVel, m_maxVel);

			r = v * sinf(phi);
			data->m_vel[i].z = v * cosf(phi);
			data->m_vel[i].x = r * cosf(theta);
			data->m_vel[i].y = r * sinf(theta);
		}
	}
}