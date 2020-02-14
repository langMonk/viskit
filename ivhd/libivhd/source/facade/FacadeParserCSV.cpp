///
/// \author Bartosz Minch <minch@agh.edu.pl>
/// \date 18.04.2019
///

#include "facade/FacadeParserCSV.h"

namespace ivhd::facade
{
	FacadeParserCSV::FacadeParserCSV(std::shared_ptr<core::Core> core, particles::ParticleSystem& ps)
		: FacadeParser(core)
		, m_internalParser(std::make_shared<ivhd::parse::ParserCSV>(core->system()))
		, m_ext_particleSystem(ps)
	{
	}

	void FacadeParserCSV::loadFile(std::string filePath)
	{
		try
		{
			m_internalParser->loadFile(filePath, m_ext_particleSystem);
		}
		catch (std::exception& ex)
		{
			m_ext_core->logger().logWarning("Failed to load data file: " + filePath + ". Error message: " + ex.what());
		}
	
	}
}
