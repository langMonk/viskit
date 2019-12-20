///
/// \author Bartosz Minch <minch@agh.edu.pl>
/// \date 28.04.2019
///

#include "facade/FacadeResourceFactory.h"
#include "facade/FacadeResourceCollection.h"
#include "facade/FacadeInteractiveVizualization.h"
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
			return std::make_shared<facade::FacadeParserCSV>(m_ext_ivhd.core());
		}
		else
		{
			return nullptr;
		}
	}

	std::shared_ptr<ICaster> FacadeResourceFactory::createCaster(CasterType type)
	{
		if (type == CasterType::Random)
		{
			return std::make_shared<facade::FacadeCasterRandom>(m_ext_ivhd.core());
		}
		else
		{
			return nullptr;
		}
	}

	std::shared_ptr<IParticleSystem> FacadeResourceFactory::createParticleSystem()
	{
		return std::make_shared<facade::FacadeParticleSystem>(m_ext_ivhd.core());
	}
}