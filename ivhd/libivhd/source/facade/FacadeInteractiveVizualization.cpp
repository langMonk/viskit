#include "facade\FacadeInteractiveVizualization.h"
#include <exception>

namespace ivhd::facade
{
	FacadeInteractiveVizualization::FacadeInteractiveVizualization(LogHandler logHandler)
		: m_ext_core(std::make_shared<core::Core>(logHandler))
	{

	}

	void FacadeInteractiveVizualization::loadDataFile(std::string dataFilePath, std::shared_ptr<IParser> parser)
	{
		try
		{
			auto internalParser = dynamic_cast<FacadeParserCSV*>(parser.get());
			internalParser->loadFile(dataFilePath);
		}
		catch (std::exception& ex)
		{
			m_ext_core->logger().logWarning("Failed to load data file: " + dataFilePath);
		}
	}

	IResourceFactory& FacadeInteractiveVizualization::resourceFactory()
	{
		return m_resourceFactory;
	}

	IParticleSystem& FacadeInteractiveVizualization::particleSystem()
	{
		return m_particleSystem;
	}
}
