///
/// \author Bartosz Minch <minch@agh.edu.pl>
/// \date 14.05.2019
///

#pragma once

#include <filesystem>

namespace test_utils
{ 
	static std::filesystem::path assetsDirectory()
	{
		std::filesystem::path currentPath = std::filesystem::current_path();
		while (true)
		{
			if (currentPath.empty())
			{
				return currentPath;
			}
			if (currentPath.stem() == "ivhd")
			{
				return currentPath / "assets";
			}

			currentPath = currentPath.parent_path();
		}
	}

	static std::filesystem::path resourcesDirectory()
	{
		return assetsDirectory() / "resources";
	}
}
