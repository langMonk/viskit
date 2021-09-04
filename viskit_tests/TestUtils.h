///
/// \author Bartosz Minch <minch@agh.edu.pl>
/// \date 14.05.2019
///

#pragma once

#include <filesystem>

inline void dump(Graph graph, const std::string& filePath, const std::string& fileName)
{
    std::ofstream m_file;

    m_file.open(filePath + "\\" + fileName + ".txt");
    for (int i = 0; i < graph.size(); i++)
    {
        if (const auto neighbors = graph.getNeighbors(i))
        {
            for (const auto neighbor : *neighbors)
            {
                if (neighbor.type == viskit::NeighborsType::Near)
                {
                    m_file << neighbor.i << "," << neighbor.j << "," << neighbor.r << "," << "Near" << std::endl;
                }
                else if (neighbor.type == viskit::NeighborsType::Far)
                {
                    m_file << neighbor.i << "," << neighbor.j << "," << neighbor.r << "," << "Far" << std::endl;
                }
                else if (neighbor.type == viskit::NeighborsType::Reverse)
                {
                    m_file << neighbor.i << "," << neighbor.j << "," << neighbor.r << "," << "Reverse" << std::endl;
                }
                else
                {
                    m_file << neighbor.i << "," << neighbor.j << "," << neighbor.r << "," << "Random" << std::endl;
                }
            }
        }
    }

    m_file.close();
}

static std::filesystem::path assetsDirectory()
{
    std::filesystem::path currentPath = std::filesystem::current_path();
    while (true)
    {
        if (currentPath.empty())
        {
            return currentPath;
        }
        if (currentPath.stem() == "viskit")
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

