///
/// \author Bartosz Minch <minch@agh.edu.pl>
/// \date 24.04.2019
///

#pragma once

#include <string>
#include <vector>
#include <fstream>

#include "core/Core.h"
#include "parse/Parser.h"

namespace ivhd::parse
{
	class ParserCSV : public ivhd::parse::Parser
	{
		// public construction and destruction methods
	public:
		ParserCSV(core::ParticleSystem& system);

		// public methods
	public:
		void loadFile(std::string filePath, size_t maxSize) override;

	};
}