///
/// \author Bartosz Minch <minch@agh.edu.pl>
/// \date 18.04.2019
///

#include "embed/cast/CasterRandom.h"
#include "math/IvhdMath.h"
#include "threading/ThreadPool.h"

namespace viskit::embed::cast
{
	CasterRandom::CasterRandom(core::System& system)
		: Caster(system)
		, m_maxEdge(1000)
		, m_gen(new RandomGenerator())
	{

	}

	void CasterRandom::calculatePositions(particles::ParticleSystem& ps)
	{
		m_ext_system.logger().logInfo("[CasterRandom] Casting particle system...");

		internalCastingThread(ps);

		m_ext_system.logger().logInfo("[CasterRandom] Finished.");
	}

	void CasterRandom::internalCastingThread(particles::ParticleSystem& ps) const
	{
		const size_t queriesPerThread = ps.countParticles() / math::threads<>;
		
		threading::ThreadPool threadPool(math::threads<>);
        std::vector<std::future<void>> results(math::threads<>);

        for (int i = 0; i < math::threads<>; i++)
        {
            auto start = i * queriesPerThread;
            auto end = (i == math::threads<> -1) ? ps.countParticles() : start + queriesPerThread;

            auto gen = m_gen;

            results[i] = threadPool.enqueue([&ps, &gen, start, end]()
                                           {
                                               auto& positions = ps.calculationData()->m_pos;

                                               for (auto i = start; i < end; i++)
                                               {
                                                   positions[i].x = gen->gen();
                                                   positions[i].y = gen->gen();
                                               }
                                           });
        }

        for (auto& result: results)
            result.get();
	}

	Dist::result_type CasterRandom::RandomGenerator::gen()
	{
		return m_dist(m_eng);
	}
}