///
/// \author Bartosz Minch <minch@agh.edu.pl>
/// \date 18.04.2019
///

#include "facade/FacadeParserCSV.h"

namespace ivhd::facade
{
	FacadeParserCSV::FacadeParserCSV(core::ParticleSystem& system)
		: m_internalParser(std::make_shared<ivhd::parse::ParserCSV>(system))
	{
	}

	void FacadeParserCSV::loadFile(std::string filePath, size_t maxSize)
	{
		m_internalParser->loadFile(filePath, maxSize);
	}
}
