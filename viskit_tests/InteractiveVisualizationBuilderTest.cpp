///
/// \author Bartosz Minch <minch@agh.edu.pl>
/// \date 27.04.2019
///

#include <gtest/gtest.h>

#include <viskit/viskit/InteractiveVisualizationBuilder.h>
#include <viskit/viskit/IInteractiveVisualization.h>

TEST(InteractiveVisualizationBuilderTest, createVisKit)
{
    const auto ivhd = viskit::createViskit();
    EXPECT_NE(ivhd, nullptr);
}

TEST(InteractiveVisualizationBuilderTest, createTwoInstances)
{
    auto ivhd1 = viskit::createViskit();
    auto ivhd2 = viskit::createViskit();

    EXPECT_NE(ivhd1, nullptr);
    EXPECT_NE(ivhd2, nullptr);

    ivhd1 = nullptr;
    ivhd2 = nullptr;
}
