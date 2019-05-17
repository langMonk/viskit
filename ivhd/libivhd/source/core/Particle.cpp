#include "core/Particle.h"

namespace ivhd::core
{
	Particle::Particle()
	{
	}

	Particle::Particle(math::float3 m_pos) : m_position(m_pos), m_frozen(false), m_removed(false), m_visible(true)
	{

	}

	Particle::~Particle()
	{

	}

	const math::float3& Particle::position() const
	{
		return m_position;
	}

	void Particle::setPosition(const math::float3& position)
	{
		m_position = position;
	}
}