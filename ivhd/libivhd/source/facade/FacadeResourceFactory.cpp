///
/// \author Bartosz Minch <minch@agh.edu.pl>
/// \date 28.04.2019
///

#include "facade/FacadeResourceFactory.h"
#include "facade/FacadeInteractiveVizualization.h"
#include "facade/FacadeCasterMDS.h"
#include "facade/FacadeParserCSV.h"

namespace ivhd::facade
{
	FacadeResourceFactory::FacadeResourceFactory(FacadeInteractiveVizualization& ivhd)
		: m_ext_ivhd(ivhd)
	{
	}

	std::shared_ptr<IParser> FacadeResourceFactory::createParser(ParserType& type)
	{
		return std::make_shared<facade::FacadeParserCSV>(m_ext_ivhd.particleSystem());
	}

	std::shared_ptr<ICaster> FacadeResourceFactory::createCaster(CasterType& type)
	{
		return std::make_shared<facade::FacadeCasterMDS>(m_ext_ivhd.particleSystem());
	}
}