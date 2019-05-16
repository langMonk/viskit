///
/// \author Bartosz Minch <minch@agh.edu.pl>
/// \date 18.04.2019
///

#include "embed/cast/Caster.h"

namespace ivhd::embed::cast
{
	Caster::Caster(core::ParticleSystem& system)
		: m_ext_system(system)
	{

	}

	Caster::~Caster()
	{

	}

	core::ParticleSystem& Caster::particleSystem() const
	{
		return m_ext_system;
	}

	void Caster::initialize()
	{
		auto dataPoints = m_ext_system.dataPoints();

		if (dataPoints.empty())
		{
			dataPoints.resize(m_ext_system.originalCoordinates().size());

			for (auto point : dataPoints)
			{
				point.pos = { 0.0f,0.0f,0.0f };
			}
		}
	}

	void Caster::finalize()
	{
	}
}