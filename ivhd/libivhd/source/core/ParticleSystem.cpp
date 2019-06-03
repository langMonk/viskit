///
/// \author Bartosz Minch <minch@agh.edu.pl>
/// \date 18.04.2019
///

#include "core/ParticleSystem.h"

namespace ivhd::core
{
	ParticleSystem::ParticleSystem(OnLogAdded handler)
		: m_logger(handler)
	{
		
	}
}