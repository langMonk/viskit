///
/// \author Bartosz Minch <minch@agh.edu.pl>
/// \date 13.07.2019
///

#include <gtest/gtest.h>
#include <embed/cast/CasterRandom.h>
#include <core/Core.h>

TEST(DistanceCalculator, DistanceCalculator)
{
	//using Logs = std::pair<ivhd::LogLevel, std::string>;

	//std::vector<Logs> logs{};
	//size_t count = 0;

	//auto handler = [&logs, &count](ivhd::LogLevel level, std::string message)
	//{
	//	logs.push_back(std::make_pair(level, message));
	//	count++;
	//};

	//ivhd::core::Core core{ handler };
	//ivhd::embed::cast::CasterRandom caster{ core.system() };
	//ivhd::particles::ParticleSystem particleSystem{ core.system() };

	//// Results of all distance calculation was created using python scipy

	//std::vector<float> x{ 1.2f, 1.4f, 1.7f, 15.0f, 12.0f };
	//std::vector<float> y{ 3.4f, 6.4f, 2.1f, 18.1f, 1.0f };
	//ivhd::particles::CoordinatesContainer container;
	//container.emplace_back(x);
	//container.emplace_back(y);
	//particleSystem.loadData(container);

	//auto dist = particleSystem.vectorDistance(0, 1);
	//std::cout << dist;
	//EXPECT_NEAR(dist, 12.67f, 0.01f);
	//particleSystem.clear();
	//container.clear();

	//x = std::vector<float>{ 1.2f, 1.4f, 1.7f };
	//y = std::vector<float>{ 3.4f, 6.4f, 2.1f };
	//container.emplace_back(x);
	//container.emplace_back(y);
	//particleSystem.loadData(container);

	//dist = particleSystem.vectorDistance(0, 1);
	//EXPECT_NEAR(dist, 5.47f, 0.01f);
	//particleSystem.clear();
	//container.clear();

	//x = std::vector<float>{ 6.486f, 1.2315f, 9.876f, 5.345f, 2.123f, 7.567f };
	//y = std::vector<float>{ 4.234f, 1.123f, 5.567f, 8.789f, 6.455f, 3.345f };
	//container.emplace_back(x);
	//container.emplace_back(y);
	//particleSystem.loadData(container);

	//dist = particleSystem.vectorDistance(0, 1);
	//EXPECT_NEAR(dist, 8.49f, 0.1f);
	//particleSystem.clear();
	//container.clear();
}

