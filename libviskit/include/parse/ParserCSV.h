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

namespace viskit::parse
{
	class ParserCSV : public Parser
	{
		// public construction and destruction methods
	public:
		ParserCSV(core::System& system);

		// public methods
	public:
		void loadFile(const std::string& filePath, particles::ParticleSystem& ps);

	};
}