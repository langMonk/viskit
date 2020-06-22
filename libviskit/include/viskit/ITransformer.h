///
/// \author Bartosz Minch <minch@agh.edu.pl>
/// \date 18.04.2019
///

#pragma once

namespace viskit
{
    class IParticleSystem;
    class IGraph;

	/// <summary>
	/// The public interface to objects, which will be able to transform between spaces.
	/// </summary>
	class ITransformer
	{
		// public methods
	public:
        /// <summary>
        /// [Optional] Initialization process, which uses particle system and graph. Necessary for GPU casters.
        /// </summary>
        /// <param name="ps"> Particle system, which contains positions that should be initialized. </param>
        /// <param name="graph"> Graph, which contains distances that should be initialized. </param>
        virtual void initialize(viskit::IParticleSystem& ps, viskit::IGraph& graph) = 0;

        /// <summary>
        /// Process, which occurs when transforming is finished.
        /// </summary>
        virtual void finalize() = 0;

        /// <summary>
        /// Handles transformer step.
        /// </summary>
        /// <param name="ps"> Particle system, which should be casted. </param>
        /// <param name="graph"> Graph used for casting. </param>
        virtual void step(IParticleSystem& ps, IGraph& graph) = 0;

		// protected construction and destruction methods
	protected:

		virtual ~ITransformer() = default;
	};
}