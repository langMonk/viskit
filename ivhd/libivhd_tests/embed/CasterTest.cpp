///
/// \author Bartosz Minch <minch@agh.edu.pl>
/// \date 13.05.2019
///

#include <gtest/gtest.h>
#include <embed/cast/CasterRandom.h>
#include <parse/Parser.h>
#include <parse/ParserCsv.h>
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
	ivhd::parse::ParserCSV parser{ core.system()};
	ivhd::embed::cast::CasterRandom caster{ core.system() };
	ivhd::particles::ParticleSystem particleSystem{ core.system() };
	
	auto csvFile = resourcesDirectory().string() + "/mnist_20_pca30.csv";

	parser.loadFile(csvFile, 20, particleSystem);

	auto& coords = particleSystem.originalCoordinates();

	EXPECT_EQ(particleSystem.numAllParticles(), 20);
	EXPECT_EQ(coords.size(), 20);

	auto dataPoints = particleSystem.finalData();

	for (int i = 0; i < particleSystem.numAllParticles(); i++)
	{
		EXPECT_EQ(dataPoints->m_pos[i], glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
	}

	caster.cast(particleSystem);

	auto positions = dataPoints->m_pos.get();
	for (int i = 0; i < particleSystem.numAllParticles()-1; i++)
	{
		EXPECT_NE(positions[i], glm::vec4(0.0f, 0.0f, 0.0f, 0.0f));
		EXPECT_NE(positions[i], positions[i+1]);
	}
}

