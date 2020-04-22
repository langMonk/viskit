///
/// \author Bartosz Minch <minch@agh.edu.pl>
/// \date 28.04.2020
///

#pragma once

#include "ivhd/IGpuResourceFactory.h"

namespace ivhd::facade
{
	class FacadeInteractiveVisualization;
}

namespace ivhd::facade::gpu
{
	/// <summary>
	/// Implementation of IGpuResourceFactory interface.
	/// </summary>
	class FacadeGpuResourceFactory : public IGpuResourceFactory
	{
		// public construction and destruction methods
	public:
		FacadeGpuResourceFactory(FacadeInteractiveVisualization& ivhd);

		// public methods
	public:
		std::shared_ptr<IGraphGenerator> createGraphGenerator(GraphGeneratorType type) override;

		std::shared_ptr<IGpuCaster> createCaster(CasterType type, OptimizerType optimizer) override;

	private:
		FacadeInteractiveVisualization& m_ext_ivhd;
	};
}