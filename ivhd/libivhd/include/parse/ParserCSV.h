///
/// \author Bartosz Minch <minch@agh.edu.pl>
/// \date 24.04.2019
///

#pragma once

#include <string>
#include <vector>
#include <fstream>

#include "core/System.h"
#include "particles/ParticleSystem.h"
#include "parse/Parser.h"

namespace ivhd::parse
{
	class ParserCSV : public Parser
	{
		// public construction and destruction methods
	public:
		ParserCSV(core::System& system);

		// public methods
	public:
		void loadFile(std::string filePath, size_t maxSize, particles::ParticleSystem& ps);

	};
}