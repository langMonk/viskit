#include "embed/cast/ivhd/CasterSGD.h"

namespace ivhd::embed::cast::ivhd
{
	CasterSGD::CasterSGD(core::System& system, particles::ParticleSystem& ps)
		: CasterIVHD(system, ps, ps.neighbourhoodGraph())
	{
		
	}

	void CasterSGD::calculatePositions()
	{
	}
}
