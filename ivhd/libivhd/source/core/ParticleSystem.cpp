///
/// \author Bartosz Minch <minch@agh.edu.pl>
/// \date 18.04.2019
///

#include "core/ParticleSystem.h"

namespace ivhd::core
{
	ParticleSystem::ParticleSystem(OnLogAdded handler, size_t maxCount)
		: m_logger(handler)
		, m_count(maxCount)
	{
		m_particles.generate(maxCount);

		for (size_t i = 0; i < maxCount; ++i)
			m_particles.wake(i);
	}
}