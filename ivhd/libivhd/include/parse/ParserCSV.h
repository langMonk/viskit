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
		// public construction and destruction methods
	public:

		ParserCSV(core::ParticleSystem& system);

		// public methods
	public:

		void loadFile(std::string filePath) override;

		// private members
	private:
		core::ParticleSystem& m_ext_system;

	};
}