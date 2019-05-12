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
	using OriginalCoordinatesContainer = std::vector<std::vector<float>>;

	class ParticleSystem
	{
		// public construction and destruction methods
	public:
		ParticleSystem(OnLogAdded handler);

		// public methods
	public:
		OriginalCoordinatesContainer& originalCoordinates() { return m_originalCoordinates; }

		const Logger& logger() const { return m_logger; }
		Logger& logger() { return m_logger; }

		// private members
	private:

		Logger m_logger;

		OriginalCoordinatesContainer m_originalCoordinates;
	};
}