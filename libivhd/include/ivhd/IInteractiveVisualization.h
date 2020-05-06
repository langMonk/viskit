///
/// \author Bartosz Minch <minch@agh.edu.pl>
/// \date 18.02.2019
///

#pragma once

#include <vector>

namespace ivhd
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
		/// Starts casting process.
		/// </summary>
		/// <param name="ps"> Particle system to casting.</param>
		/// <param name="graph"> Graph used for casting.</param>
		/// <param name="caster"> Caster used for casting.</param>
		virtual void startCasting(IParticleSystem& ps, IGraph& graph, ICaster& caster) = 0;

		/// <summary>
		/// Stops casting process.
		/// </summary>
		virtual void stopCasting() = 0;

		/// <summary>
		/// Pause casting process.
		/// </summary>
		virtual void pauseCasting() = 0;

		/// <summary>
		/// Calculate min and max values for Bounding Box.
		/// </summary>
		/// </return> Vector of pairs, where min x,y are first and max x,y second values
		virtual std::vector<std::pair<float, float>> calculateBoundingBox() = 0;

		/// <summary>
		/// Subscribe to event fired, when casting step finishes.
		/// </summary>
		/// <param name="handler"> Handler for the event. </param>
		virtual void subscribeOnCastingStepFinish(CasterEventHandler handler) = 0;
		
		// protected construction and destruction methods
	protected:
		virtual ~IInteractiveVisualization() = default;

	};
}