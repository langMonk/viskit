///
/// \author Bartosz Minch <minch@agh.edu.pl>
/// \date 18.04.2019
///

#include "core/Core.h"

namespace ivhd::core
{
	Core::Core(OnLogAdded handler)
		: m_particleSystem(ParticleSystem(handler))
	{


	}
	
	bool Core::load(std::string dataFilePath, IParser& parser)
	{
		parser.loadFile(dataFilePath);
		return true;
	}

}