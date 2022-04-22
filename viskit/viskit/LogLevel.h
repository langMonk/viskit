///
/// \author Bartosz Minch <minch@agh.edu.pl>
/// \date 22.04.2019
///

#pragma once

namespace viskit
{
    /// <summary>
    /// Levels of logs: Info, Warning (viskit can operate), Error (viskit crush), Debug (only in debug mode)
    /// <!summary>
    enum class LogLevel
    {
        Debug,
        Info,
        Warning,
        Error,
    };
}