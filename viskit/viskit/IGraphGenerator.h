///
/// \author Bartosz Minch <minch@agh.edu.pl>
/// \date 10.02.2020
///

#pragma once

#include <cstddef>

namespace viskit {
class IParticleSystem;
class IGraph;

/// <summary>
/// The public graph generator interface.
/// </summary>
class IGraphGenerator {
    // public methods
public:
    /// <summary>
    /// Generates a neighbors for specified graph.
    /// </summary>
    /// <param name="ps"> Particle system, for which graph will be generated. </param>
    /// <param name="graph"> Graph used for generation. </param>
    /// <param name="k"> Number of neighbors, which should be calculated in this graph.</param>
    /// <param name="distancesEqualOne"> If true all distances while generating graph are set to 1.</param>
    virtual void generate(IParticleSystem& ps, IGraph& graph, size_t k, bool distancesEqualOne) = 0;

    /// <summary>
    /// Generates a neighbors for specified graph.
    /// </summary>
    /// <param name="ps"> Particle system, for which graph will be generated. </param>
    /// <param name="graph"> Graph used for generation. </param>
    /// <param name="graphHelper"> Graph used as helper graph (for reverse neighbors).</param>
    /// <param name="k"> Number of neighbors, which should be calculated in this graph.</param>
    /// <param name="distancesEqualOne"> If true all distances while generating graph are set to 1.</param>
    virtual void generate(IParticleSystem& ps, IGraph& graph, IGraph& graphHelper, size_t k, bool distancesEqualOne) = 0;

    /// <summary>
    /// Generates a neighbors graph by using helper graph.
    /// </summary>
    /// <param name="ps"> Particle system, for which graph will be generated. </param>
    /// <param name="graph"> Graph used for generation. </param>
    /// <param name="graphHelper"> Graph used as helper graph (for reverse neighbors).</param>
    virtual void generate(IParticleSystem& ps, IGraph& graph, IGraph& graphHelper) = 0;
};
}