///
/// \author Bartosz Minch <minch@agh.edu.pl>
/// \date 18.04.2019
///

#pragma once

namespace ivhd
{
	class IResourceFactory;
	class IParser;
	class ICaster;
	class IParticleSystem;

	/// <summary>
	/// The main interface for controlling IVHD.
	/// </summary>
	class IInteractiveVizualization
	{
		// public sub-types
	public:
		using CasterEventHandler = std::function<void(void)>;
		
		// public methods
	public:
		/// <summary>
		/// Obtains particle system.
		/// </summary>
		virtual IParticleSystem& particleSystem() = 0;
		
		/// <summary>
		/// Obtains resource factory, that enables creation of IVHD objects.
		/// </summary>
		virtual IResourceFactory& resourceFactory() = 0;

		/// <summary>
		/// Starts casting process.
		/// </summary>
		virtual void startCasting() = 0;

		/// <summary>
		/// Stops casting process.
		/// </summary>
		virtual void stopCasting() = 0;

		/// <summary>
		/// Pause casting process.
		/// </summary>
		virtual void pauseCasting() = 0;
		
		/// <summary>
		/// Sets caster that is currently used.
		/// </summary>
		virtual void currentCaster(std::shared_ptr<ivhd::ICaster> caster) = 0;

		/// <summary>
		/// Subscribe to event on casting step finished.
		/// </summary>
		virtual void subscribeOnCastingStepFinish(CasterEventHandler handler) = 0;
		
		// protected construction and destruction methods
	protected:
		virtual ~IInteractiveVizualization() = default;

	};
}