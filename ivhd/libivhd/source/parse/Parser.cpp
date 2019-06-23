#include "parse/Parser.h"

namespace ivhd::parse
{
	Parser::Parser(core::System& system)
		: m_ext_system(system)
	{
	}

	void Parser::finalize(particles::ParticleSystem& ps)
	{
		auto dataPoints = ps.finalData();

		for (int i = 0; i < ps.numAliveParticles(); i++)
		{
			dataPoints->m_pos[i] = glm::vec4(0.0f, 0.0f, 0.0f, 0.0f);
		}
	}
}