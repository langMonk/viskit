#pragma once

#include <memory>
#include <functional>

#include "IInteractiveVisualization.h"
#include "IResourceCollection.h"
#include "ivhd/LogLevel.h"
#include "facade/FacadeResourceCollection.h"

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
	std::shared_ptr<IInteractiveVisualization> createIVHD(LogHandler logHandler = LogHandler{});

	/// <summary>
	/// Creates the IVHD resource collection.
	/// </summary>
	/// <returns>The created resource collection or nullptr in case of an error.</returns>
	template<typename T>
	std::shared_ptr<IResourceCollection<T>> createResourceCollection()
	{
		try
		{
			return std::make_shared<facade::FacadeResourceCollection<T>>();
		}
		catch (std::exception& e)
		{
			return nullptr;
		}
	}
}