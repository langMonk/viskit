///
/// \author Bartosz Minch <minch@agh.edu.pl>
/// \date 18.04.2019
///

#include "facade/FacadeCasterMDS.h"

namespace ivhd::facade
{ 
	FacadeCasterMDS::FacadeCasterMDS(core::ParticleSystem& system)
		//: m_internalCaster(system)
	{
	}

	void FacadeCasterMDS::cast()
	{
		//m_internalCaster.cast();
	}

	void FacadeCasterMDS::initialize()
	{
	}

	void FacadeCasterMDS::finalize()
	{
	}

	void FacadeCasterMDS::resetSettings()
	{
	}

	void FacadeCasterMDS::loadSettings(std::istream& in)
	{
	}

	void FacadeCasterMDS::saveSettings(std::ostream& out)
	{
	}
}
