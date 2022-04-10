///
/// \author Bartosz Minch <minch@agh.edu.pl>
/// \date 28.04.2019
///

#include <viskit/facade/FacadeInteractiveVisualization.h>
#include <viskit/viskit/InteractiveVisualizationBuilder.h>

namespace viskit {
std::shared_ptr<IInteractiveVisualization> createViskit(const LogHandler& logHandler)
{
    try {
        return std::make_shared<facade::FacadeInteractiveVisualization>(logHandler);
    } catch (std::exception& exception) {
        std::string message = "Failed to create CPU IVHD resource: ";
        message += exception.what();
        logHandler(LogLevel::Error, message);
        return nullptr;
    }
}
}
