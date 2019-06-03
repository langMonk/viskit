#include "parse/Parser.h"

namespace ivhd::parse
{
	Parser::Parser(core::ParticleSystem& system)
		: m_ext_system(system)
	{
	}

	void Parser::initialize()
	{
	}

	void Parser::loadFile(std::string filePath, size_t maxSize)
	{
	}

	void Parser::finalize()
	{
		auto dataPoints = m_ext_system.finalData();

		for (int i = 0; i < m_ext_system.numAliveParticles(); i++)
		{
			dataPoints->m_pos[i] = glm::vec4(0.0f, 0.0f, 0.0f, 0.0f);
		}
	}

}