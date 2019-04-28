///
/// \author Bartosz Minch <minch@agh.edu.pl>
/// \date 24.04.2019
///

#pragma once

#include <string>
#include <vector>
#include <fstream>

#include "core/ParticleSystem.h"
#include "core/Logger.h"

#include "ivhd/IParser.h"

namespace ivhd::parse
{
	class ParserCSV : public ivhd::IParser
	{
		// public construction and destruction methods
	public:

		ParserCSV(core::ParticleSystem& system, core::Logger& logger);

		// public methods
	public:

		void loadFile(std::string filePath) override;
		
		// private methods
	private:

		void initialize(std::string filePath);

		void finalize(std::ifstream& input);

		// private members
	private:
		core::ParticleSystem& m_system;

		core::Logger& m_logger;

		std::ifstream m_input;

		int m_coordsToRead;
	};
}