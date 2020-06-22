///
/// \author Bartosz Minch <minch@agh.edu.pl>
/// \date 13.06.2020
///

#include <gtest/gtest.h>

#include <graph/generate/BruteForce.h>
#include <graph/generate/Reverse.h>
#include <viskit/Structures.h>
#include <utils/TimeProfiler.h>

#include "TestUtils.h"
#include "ViskitTest.h"

using namespace viskit;

namespace viskit_test
{
    class ReverseTest : public ViskitTest {};

    TEST_F(ReverseTest, Generation)
    {
        generate::BruteForce nearestGenerator{ core->system() };
        generate::Reverse reverseGenerator{ core->system() };

        auto csvFile = utils::resourcesDirectory().string() + "/mnist_7k_pca30.csv";
        parser->loadFile(csvFile, *particleSystem);

        EXPECT_EQ(particleSystem->countParticles(), 7000);
        EXPECT_EQ(particleSystem->originalCoordinates().size(), 7000);

        auto profiler = viskit::utils::TimeProfiler(true);
        profiler.start();
        nearestGenerator.generate(*particleSystem, *graph, 2, true);
        reverseGenerator.generate(*particleSystem, *graph, 1, true);
        profiler.stop();
        profiler.measurementMs();

        EXPECT_EQ(graph->size(), 7000); // 7000 elements (size) and every has 3 NN
        EXPECT_EQ(graph->overallNeighborsCount(), 19669); // not all elements has rkNN

        utils::dump(*graph, "./", "test_reverse");
    }
}