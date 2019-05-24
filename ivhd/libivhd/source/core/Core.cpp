///
/// \author Bartosz Minch <minch@agh.edu.pl>
/// \date 18.04.2019
///

#include "core/Core.h"

namespace ivhd::core
{
	Core::Core(OnLogAdded handler, size_t maxCount)
		: m_particleSystem(ParticleSystem(handler, maxCount))
	{


	}
}