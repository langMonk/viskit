///
/// \author Bartosz Minch <minch@agh.edu.pl>
/// \date 18.04.2019
///

#pragma once

#include <string>

namespace viskit
{
	class IParticleSystem;

	class IParser
	{
		// public methods
	public:
		/// <summary>
		/// Load specified file into particle system structure
		/// </summary>
        /// <param name="datasetFilePath"> Path to file containing dataset.</param>
        /// <param name="labelsFilePath"> Path to file containing labels.</param>
		/// <param name="ps"> Particle system which should be casted by this caster.</param>
		virtual void loadFile(std::string datasetFilePath, std::string labelsFilePath, IParticleSystem& ps) = 0;

	};
}