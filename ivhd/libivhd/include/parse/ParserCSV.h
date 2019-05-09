///
/// \author Bartosz Minch <minch@agh.edu.pl>
/// \date 24.04.2019
///

#pragma once

#include <string>
#include <vector>
#include <fstream>

#include "core/Core.h"
#include "ivhd/IParser.h"

namespace ivhd::parse
{
	class ParserCSV : public ivhd::IParser
	{
		// public sub-types
		using CoordinatesContainer = std::vector<std::vector<std::string>>;

		// public construction and destruction methods
	public:

		ParserCSV(core::ParticleSystem& system);

		// public methods
	public:

		void loadFile(std::string filePath) override;
		
		// private methods
	private:

		void initialize(std::string filePath);

		void finalize(std::ifstream& input);

		// private members
	private:

		std::ifstream m_input;
		CoordinatesContainer m_coordinates;

		core::ParticleSystem& m_ext_system;

	};
}