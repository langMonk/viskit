///
/// \author Bartosz Minch <minch@agh.edu.pl>
/// \date 28.04.2019
///

#include "viskit/InteractiveVisualizationBuilder.h"
#include "facade/FacadeInteractiveVisualization.h"

namespace viskit
{ 
	std::shared_ptr<IInteractiveVisualization> createVisKit(LogHandler logHandler)
	{
		try
		{
			return std::make_shared<facade::FacadeInteractiveVisualization>(logHandler);
		}
		catch(std::exception& exception)
		{
			std::string message = "Failed to create IVHD: ";
			message += exception.what();
			logHandler(LogLevel::Error, message);
			return nullptr;
		}
	}
}
