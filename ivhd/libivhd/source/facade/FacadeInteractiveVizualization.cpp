#include "facade\FacadeInteractiveVizualization.h"

namespace ivhd::facade
{
	FacadeInteractiveVizualization::FacadeInteractiveVizualization(LogHandler logHandler)
		: m_core(std::make_shared<core::Core>(logHandler))
	{

	}

	void FacadeInteractiveVizualization::loadDataFile(std::string dataFilePath, IParser& parser)
	{
		return parser.loadFile(dataFilePath);
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
