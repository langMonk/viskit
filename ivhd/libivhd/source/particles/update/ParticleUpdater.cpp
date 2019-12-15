#include "particles/update/ParticleUpdater.h"

namespace ivhd::particles::update
{
	void EulerUpdater::update(double dt, ParticleData* data)
	{
		const glm::vec4 globalA{ dt * m_globalAcceleration.x,
							 dt * m_globalAcceleration.y,
							 dt * m_globalAcceleration.z,
							 0.0 };
		const float localDT = (float)dt;

		const unsigned int endId = static_cast<unsigned int>(data->m_countAlive);
		for (size_t i = 0; i < endId; ++i)
			data->m_acc[i] += globalA;

		for (size_t i = 0; i < endId; ++i)
			data->m_vel[i] += localDT * data->m_acc[i];

		for (size_t i = 0; i < endId; ++i)
			data->m_pos[i] += localDT * data->m_vel[i];
	}

	void FloorUpdater::update(double dt, ParticleData* data)
	{
		const float localDT = (float)dt;

		const size_t endId = data->m_countAlive;
		for (size_t i = 0; i < endId; ++i)
		{
			if (data->m_pos[i].y < m_floorY)
			{
				glm::vec4 force = data->m_acc[i];
				float normalFactor = glm::dot(force, glm::vec4(0.0f, 1.0f, 0.0f, 0.0f));
				if (normalFactor < 0.0f)
					force -= glm::vec4(0.0f, 1.0f, 0.0f, 0.0f) * normalFactor;

				float velFactor = glm::dot(data->m_vel[i], glm::vec4(0.0f, 1.0f, 0.0f, 0.0f));
				//if (velFactor < 0.0)
				data->m_vel[i] -= glm::vec4(0.0f, 1.0f, 0.0f, 0.0f) * (1.0f + m_bounceFactor) * velFactor;

				data->m_acc[i] = force;
			}
		}
	}

	void AttractorUpdater::update(double dt, ParticleData* data)
	{
		const float localDT = (float)dt;

		const size_t endId = data->m_countAlive;
		const size_t countAttractors = m_attractors.size();
		glm::vec4 off;
		float dist;
		size_t a;
		for (size_t i = 0; i < endId; ++i)
		{
			for (a = 0; a < countAttractors; ++a)
			{
				off.x = m_attractors[a].x - data->m_pos[i].x;
				off.y = m_attractors[a].y - data->m_pos[i].y;
				off.z = m_attractors[a].z - data->m_pos[i].z;
				dist = glm::dot(off, off);

				//if (fabs(dist) > 0.00001)
				dist = m_attractors[a].w / dist;

				data->m_acc[i] += off * dist;
			}
		}
	}

	void PosColorUpdater::update(double dt, ParticleData* data)
	{
		const size_t endId = data->m_countAlive;
		float scaler, scaleg, scaleb;
		float diffr = m_maxPos.x - m_minPos.x;
		float diffg = m_maxPos.y - m_minPos.y;
		float diffb = m_maxPos.z - m_minPos.z;
		for (size_t i = 0; i < endId; ++i)
		{
			scaler = (data->m_pos[i].x - m_minPos.x) / diffr;
			scaleg = (data->m_pos[i].y - m_minPos.y) / diffg;
			scaleb = (data->m_pos[i].z - m_minPos.z) / diffb;
			data->m_col[i].r = scaler;// glm::mix(data->m_startCol[i].r, data->m_endCol[i].r, scaler);
			data->m_col[i].g = scaleg;// glm::mix(data->m_startCol[i].g, data->m_endCol[i].g, scaleg);
			data->m_col[i].b = scaleb;// glm::mix(data->m_startCol[i].b, data->m_endCol[i].b, scaleb);
		}
	}

	void VelColorUpdater::update(double dt, ParticleData* data)
	{
		const size_t endId = data->m_countAlive;
		float scaler, scaleg, scaleb;
		float diffr = m_maxVel.x - m_minVel.x;
		float diffg = m_maxVel.y - m_minVel.y;
		float diffb = m_maxVel.z - m_minVel.z;
		for (size_t i = 0; i < endId; ++i)
		{
			scaler = (data->m_vel[i].x - m_minVel.x) / diffr;
			scaleg = (data->m_vel[i].y - m_minVel.y) / diffg;
			scaleb = (data->m_vel[i].z - m_minVel.z) / diffb;
			data->m_col[i].r = scaler;// glm::mix(data->m_startCol[i].r, data->m_endCol[i].r, scaler);
			data->m_col[i].g = scaleg;// glm::mix(data->m_startCol[i].g, data->m_endCol[i].g, scaleg);
			data->m_col[i].b = scaleb;// glm::mix(data->m_startCol[i].b, data->m_endCol[i].b, scaleb);
		}
	}
}