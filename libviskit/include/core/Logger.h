///
/// \author Bartosz Minch <minch@agh.edu.pl>
/// \date 18.04.2019
///

#pragma once

#include <string>
#include <functional>
#include "ivhd/LogLevel.h"

namespace ivhd::core
{
	using OnLogAdded = std::function<void(LogLevel level, std::string message)>;

	/// <summary>
	/// A logger used for logging messages of different levels (warning, info, error etc.).
	/// </summary>
	class Logger
	{
		// public construction and destruction methods
	public:
		explicit Logger(OnLogAdded handler);
		~Logger() = default;

		Logger(const Logger&) = delete;
		Logger(Logger&&) = default;

		Logger& operator=(const Logger&) = delete;
		Logger& operator=(Logger&&) = default;

		// public methods
	public:
		void logInfo(std::string message) const;

		void logWarning(std::string message) const;

		void logError(std::string message) const;

		void logDebug(std::string message) const;

	private:

		OnLogAdded m_onLogAddedHandler;
	};
}
