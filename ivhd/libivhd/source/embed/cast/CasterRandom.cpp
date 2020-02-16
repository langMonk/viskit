///
/// \author Bartosz Minch <minch@agh.edu.pl>
/// \date 18.04.2019
///

#include "embed/cast/CasterRandom.h"
#include "math/IvhdMath.h"

namespace ivhd::embed::cast
{
	CasterRandom::CasterRandom(core::System& system, particles::ParticleSystem& ps)
		: Caster(system, ps)
		, m_maxEdge(1000)
		, m_gen(new RandomGenerator())
	{

	}

	void CasterRandom::castParticle(size_t index)
	{
		m_ext_system.logger().logInfo("[CasterRandom] Casting particle with index" + index);

		auto dataPoints = m_ext_particleSystem.calculationData();

		dataPoints->m_pos[index].x = m_gen->gen();
		dataPoints->m_pos[index].y = m_gen->gen();

		m_ext_system.logger().logInfo("[CasterRandom] Finished.");
	}

	void CasterRandom::castParticleSystem()
	{
		m_ext_system.logger().logInfo("[CasterRandom] Casting particle system...");

		internalCastingThread();

		m_ext_system.logger().logInfo("[CasterRandom] Finished.");
	}

	void CasterRandom::internalCastingThread() const
	{
		const size_t queriesPerThread = m_ext_particleSystem.countParticles() / math::threads<>;
		
		threading::ThreadPool threadPool(math::threads<>);

		for (size_t i = 0; i < math::threads<>; i++)
		{
			auto start = i * queriesPerThread;
			auto end = (i == math::threads<> -1) ? m_ext_particleSystem.countParticles() : start + queriesPerThread;

			auto gen = m_gen;
			auto ps = &m_ext_particleSystem;
			auto future = threadPool.enqueue([&ps, &gen, start, end]()
			{
				auto& positions = ps->calculationData()->m_pos;

				for (auto i = start; i < end; i++)
				{
					positions[i].x = gen->gen();
					positions[i].y = gen->gen();
				}
			});
		}
	}

	Dist::result_type CasterRandom::RandomGenerator::gen()
	{
		return m_dist(m_eng);
	}
}