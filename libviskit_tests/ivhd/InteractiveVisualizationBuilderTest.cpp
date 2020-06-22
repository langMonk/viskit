///
/// \author Bartosz Minch <minch@agh.edu.pl>
/// \date 27.04.2019
///

#include <gtest/gtest.h>
#include <viskit/InteractiveVisualizationBuilder.h>
#include <viskit/IInteractiveVisualization.h>

namespace viskit_test
{
    class InteractiveVisualizationBuilderTest : public ::testing::Test {};

	TEST(InteractiveVisualizationBuilderTest, createVisKit)
	{
		const auto ivhd = viskit::createVisKit();
		EXPECT_NE(ivhd, nullptr);
	}

	TEST(InteractiveVisualizationBuilderTest, createTwoInstances)
	{
		auto ivhd1 = viskit::createVisKit();
		auto ivhd2 = viskit::createVisKit();

		EXPECT_NE(ivhd1, nullptr);
		EXPECT_NE(ivhd2, nullptr);

		ivhd1 = nullptr;
		ivhd2 = nullptr;
	}
}