///
/// \author Bartosz Minch <minch@agh.edu.pl>
/// \date 18.04.2019
///

#include <boost/random.hpp>
#include "embed/cast/CasterRandom.h"

namespace ivhd::embed::cast
{
	CasterRandom::CasterRandom(core::ParticleSystem& system)
		: Caster(system)
		, m_maxEdge(1000)
	{
	}

	void CasterRandom::cast()
	{
		initialize();

		boost::mt19937 rng;
		boost::uniform_real<float> u(-m_maxEdge*0.5f, m_maxEdge*0.5f);
		boost::variate_generator<boost::mt19937&, boost::uniform_real<float> > gen(rng, u);

		m_ext_system.logger().logInfo("[CasterRandom] Casting...");

		auto& dataParticles = m_ext_system.dataParticles();
		for (auto& particle : dataParticles)
		{
			particle.setPosition(math::float3{ 1.0f, 1.0f, 1.0f });
		}

		m_ext_system.logger().logInfo("[CasterRandom] Finished.");

		finalize();
	}
}