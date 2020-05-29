///
/// \author Bartosz Minch <minch@agh.edu.pl>
/// \date 18.04.2019
///

#include "facade/FacadeParserCSV.h"

namespace ivhd::facade
{
	FacadeParserCSV::FacadeParserCSV(const std::shared_ptr<core::Core>& core)
		: FacadeParser(core)
		, m_internalParser(std::make_shared<ivhd::parse::ParserCSV>(core->system()))
	{
	}

	void FacadeParserCSV::loadFile(const std::string filePath, IParticleSystem& ps)
	{
		try
		{
			const auto facadePs = reinterpret_cast<FacadeParticleSystem*>(&ps);
			m_internalParser->loadFile(filePath, facadePs->internalSystem());
		}
		catch (std::exception& ex)
		{
			m_ext_core->logger().logWarning("Failed to load data file: " + filePath + ". Error message: " + ex.what());
		}
	
	}
}
