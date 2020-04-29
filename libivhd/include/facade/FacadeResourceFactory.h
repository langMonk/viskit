///
/// \author Bartosz Minch <minch@agh.edu.pl>
/// \date 28.04.2019
///

#pragma once

#include "ivhd/IResourceFactory.h"

namespace ivhd::facade
{
	class FacadeInteractiveVisualization;

	/// <summary>
	/// Implementation of IResourceFactory interface.
	/// </summary>
	class FacadeResourceFactory : public IResourceFactory
	{
		// public construction and destruction methods
	public:
		FacadeResourceFactory(FacadeInteractiveVisualization& ivhd);

		// public methods
	public:
		std::shared_ptr<IParser> createParser(ParserType type) override;

		std::shared_ptr<IGraphGenerator> createGraphGenerator(GraphGeneratorType type) override;

		std::shared_ptr<IGraphGenerator> createGraphGeneratorGPU(GraphGeneratorType type) override;

		std::shared_ptr<ICaster> createCaster(CasterType type, OptimizerType optimizer) override;
		
		std::shared_ptr<IParticleSystem> createParticleSystem() override;
		
		std::shared_ptr<IGraph> createGraph() override;

	private:
		FacadeInteractiveVisualization& m_ext_ivhd;
	};
}