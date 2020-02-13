///
/// \author Bartosz Minch <minch@agh.edu.pl>
/// \date 10.02.2020
///

#pragma once

#include <ivhd/IGraph.h>

namespace ivhd
{
	/// <summary>
	/// The public graph generator interface.
	/// </summary>
	class IGraphGenerator
	{
		/// <summary>
		/// Generate a graph using specified method
		/// </summary>
		/// <param name="ps"> Particle system which should be casted by this caster.</param>
		virtual std::shared_ptr<ivhd::IGraph> generate(std::shared_ptr<ivhd::IParticleSystem>& ps) = 0;

	};
}