#include "facade\FacadeInteractiveVizualization.h"

namespace ivhd::facade
{
	FacadeInteractiveVizualization::FacadeInteractiveVizualization()
	{
	}

	bool FacadeInteractiveVizualization::loadDataFile(std::string dataFilePath, IParser& parser)
	{
		return true;
	}

	void FacadeInteractiveVizualization::castData(ICaster& caster)
	{
		//caster.cast();
	}

	IResourceFactory& FacadeInteractiveVizualization::resourceFactory()
	{
		return m_resourceFactory;
	}
}
