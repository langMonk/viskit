///
/// \author Bartosz Minch <minch@agh.edu.pl>
/// \date 18.04.2019
///

#include "facade/FacadeParserCSV.h"

namespace ivhd::facade
{
	FacadeParserCSV::FacadeParserCSV(std::shared_ptr<core::Core> core)
		: FacadeParser(core)
		, m_internalParser(std::make_shared<ivhd::parse::ParserCSV>(core->system()))
	{
	}

	void FacadeParserCSV::loadFile(std::string filePath, std::shared_ptr<ivhd::IParticleSystem>& ps)
	{
		try
		{
			auto particleSystem = dynamic_cast<FacadeParticleSystem*>(ps.get());
			m_internalParser->loadFile(filePath, *particleSystem->internalParticleSystem().get());
		}
		catch (std::exception& ex)
		{
			m_ext_core->logger().logWarning("Failed to load data file: " + filePath + ". Error message: " + ex.what());
		}
	
	}
}
