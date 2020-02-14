///
/// \author Bartosz Minch <minch@agh.edu.pl>
/// \date 28.04.2019
///

#include "ivhd/InteractiveVizualizationBuilder.h"
#include "facade/FacadeInteractiveVizualization.h"

namespace ivhd
{ 
	std::shared_ptr<IInteractiveVizualization> createIVHD(LogHandler logHandler)
	{
		try
		{
			return std::make_shared<facade::FacadeInteractiveVizualization>(logHandler);
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
