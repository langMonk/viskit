///
/// \author Bartosz Minch <minch@agh.edu.pl>
/// \date 27.04.2019
///

#include <gtest/gtest.h>

#include <viskit_tests/ViskitTest.h>

using Logs = std::pair<LogLevel, std::string>;

TEST(LoggerTest, logging)
{
    std::vector<Logs> logs;
    auto logsCount = 0;
    auto handler = [&](viskit::LogLevel level, const std::string &message)
            {
        logs.emplace_back(level, message);
        logsCount++;
            };

    std::shared_ptr<core::Core> core = std::make_shared<core::Core>(handler);
    std::shared_ptr<particles::ParticleSystem> particleSystem = std::make_shared<particles::ParticleSystem>(core->system());
    std::shared_ptr<parse::ParserCSV> parser = std::make_shared<parse::ParserCSV>(core->system());
    std::shared_ptr<Graph> graph = std::make_shared<Graph>(core->system());

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

