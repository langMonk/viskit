///
/// \author Bartosz Minch <minch@agh.edu.pl>
/// \date 28.04.2019
///

#include "facade/FacadeResourceFactory.h"
#include "facade/FacadeInteractiveVizualization.h"
#include "facade/FacadeCasterMDS.h"
#include "facade/FacadeCasterRandom.h"
#include "facade/FacadeParserCSV.h"

namespace ivhd::facade
{
	FacadeResourceFactory::FacadeResourceFactory(FacadeInteractiveVizualization& ivhd)
		: m_ext_ivhd(ivhd)
	{
	}

	std::shared_ptr<IParser> FacadeResourceFactory::createParser(ParserType type)
	{
		if (type == ParserType::Csv)
		{
			return std::make_shared<facade::FacadeParserCSV>(*m_ext_ivhd.core()->particleSystem());
		}
		else
		{
			return nullptr;
		}
	}

	std::shared_ptr<ICaster> FacadeResourceFactory::createCaster(CasterType type)
	{
		if (type == CasterType::Mds)
		{
			return std::make_shared<facade::FacadeCasterMDS>(*m_ext_ivhd.core()->particleSystem());
		}
		else if (type == CasterType::Random)
		{
			return std::make_shared<facade::FacadeCasterRandom>(*m_ext_ivhd.core()->particleSystem());
		}
		else
		{
			return nullptr;
		}
	}
}