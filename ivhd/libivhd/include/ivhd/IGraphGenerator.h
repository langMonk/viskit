///
/// \author Bartosz Minch <minch@agh.edu.pl>
/// \date 10.02.2020
///

#pragma once

namespace ivhd
{
	class IParticleSystem;
	class IGraph;

	/// <summary>
	/// The public graph generator interface.
	/// </summary>
	class IGraphGenerator
	{
		// public methods 
	public:
		/// <summary>
		/// Generates a kNN graph based on specified particle system and saves it to graph structure.
		/// This method should usually just call generateNearestNeighbors() and generateRandomNeighbors() accordingly.
		/// </summary>
		/// <param name="ps"> Particle system, for which graph will be generated. </param>
		/// <param name="graph"> Graph used for generation. </param>
		/// <param name="nn"> Number of nearest neighbors, which should be calculated for this graph.</param>
		/// <param name="rn"> Number of random neighbors, which should be calculated for this graph.</param>
		/// <param name="distancesEqualOne"> If true all distances while generating graph are set to 1.</param>
		virtual void generate(IParticleSystem& ps, IGraph& graph, size_t nn, size_t rn = 0, bool distancesEqualOne = true) = 0;
		
		/// <summary>
		/// Generates a nearest neighbors for specified graph.
		/// </summary>
		/// <param name="ps"> Particle system, for which graph will be generated. </param>
		/// <param name="graph"> Graph used for generation. </param>
		/// <param name="k"> Number of nearest neighbors, which should be calculated in this graph.</param>
		/// <param name="distancesEqualOne"> If true all distances while generating graph are set to 1.</param>
		virtual void generateNearestNeighbors(IParticleSystem& ps, IGraph& graph, size_t k = 0, bool distancesEqualOne = true) = 0;

		/// <summary>
		/// Generates a graph.
		/// </summary>
		/// <param name="ps"> Particle system, for which graph will be generated. </param>
		/// <param name="graph"> Graph used for generation. </param>
		/// <param name="k"> Number of random neighbors, which should be calculated in this graph.</param>
		/// <param name="distancesEqualOne"> If true all distances while generating graph are set to 1.</param>
		virtual void generateRandomNeighbors(IParticleSystem& ps, IGraph& graph, size_t k = 0, bool distancesEqualOne = true) = 0;

	};
}