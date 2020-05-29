#include <algorithm>

#include "particles/ParticleData.h"

namespace ivhd::particles
{
	void ParticleData::generate(size_t maxSize)
	{
		m_count = maxSize;

		m_pos.resize(maxSize);
		m_acc.resize(maxSize);
		m_col.resize(maxSize);
		m_force.resize(maxSize);
		m_vel.resize(maxSize);
		m_acc.resize(maxSize);
		m_alive.resize(maxSize);

		for (int i = 0; i < maxSize; i++)
		{
			wake(i);
			m_pos[i] = glm::vec4{ 0.0f, 0.0f, 0.0f, 1.0f };
			m_col[i] = glm::vec4{ 0.0f, 0.0f, 0.0f, 1.0f };
			m_force[i] = glm::vec4{ 0.0f, 0.0f, 0.0f, 0.0f };
			m_vel[i] = glm::vec4{ 0.0f, 0.0f, 0.0f, 0.0f };
		}
	}

	void ParticleData::kill(size_t id)
	{
		if (m_countAlive > 0)
		{
			m_alive[id] = false;
			swapData(id, m_countAlive - 1);
			m_countAlive--;
		}
	}

	void ParticleData::wake(size_t id)
	{
		if (m_countAlive < m_count)
		{
			m_alive[id] = true;
			m_countAlive++;
		}
	}

	void ParticleData::swapData(size_t a, size_t b)
	{
		std::swap(m_pos[a], m_pos[b]);
		std::swap(m_acc[a], m_acc[b]);
		std::swap(m_col[a], m_col[b]);
		std::swap(m_vel[a], m_vel[b]);
		std::vector<bool>::swap(m_alive[a], m_alive[b]);
	}
	
	bool ParticleData::empty()
	{
		return m_count != 0;
	}

	void ParticleData::clear()
	{
		m_pos.clear();
		m_acc.clear();
		m_col.clear();
		m_vel.clear();
		m_acc.clear();
		m_alive.clear();
	}
}