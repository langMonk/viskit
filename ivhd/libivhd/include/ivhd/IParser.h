///
/// \author Bartosz Minch <minch@agh.edu.pl>
/// \date 18.04.2019
///

#pragma once

#include <string>
#include "ivhd/IParticleSystem.h"

namespace ivhd
{
	class IParser
	{
		// public methods
	public:
		/// <summary>
		/// Load specified file into particle system structure
		/// </summary>
		/// <param name="filePath"> Path, where the file (to read) is located.</param>
		/// <param name="ps"> Particle system which should be casted by this caster.</param>
		virtual void loadFile(std::string filePath) = 0;

	};
}