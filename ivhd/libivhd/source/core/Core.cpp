#include "core/Core.h"

///
/// \author Bartosz Minch <minch@agh.edu.pl>
/// \date 18.04.2019
///

#include <filesystem>

namespace ivhd::core
{
	Core::Core(OnLogAdded handler)
		: m_logger(handler)
		, m_system(ParticleSystem(m_logger))
	{


	}
	
	bool Core::load(std::string dataFilePath, IParser& parser)
	{
		parser.loadFile(dataFilePath);

	}

	void Core::clusterParticles()
	{

	}

	void Core::reduceParticles()
	{

	}

	void Core::castParticles()
	{

	}

	void Core::freezeParticle(Particle particle)
	{

	}

	void Core::defrostParticle(Particle particle)
	{

	}
}