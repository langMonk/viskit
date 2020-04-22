///
/// \author Bartosz Minch <minch@agh.edu.pl>
/// \date 28.04.2019
///

#pragma once

#include <memory>
#include "ivhd/Structures.h"

namespace ivhd
{
	class IParser;
	class ICaster;
	class IParticleSystem;
	class IGraphGenerator;
	class IGraph;

	class IResourceFactory
	{
		// public methods
	public:
		/// <summary>
		/// Creates a new parser used for loading data into ivhd
		/// </summary>
		/// <param name="type"> Type of parser, which will be created. </param>
		/// <returns> The created parser. </returns>
		virtual std::shared_ptr<IParser> createParser(ParserType type) = 0;

		/// <summary>
		/// Creates a new kNN graph generator used for creating kNN Graph
		/// </summary>
		/// <param name="type"> Type of graph generator, which will be created. </param>
		/// <returns> The created generator. </returns>
		virtual std::shared_ptr<IGraphGenerator> createGraphGenerator(GraphGeneratorType type) = 0;

		/// <summary>
		/// Creates a new GPU kNN graph generator used for creating kNN Graph.
		/// </summary>
		/// <param name="type"> Type of graph generator, which will be created. </param>
		/// <returns> The created generator. </returns>
		virtual std::shared_ptr<IGraphGenerator> createGraphGeneratorGPU(GraphGeneratorType type) = 0;

		/// <summary>
		/// Creates a new caster, that might be used for data embedding.
		/// </summary>
		/// <param name="type"> Type of caster, which will be created. </param>
		/// <param name="optimizer"> Type of optimizer, which will be used. </param>
		/// <returns> The created caster. </returns>
		virtual std::shared_ptr<ICaster> createCaster(CasterType type, OptimizerType optimizer = OptimizerType::None) = 0;

		/// <summary>
		/// Creates a new GPU caster, that might be used for data embedding.
		/// </summary>
		/// <param name="type"> Type of caster, which will be created. </param>
		/// <param name="optimizer"> Type of optimizer, which will be used. </param>
		/// <returns> The created caster. </returns>
		virtual std::shared_ptr<ICaster> createCasterGPU(CasterType type, OptimizerType optimizer = OptimizerType::None) = 0;

		/// <summary>
		/// Creates a new particle system
		/// </summary>
		/// <returns>The created system.</returns>
		virtual std::shared_ptr<IParticleSystem> createParticleSystem() = 0;

		/// <summary>
		/// Creates a new graph structure
		/// </summary>
		/// <returns>The created graph.</returns>
		virtual std::shared_ptr<IGraph> createGraph() = 0;

	public:
		virtual ~IResourceFactory() = default;

	};
}