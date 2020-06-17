///
///\author Bartosz Minch <minch@agh.edu.pl>
///\date 13.05.2019
///

#include <gtest/gtest.h>
#include <embed/cast/CasterRandom.h>
#include <parse/ParserCSV.h>
#include <core/Core.h>
#include "TestUtils.h"

namespace libivhd_test
{
	TEST(CasterTest, CasterRandom)
	{
		using Logs = std::pair<viskit::LogLevel, std::string>;

		std::vector<Logs> logs{};
		size_t count = 0;

		auto handler = [&logs, &count](viskit::LogLevel level, const std::string& message)
		{
			logs.emplace_back(level, message);
			count++;
		};

		viskit::core::Core core{ handler };
		viskit::particles::ParticleSystem particleSystem{ core.system() };
		viskit::embed::cast::CasterRandom caster{ core.system() };
		viskit::parse::ParserCSV parser{ core.system() };
		Graph graph{ core.system() };

		auto csvFile = utils::resourcesDirectory().string() + "/mnist_20_pca30.csv";

		parser.loadFile(csvFile, particleSystem);

		auto coords = particleSystem.originalCoordinates();

		EXPECT_EQ(particleSystem.countParticles(), 20);
		EXPECT_EQ(coords.size(), 20);

		auto dataPoints = particleSystem.calculationData();

		caster.calculatePositions(particleSystem);

		auto positions = dataPoints->m_pos;
		for (int i = 0; i < particleSystem.countParticles() - 1; i++)
		{
			EXPECT_NE(positions[i], glm::vec4(0.0f, 0.0f, 0.0f, 0.0f));
			EXPECT_NE(positions[i], positions[i + 1]);
		}
	}
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

