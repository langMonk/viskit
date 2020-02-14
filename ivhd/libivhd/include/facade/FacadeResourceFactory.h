///
/// \author Bartosz Minch <minch@agh.edu.pl>
/// \date 28.04.2019
///

#pragma once

#include "ivhd/IResourceFactory.h"

namespace ivhd::facade
{
	class FacadeInteractiveVizualization;

	/// <summary>
	/// Implementation of IVHD interface.
	/// </summary>
	class FacadeResourceFactory : public IResourceFactory
	{
		// public construction and destruction methods
	public:
		FacadeResourceFactory(FacadeInteractiveVizualization& ivhd);

		// public methods
	public:
		std::shared_ptr<IParser> createParser(ParserType type) override;

		std::shared_ptr<IGraphGenerator> createGraphGenerator(GraphGeneratorType type) override;

		std::shared_ptr<ICaster> createCaster(CasterType type) override;

	private:
		FacadeInteractiveVizualization& m_ext_ivhd;
	};
}