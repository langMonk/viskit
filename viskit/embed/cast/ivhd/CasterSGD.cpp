///
/// \author Bartosz Minch <minch@agh.edu.pl>
/// \date 19.02.2020
///

#include <viskit/embed/cast/ivhd/CasterSGD.h>

namespace viskit::embed::cast::ivhd
{
	CasterSGD::CasterSGD(core::System& system)
		: CasterIVHD(system)
	{
		
	}

	void CasterSGD::calculatePositions(particles::ParticleSystem& ps)
	{
	}
}
