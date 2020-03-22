///
/// \author Bartosz Minch <minch@agh.edu.pl>
/// \date 22.04.2019
///

#pragma once

namespace ivhd
{
	/// <summary>
	/// Levels of logs: Info, Warning (ivhd can operate), Error (ivhd crush), Debug (only in debug mode)
	/// <!summary>
	enum class LogLevel
	{
		Debug,
		Info,
		Warning,
		Error,
	};
}