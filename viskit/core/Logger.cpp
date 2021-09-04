///
/// \author Bartosz Minch <minch@agh.edu.pl>
/// \date 18.04.2019
///

#include <utility>
#include <viskit/core/Logger.h>

namespace viskit::core
{
	Logger::Logger(OnLogAdded handler)
		: m_onLogAddedHandler(std::move(handler))
	{
	}

	void Logger::logInfo(std::string message) const
	{
		if (m_onLogAddedHandler)
		{
			m_onLogAddedHandler(LogLevel::Info, std::move(message));
		}
	}

	void Logger::logWarning(std::string message) const
	{
		if (m_onLogAddedHandler)
		{
			m_onLogAddedHandler(LogLevel::Warning, std::move(message));
		}
	}

	void Logger::logError(std::string message) const
	{
		if (m_onLogAddedHandler)
		{
			m_onLogAddedHandler(LogLevel::Error, std::move(message));
		}
	}

	void Logger::logDebug(std::string message) const
	{
		if (m_onLogAddedHandler)
		{
			m_onLogAddedHandler(LogLevel::Debug, std::move(message));
		}
	}
}