#include "parse/Parser.h"
#include "core/Particle.h"

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
		auto& dataPoints = m_ext_system.dataParticles();

		if (dataPoints.empty())
		{
			for (int i = 0; i < m_ext_system.originalCoordinates().size(); i++)
			{
				dataPoints.push_back(core::Particle(math::float3(0.0f, 0.0f, 0.0f)));
			}
		}
	}

}