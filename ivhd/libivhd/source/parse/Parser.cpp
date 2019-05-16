#include "parse\Parser.h"

namespace ivhd::parse
{
	Parser::Parser(core::ParticleSystem& system)
		: m_ext_system(system)
	{
	}

	void Parser::initialize()
	{
	}

	void Parser::loadFile(std::string filePath)
	{
	}

	void Parser::finalize()
	{
		auto dataPoints = m_ext_system.dataPoints();

		if (dataPoints.empty())
		{
			dataPoints.resize(m_ext_system.originalCoordinates().size());

			for (auto point : dataPoints)
			{
				point.pos = { 0.0f,0.0f,0.0f };
			}
		}
	}

}