///
/// \author Bartosz Minch <minch@agh.edu.pl>
/// \date 18.04.2019
///

#pragma once

#include <memory>
#include <vector>
#include <map>

#include "core/Logger.h"
#include "ivhd/IParser.h"
#include "ivhd/Structures.h"

namespace ivhd::core
{
		// public sub-types
	using CoordinatesContainer = std::vector<std::vector<float>>;
	using DataPointContainer = std::vector<DataPoint>;

	class ParticleSystem
	{
		// public construction and destruction methods
	public:
		ParticleSystem(OnLogAdded handler);

		// public methods
	public:
		CoordinatesContainer& originalCoordinates() { return m_originalCoordinates; }
		CoordinatesContainer& reducedCoordinates() { return m_reducedCoordinates; }
		DataPointContainer& dataPoints() { return m_dataPoints; }

		const Logger& logger() const { return m_logger; }
		Logger& logger() { return m_logger; }

		// private members
	private:
		Logger m_logger;

		CoordinatesContainer m_originalCoordinates;

		CoordinatesContainer m_reducedCoordinates;

		DataPointContainer m_dataPoints;
	};
}