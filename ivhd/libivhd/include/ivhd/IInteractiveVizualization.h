///
/// \author Bartosz Minch <minch@agh.edu.pl>
/// \date 18.04.2019
///

#pragma once

#include "ivhd/IParticleSystem.h"
#include "ivhd/IParser.h"

namespace ivhd
{
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
		virtual bool loadDataFile(std::string dataFilePath, IParser& parser) = 0;

		// protected construction and destruction methods
	protected:
		virtual ~IInteractiveVizualization() = default;

	};
}