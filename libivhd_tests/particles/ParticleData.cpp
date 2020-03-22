///
/// \author Bartosz Minch <minch@agh.edu.pl>
/// \date 13.05.2019
///

#include <gtest/gtest.h>
#include <particles/ParticleData.h>

namespace libivhd_test
{
	TEST(ParticleData, create)
	{
		ivhd::particles::ParticleData data;
		data.generate(30);
	}
}
