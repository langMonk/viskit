///
/// \author Bartosz Minch <minch@agh.edu.pl>
/// \date 12.05.2019
///

#include "facade/FacadeCasterRandom.h"

namespace ivhd::facade
{
	FacadeCasterRandom::FacadeCasterRandom(core::ParticleSystem& system)
		: m_internalCaster(system)
	{
	}

	void FacadeCasterRandom::cast()
	{
		m_internalCaster.cast();
	}

	void FacadeCasterRandom::initialize()
	{
	}
	void FacadeCasterRandom::finalize()
	{
	}
	void FacadeCasterRandom::resetSettings()
	{
	}
	void FacadeCasterRandom::loadSettings(std::istream& in)
	{
	}
	void FacadeCasterRandom::saveSettings(std::ostream& out)
	{
	}
}
