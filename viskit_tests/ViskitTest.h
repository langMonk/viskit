///
/// \author Bartosz Minch <minch@agh.edu.pl>
/// \date 14.06.2020
///

#pragma once

#include <viskit/particles/ParticleSystem.h>
#include <viskit/core/Core.h>
#include <viskit/parse/ParserCSV.h>
#include <viskit/parse/Parser.h>
#include <viskit/graph/Graph.h>
#include <viskit/viskit/LogLevel.h>

#include <memory>

using namespace viskit;

using ::testing::TestWithParam;

namespace viskit_test
{
    using Logs = std::pair<viskit::LogLevel, std::string>;

    class ViskitTest : public TestWithParam<int>
    {
    public:
        ViskitTest() = default;

        ~ViskitTest() override = default;

        ViskitTest(ViskitTest const &) = delete;

        ViskitTest &operator=(ViskitTest const &) = delete;

        ViskitTest(ViskitTest &&) noexcept = delete;

        ViskitTest &operator=(ViskitTest &&) noexcept = delete;

        // protected methods
    protected:
        void SetUp() override
        {
            logsCount = 0;
            auto handler = [&](viskit::LogLevel level, const std::string &message)
            {
                logs.emplace_back(level, message);
                logsCount++;
            };

            core = std::make_shared<core::Core>(handler);
            particleSystem = std::make_shared<particles::ParticleSystem>(core->system());
            parser = std::make_shared<parse::ParserCSV>(core->system());
            graph = std::make_shared<Graph>(core->system());
        }

        void TearDown() override
        {

        }

        // protected members
    protected:
        std::shared_ptr<core::Core> core;
        std::shared_ptr<particles::ParticleSystem> particleSystem;
        std::shared_ptr<parse::ParserCSV> parser;
        std::shared_ptr<Graph> graph;
        std::vector <Logs> logs{};
        size_t logsCount{};
    };
}