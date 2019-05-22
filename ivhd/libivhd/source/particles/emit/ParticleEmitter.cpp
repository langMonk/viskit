#include <algorithm>
#include "particles/emit/ParticleEmitter.h"

namespace ivhd::particles::emit
{
	void ParticleEmitter::emit(double dt, ParticleData* data)
	{
		const size_t maxNewParticles = static_cast<size_t>(dt * m_emitRate);
		const size_t startId = data->m_countAlive;
		const size_t endId = std::min(startId + maxNewParticles, data->m_count - 1);

		for (auto& gen : m_generators)
		{
			gen->generate(dt, data, startId, endId);
		}

		for (size_t i = startId; i < endId; ++i)
		{ 
			data->wake(i);
		}
	}

	void ParticleEmitter::addGenerator(std::shared_ptr<generate::ParticleGenerator> gen)
	{
		m_generators.push_back(gen);
	}
}