///
/// \author Bartosz Minch <minch@agh.edu.pl>
/// \date 18.04.2019
///

#pragma once

#include <memory>
#include "ivhd/IKnnGraph.h"

namespace ivhd::core
{
	class ParticleSystem
	{
		// public construction and destruction methods
	public:
		ParticleSystem();

	private:
		std::shared_ptr<IKnnGraph> m_distanceMatrix;


	};
}