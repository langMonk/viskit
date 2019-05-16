///
/// \author Bartosz Minch <minch@agh.edu.pl>
/// \date 18.04.2019
///

#include "facade/FacadeParserCSV.h"

namespace ivhd::facade
{
	FacadeParserCSV::FacadeParserCSV(core::ParticleSystem& system)
		: m_internalParser(std::make_shared<ivhd::parse::Parser>(system))
	{
	}

	void FacadeParserCSV::loadFile(std::string filePath)
	{
		m_internalParser->loadFile(filePath);
	}
}
