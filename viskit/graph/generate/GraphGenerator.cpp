///
/// \author Bartosz Minch <minch@agh.edu.pl>
/// \date 18.04.2019
///

#include <viskit/graph/generate/GraphGenerator.h>
#include <viskit/utils/Math.h>

namespace viskit::graph::generate
{
	GraphGenerator::GraphGenerator(core::System& system)
		: m_ext_system(system)
	{
	}

    [[maybe_unused]] bool GraphGenerator::alreadyNeighbors(size_t index1, size_t index2, Graph& graph)
	{
		if(const auto neighbors = graph.getNeighbors(index1))
		{
			for (const auto neighbor : *neighbors)
			{
				if(neighbor.j == index2)
				{
					return true;
				}
			}
		}
		return false;
	}
}
