///
/// \author Bartosz Minch <minch@agh.edu.pl>
/// \date 18.02.2019
///

#pragma once

#include <vector>

namespace viskit
{
	class IResourceFactory;
	class IParser;
	class ICaster;
	class IParticleSystem;
	class IGraph;

	/// <summary>
	/// The main interface for controlling IVHD.
	/// </summary>
	class IInteractiveVisualization
	{
		// public sub-types
	public:
		using CasterEventHandler = std::function<void(void)>;
		
		// public methods
	public:	
		/// <summary>
		/// Obtains resource factory, that enables creation of IVHD objects.
		/// </summary>
		virtual IResourceFactory& resourceFactory() = 0;

        /// <summary>
        /// Casts positions in the specified particle system (using specified caster and graph).
        /// </summary>
        /// <param name="ps"> Particle system to casting.</param>
        /// <param name="graph"> Graph used for casting.</param>
        /// <param name="caster"> Caster used for casting.</param>
        [[maybe_unused]] virtual void computePositions(IParticleSystem& ps, IGraph& graph, ICaster& caster) = 0;

		/// <summary>
		/// Calculate min and max values for Bounding Box.
		/// </summary>
		/// </return> Vector of pairs, where min x,y are first and max x,y second values
        [[maybe_unused]] virtual std::vector<std::pair<float, float>> calculateBoundingBox() = 0;

		/// <summary>
		/// Subscribe to event fired, when casting step finishes.
		/// </summary>
		/// <param name="handler"> Handler for the event. </param>
        [[maybe_unused]] virtual void subscribeOnCastingStepFinish(CasterEventHandler handler) = 0;
		
		// protected construction and destruction methods
	protected:
		virtual ~IInteractiveVisualization() = default;

	};
}