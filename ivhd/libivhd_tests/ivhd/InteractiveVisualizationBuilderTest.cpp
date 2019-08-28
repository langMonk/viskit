///
/// \author Bartosz Minch <minch@agh.edu.pl>
/// \date 27.04.2019
///

#include <gtest/gtest.h>
#include <ivhd/InteractiveVizualizationBuilder.h>
#include <ivhd/IInteractiveVizualization.h>

namespace libivhd_test
{
	TEST(InteractiveVisualizationBuilderTest, createIVHD)
	{
		std::shared_ptr<ivhd::IInteractiveVizualization> ivhd = ivhd::createIVHD();
		EXPECT_NE(ivhd, nullptr);
	}

	TEST(InteractiveVisualizationBuilderTest, createTwoInstances)
	{
		std::shared_ptr<ivhd::IInteractiveVizualization> ivhd1 = ivhd::createIVHD();
		std::shared_ptr<ivhd::IInteractiveVizualization> ivhd2 = ivhd::createIVHD();

		EXPECT_NE(ivhd1, nullptr);
		EXPECT_NE(ivhd2, nullptr);

		ivhd1 = nullptr;
		ivhd2 = nullptr;
	}
}