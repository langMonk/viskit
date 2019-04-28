///
/// \author Bartosz Minch <minch@agh.edu.pl>
/// \date 18.04.2019
///

#pragma once

#include "Structures.h"

namespace ivhd
{
	class IParser
	{
		// public methods
	public:
		/// <summary>
		/// Load specified file into kNN structure
		/// </summary>
		virtual void loadFile(std::string filePath) = 0;

	};
}