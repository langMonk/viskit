#include "facade\FacadeInteractiveVizualization.h"
#include <exception>

namespace ivhd::facade
{
	FacadeInteractiveVizualization::FacadeInteractiveVizualization(LogHandler logHandler)
		: m_core(std::make_shared<core::Core>(logHandler))
	{

	}

	IResourceFactory& FacadeInteractiveVizualization::resourceFactory()
	{
		return m_resourceFactory;
	}
}
