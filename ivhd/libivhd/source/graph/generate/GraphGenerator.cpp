#include "graph/generate/GraphGenerator.h"

namespace ivhd::graph::generate
{ 
	GraphGenerator::GraphGenerator(core::System& system, particles::ParticleSystem& ps)
		: m_ext_system(system)
		, m_ext_particleSystem(ps)
	{
	}
}
