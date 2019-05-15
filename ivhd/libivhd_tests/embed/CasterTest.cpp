///
/// \author Bartosz Minch <minch@agh.edu.pl>
/// \date 13.05.2019
///

#include <gtest/gtest.h>
#include <embed/cast/CasterRandom.h>
#include <parse/ParserCSV.h>
#include <core/Core.h>
#include "utils.h"

TEST(CasterTest, CasterRandom)
{
	using Logs = std::pair<ivhd::LogLevel, std::string>;

	std::vector<Logs> logs{};
	size_t count = 0;

	auto handler = [&logs, &count](ivhd::LogLevel level, std::string message)
	{
		logs.push_back(std::make_pair(level, message));
		count++;
	};

	ivhd::core::Core core{ handler };
	ivhd::parse::ParserCSV parser{ core.particleSystem() };
	ivhd::embed::cast::CasterRandom caster{ core.particleSystem() };

	auto csvFile = resourcesDirectory().string() + "/mnist_20_pca30.csv";
	parser.loadFile(csvFile);
}

