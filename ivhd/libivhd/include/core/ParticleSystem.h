///
/// \author Bartosz Minch <minch@agh.edu.pl>
/// \date 18.04.2019
///

#pragma once

#include <memory>
#include <vector>
#include <map>

#include "ivhd/IParser.h"
#include "core/Logger.h"
#include "ivhd/Structures.h"

namespace ivhd::core
{
	// public sub-types
	using OriginalDataContainer = std::vector<Particle>;
	using ReducedDataContainer = std::vector<DistElem>;

	class ParticleSystem
	{
		// public construction and destruction methods
	public:
		ParticleSystem(Logger& logger);

		// public methods
	public:
		bool loadDataFile(std::string dataFilePath);

		void setParser(std::shared_ptr<IParser> parser) { m_parser = parser; };

		std::shared_ptr<IParser> parser() { return m_parser; };

		Logger& logger() { return m_logger; }

		// private members
	private:

		std::shared_ptr<IParser> m_parser;
		Logger& m_logger;

		OriginalDataContainer m_originalData;
		ReducedDataContainer m_data;
	};
}