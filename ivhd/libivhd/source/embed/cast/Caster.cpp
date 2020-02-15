///
/// \author Bartosz Minch <minch@agh.edu.pl>
/// \date 18.04.2019
///

#include "embed/cast/Caster.h"
#include "math/IvhdMath.h"

namespace ivhd::embed::cast
{
	Caster::Caster(core::System& system, particles::ParticleSystem& ps)
		: m_ext_system(system)
		, m_ext_particleSystem(ps)
		, m_threadPool(threading::ThreadPool(math::threads<>))
	{

	}
}