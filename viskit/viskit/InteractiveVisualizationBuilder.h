///
/// \author Bartosz Minch <minch@agh.edu.pl>
/// \date 18.04.2019
///

#pragma once

#include <memory>
#include <functional>

#include <viskit/viskit/IInteractiveVisualization.h>
#include <viskit/viskit/ResourceCollection.h>
#include <viskit/viskit/LogLevel.h>

namespace viskit
{
	/// <summary>
	/// A function used as a callback for each log entry added.
	/// </summary>
	/// <param name="level">Logging level: Info, Warning, Debug, Error.</param>
	/// <param name="message>Textual log message.</param>
	using LogHandler = std::function<void(LogLevel level, std::string message)>;

	/// <summary>
	/// Creates the VisKit.
	/// </summary>
	/// <returns>The created VisKit resource or nullptr in case of an error.</returns>
	std::shared_ptr<IInteractiveVisualization> createViskit(const LogHandler& logHandler = LogHandler{});

	/// <summary>
	/// Creates the VisKit, which utilize GPU.
	/// </summary>
	/// <returns>The created VisKit resource or nullptr in case of an error.</returns>
	std::shared_ptr<IInteractiveVisualization> createGpuViskit(const LogHandler& logHandler = LogHandler{});
}