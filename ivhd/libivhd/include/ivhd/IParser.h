///
/// \author Bartosz Minch <minch@agh.edu.pl>
/// \date 18.04.2019
///

#pragma once

namespace ivhd
{
	class IParser
	{
		// public methods
	public:
		/// <summary>
		/// Called, when parser is being created.
		/// </summary>
		virtual void initialize() = 0;

		/// <summary>
		/// Load specified file into kNN structure
		/// </summary>
		virtual void loadFile(std::string filePath) = 0;

		/// <summary>
		/// Called, when parser is finishing the load method.
		/// </summary>
		virtual void finalize() = 0;

	};
}