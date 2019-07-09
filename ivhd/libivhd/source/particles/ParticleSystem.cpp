///
/// \author Bartosz Minch <minch@agh.edu.pl>
/// \date 18.04.2019
///

#include "particles/ParticleSystem.h"

namespace ivhd::particles
{
	ParticleSystem::ParticleSystem(core::System& system)
		: m_ext_system(system)
		, m_particles(ParticleData())
	{
		
	}
}
