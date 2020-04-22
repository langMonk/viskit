///
/// \author Bartosz Minch <minch@agh.edu.pl>
/// \date 28.04.2019
///

#pragma once

#include <memory>
#include "ivhd/Structures.h"

namespace ivhd
{
	class IGpuCaster;
	class IGraphGenerator;

	class IGpuResourceFactory
	{
		// public methods
	public:
		/// <summary>
		/// Creates a new GPU kNN graph generator used for creating kNN Graph
		/// </summary>
		/// <param name="type"> Type of graph generator, which will be created. </param>
		/// <returns> The created GPU generator. </returns>
		virtual std::shared_ptr<IGraphGenerator> createGraphGenerator(GraphGeneratorType type) = 0;

		/// <summary>
		/// Creates a new GPU caster, that might be used for data embedding.
		/// </summary>
		/// <param name="type"> Type of caster, which will be created. </param>
		/// <param name="optimizer"> Type of optimizer, which will be used. </param>
		/// <returns> The created GPU caster. </returns>
		virtual std::shared_ptr<IGpuCaster> createCaster(CasterType type, OptimizerType optimizer = OptimizerType::None) = 0;

	public:
		virtual ~IGpuResourceFactory() = default;

	};
}