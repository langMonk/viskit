///
/// \author Bartosz Minch <minch@agh.edu.pl>
/// \date 18.04.2019
///

#include "core\Logger.h"

namespace ivhd::core
{
	Logger::Logger(OnLogAdded handler)
		: m_onLogAddedHandler(handler)
	{
	}

	void Logger::logInfo(std::string message)
	{
		if (m_onLogAddedHandler)
		{
			m_onLogAddedHandler(LogLevel::Info, message);
		}
	}

	void Logger::logWarning(std::string message)
	{
		if (m_onLogAddedHandler)
		{
			m_onLogAddedHandler(LogLevel::Warning, message);
		}
	}

	void Logger::logError(std::string message)
	{
		if (m_onLogAddedHandler)
		{
			m_onLogAddedHandler(LogLevel::Error, message);
		}
	}

	void Logger::logDebug(std::string message)
	{
		if (m_onLogAddedHandler)
		{
			m_onLogAddedHandler(LogLevel::Debug, message);
		}
	}
}