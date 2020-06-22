///
///\author Bartosz Minch <minch@agh.edu.pl>
///\date 13.05.2019
///

#include <gtest/gtest.h>
#include <embed/cast/CasterRandom.h>

#include "ViskitTest.h"
#include "TestUtils.h"

namespace viskit_test
{
    class CasterRandomTest : public ViskitTest {};

    TEST_F(CasterRandomTest, Casting)
    {
        viskit::embed::cast::CasterRandom caster{core->system()};

        auto csvFile = utils::resourcesDirectory().string() + "/mnist_20_pca30.csv";

        parser->loadFile(csvFile, *particleSystem);

        auto coords = particleSystem->originalCoordinates();

        EXPECT_EQ(particleSystem->countParticles(), 20);
        EXPECT_EQ(coords.size(), 20);

        auto dataPoints = particleSystem->calculationData();

        caster.calculatePositions(*particleSystem);

        auto positions = dataPoints->m_pos;
        for (int i = 0; i < particleSystem->countParticles() - 1; i++)
        {
            EXPECT_NE(positions[i], glm::vec4(0.0f, 0.0f, 0.0f, 0.0f));
            EXPECT_NE(positions[i], positions[i + 1]);
        }
    }
}
