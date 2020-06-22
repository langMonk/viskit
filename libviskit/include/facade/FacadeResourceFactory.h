///
/// \author Bartosz Minch <minch@agh.edu.pl>
/// \date 28.04.2019
///

#pragma once

#include "viskit/IResourceFactory.h"

namespace viskit::facade
{
	class FacadeInteractiveVisualization;

	/// <summary>
	/// Implementation of IResourceFactory interface.
	/// </summary>
	class FacadeResourceFactory : public IResourceFactory
	{
		// public construction and destruction methods
	public:
		explicit FacadeResourceFactory(FacadeInteractiveVisualization& viskit);

		// public methods
	public:
		std::shared_ptr<IParser> createParser(ParserType type) override;

		std::shared_ptr<IGraphGenerator> createGraphGenerator(GraphGeneratorType type) override;

		std::shared_ptr<ICaster> createCaster(CasterType type, OptimizerType optimizer) override;
		
		std::shared_ptr<IParticleSystem> createParticleSystem() override;
		
		std::shared_ptr<IGraph> createGraph() override;

		std::shared_ptr<IMetric> createMetricCalculator() override;

	private:
		FacadeInteractiveVisualization& m_ext_viskit;
	};
}