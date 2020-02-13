///
/// \author Bartosz Minch <minch@agh.edu.pl>
/// \date 10.02.2020
///

#pragma once

#include "ivhd/IParticleSystem.h"
#include "ivhd/IGraphGenerator.h"
#include "facade/FacadeGraphGenerator.h"
#include "facade/FacadeParticleSystem.h"

namespace ivhd::facade
{
	/// <summary>
	/// Implementation of ICaster interface.
	/// </summary>
	class FacadeGraphGeneratorKDTree : public FacadeGraphGenerator
	{
	public:
		std::shared_ptr<IGraph> generate(std::shared_ptr<ivhd::IParticleSystem>& ps) override;

	private:

	};
}