#include "core\Logger.h"
///
/// \author Bartosz Minch <minch@agh.edu.pl>
/// \date 18.04.2019
///

namespace ivhd::core
{
	Logger::Logger(OnLogAdded handler)
		: m_handler(handler)
	{
	}

	void Logger::logInfo(std::string message)
	{
		if (m_handler)
		{
			m_handler(LogLevel::Info, message);
		}
	}

	void Logger::logWarning(std::string message)
	{
		if (m_handler)
		{
			m_handler(LogLevel::Warning, message);
		}
	}

	void Logger::logError(std::string message)
	{
		if (m_handler)
		{
			m_handler(LogLevel::Error, message);
		}
	}

	void Logger::logDebug(std::string message)
	{
		if (m_handler)
		{
			m_handler(LogLevel::Debug, message);
		}
	}
}