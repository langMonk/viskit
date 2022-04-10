///
/// \author Bartosz Minch <minch@agh.edu.pl>
/// \date 18.04.2019
///

#include <utility>
#include <viskit/core/System.h>

namespace viskit::core {
System::System(OnLogAdded logHandler)
    : m_logger(std::move(logHandler))
{
}
}