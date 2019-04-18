///
/// \author Bartosz Minch <minch@agh.edu.pl>
/// \date 18.04.2019
///

#pragma once

namespace ivhd
{
	/// <summary>
	/// The main interface for controlling IVHD.
	/// </summary>
	class IInteractiveVizualization
	{
	public:
		IInteractiveVizualization();

		// protected construction and destruction methods
	protected:
		virtual ~IInteractiveVizualization() = default;

	};
}