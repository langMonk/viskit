///
/// \author Bartosz Minch <minch@agh.edu.pl>
/// \date 27.04.2019
///

#include <gtest/gtest.h>
#include <core/Logger.h>
#include <ivhd/LogLevel.h>

namespace libivhd_test
{
	TEST(LoggerTest, logging)
	{
		using Logs = std::pair<ivhd::LogLevel, std::string>;

		std::vector<Logs> logs{};
		size_t count = 0;

		auto handler = [&logs, &count](ivhd::LogLevel level, const std::string& message)
		{
			logs.emplace_back(level, message);
			count++;
		};

		const ivhd::core::Logger logger{ handler };

		logger.logInfo("Info: 1");
		EXPECT_EQ(logs.size(), count);
		EXPECT_EQ(logs.back().first, ivhd::LogLevel::Info);
		EXPECT_EQ(logs.back().second, "Info: 1");

		logger.logInfo("Info: 2");
		EXPECT_EQ(logs.size(), count);
		EXPECT_EQ(logs.back().first, ivhd::LogLevel::Info);
		EXPECT_EQ(logs.back().second, "Info: 2");

		logger.logError("Error: 1");
		EXPECT_EQ(logs.size(), count);
		EXPECT_EQ(logs.back().first, ivhd::LogLevel::Error);
		EXPECT_EQ(logs.back().second, "Error: 1");
	}
}
