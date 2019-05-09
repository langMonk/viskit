///
/// \author Bartosz Minch <minch@agh.edu.pl>
/// \date 18.04.2019
///

#pragma once

namespace ivhd
{
	class IResourceFactory;
	class ICaster;
	class IParser;

	/// <summary>
	/// The main interface for controlling IVHD.
	/// </summary>
	class IInteractiveVizualization
	{
		// public methods
	public:
		/// <summary>
		/// Load data from specified file into ivhd particle system.
		/// </summary>
		virtual void loadDataFile(std::string dataFilePath, IParser& parser) = 0;

		/// <summary>
		/// Cast data between two spaces. 
		/// </summary>
		virtual void castData(ICaster& caster) = 0;

		/// <summary>
		/// Reduce data dimensionality. 
		/// </summary>
		//virtual void reduceData(IReducer& caster) = 0;

		/// <summary>
		/// Obtains resource factory, that enables creation of IVHD objects.
		/// </summary>
		virtual IResourceFactory& resourceFactory() = 0;

		// protected construction and destruction methods
	protected:
		virtual ~IInteractiveVizualization() = default;

	};
}