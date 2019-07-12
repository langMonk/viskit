///
/// \author Bartosz Minch <minch@agh.edu.pl>
/// \date 18.04.2019
///

#include <boost/random.hpp>
#include <glm/glm/gtc/random.hpp>

#include "embed/cast/CasterRandom.h"

namespace ivhd::embed::cast
{
	CasterRandom::CasterRandom(core::System& system)
		: Caster(system)
		, m_maxEdge(1000)
	{
	}

	void CasterRandom::cast(particles::ParticleSystem& ps)
	{
		initialize();

		boost::mt19937 rng;
		boost::uniform_real<float> u(-0.5f, 0.5f);
		boost::variate_generator<boost::mt19937&, boost::uniform_real<float> > gen(rng, u);

		m_ext_system.logger().logInfo("[CasterRandom] Casting...");

		auto dataPoints = ps.finalData();

		for (int i = 0; i < ps.countAwakeParticles(); i++)
		{
			dataPoints->m_pos[i].x = gen();
			dataPoints->m_pos[i].y = gen();
		}

		m_ext_system.logger().logInfo("[CasterRandom] Finished.");

		finalize();
	}
}