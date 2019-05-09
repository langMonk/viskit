///
/// \author Bartosz Minch <minch@agh.edu.pl>
/// \date 18.04.2019
///

#include "core/ParticleSystem.h"

namespace ivhd::core
{
	ParticleSystem::ParticleSystem(OnLogAdded handler)
		: m_logger(handler)
		, m_parser(nullptr)
	{
		
	}

	bool ParticleSystem::loadDataFile(std::string dataFilePath)
	{
		if(m_parser != nullptr)
		{ 
			m_parser->loadFile(dataFilePath);
			return true;
		}
		
		m_logger.logError("Cannot load file, when no parser is attached to system.");
		return false;
	}
}