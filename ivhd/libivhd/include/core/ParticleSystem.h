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
		ParticleSystem(OnLogAdded handler);

		// public methods
	public:
		bool loadDataFile(std::string dataFilePath);

		void setParser(std::shared_ptr<IParser> parser) { m_parser = parser; };

		std::shared_ptr<IParser> parser() { return m_parser; };

		const Logger& logger() const { return m_logger; }
		Logger& logger() { return m_logger; }

		// private members
	private:
		Logger m_logger;
		std::shared_ptr<IParser> m_parser;

		OriginalDataContainer m_originalData;
		ReducedDataContainer m_data;
	};
}