#pragma once

#include <memory>
#include <functional>

#include "IInteractiveVizualization.h"
#include "ivhd/LogLevel.h"

namespace ivhd
{
	/// <summary>
	/// A function used as a callback for each log entry added.
	/// </summary>
	/// <param name="level">Logging level: Info, Warning, Debug, Error.</param>
	/// <param name="message>Textual log message.</param>
	using LogHandler = std::function<void(LogLevel level, std::string message)>;

	/// <summary>
	/// Creates the IVHD.
	/// </summary>
	/// <returns>The created IVHD resource or nullptr in case of an error.</returns>
	std::shared_ptr<IInteractiveVizualization> createIVHD(LogHandler logHandler = LogHandler{}, size_t maxCount = 20);
}