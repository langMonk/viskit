///
/// \author Bartosz Minch <minch@agh.edu.pl>
/// \date 12.05.2019
///

#include "graph/GraphGenerator.h"

namespace ivhd::graph
{ 
	GraphGenerator::GraphGenerator(core::ParticleSystem& system, bool useCache)
		: m_ext_system(system)
		, m_useCache(useCache)
	{
	}

	void GraphGenerator::kNN()
	{
		m_ext_system.logger().logInfo("Matrix generation started");


	}
}
