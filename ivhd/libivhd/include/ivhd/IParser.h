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
		virtual void loadFile(std::string filePath, std::shared_ptr<ivhd::IParticleSystem>& ps) = 0;

	};
}