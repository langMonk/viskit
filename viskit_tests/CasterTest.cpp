///
///\author Bartosz Minch <minch@agh.edu.pl>
///\date 13.05.2019
///

#include <gtest/gtest.h>
#include <viskit/embed/cast/CasterRandom.h>

#include <viskit_tests/ViskitTest.h>
#include <viskit_tests/TestUtils.h>

using Logs = std::pair<LogLevel, std::string>;

TEST(CasterRandomTest, Casting)
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
    viskit::embed::cast::CasterRandom caster{core->system()};

    auto csvFile = resourcesDirectory().string() + "/mnist_20_pca30.csv";

    parser->loadFile(csvFile, *particleSystem);

    auto coords = particleSystem->originalCoordinates();

    EXPECT_EQ(particleSystem->countParticles(), 20);
    EXPECT_EQ(coords.size(), 20);

    auto dataPoints = particleSystem->calculationData();

    caster.calculatePositions(*particleSystem);

    auto positions = dataPoints->m_pos;
    for (int i = 0; i < particleSystem->countParticles() - 1; i++)
    {
        //ASSERT_NE(positions[i], glm::vec4(0.0f, 0.0f, 0.0f, 0.0f));
        //ASSERT_NE(positions[i], positions[i + 1]);
    }
}
