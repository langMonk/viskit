///
/// \author Bartosz Minch <minch@agh.edu.pl>
/// \date 27.04.2019
///

#include <gtest/gtest.h>
#include <viskit/InteractiveVisualizationBuilder.h>
#include <viskit/IInteractiveVisualization.h>

namespace libivhd_test
{
	TEST(InteractiveVisualizationBuilderTest, createIVHD)
	{
		const auto ivhd = viskit::createIVHD();
		EXPECT_NE(ivhd, nullptr);
	}

	TEST(InteractiveVisualizationBuilderTest, createTwoInstances)
	{
		auto ivhd1 = viskit::createIVHD();
		auto ivhd2 = viskit::createIVHD();

		EXPECT_NE(ivhd1, nullptr);
		EXPECT_NE(ivhd2, nullptr);

		ivhd1 = nullptr;
		ivhd2 = nullptr;
	}
}