///
/// \author Bartosz Minch <minch@agh.edu.pl>
/// \date 27.04.2019
///

#include <gtest/gtest.h>

#include "ViskitTest.h"

namespace viskit_test
{
    class LoggerTest : public ViskitTest {};

	TEST_F(LoggerTest, logging)
	{
        core->logger().logInfo("Info: 1");
		EXPECT_EQ(logs.size(), logsCount);
		EXPECT_EQ(logs.back().first, viskit::LogLevel::Info);
		EXPECT_EQ(logs.back().second, "Info: 1");

        core->logger().logInfo("Info: 2");
		EXPECT_EQ(logs.size(), logsCount);
		EXPECT_EQ(logs.back().first, viskit::LogLevel::Info);
		EXPECT_EQ(logs.back().second, "Info: 2");

        core->logger().logError("Error: 1");
		EXPECT_EQ(logs.size(), logsCount);
		EXPECT_EQ(logs.back().first, viskit::LogLevel::Error);
		EXPECT_EQ(logs.back().second, "Error: 1");
	}
}
