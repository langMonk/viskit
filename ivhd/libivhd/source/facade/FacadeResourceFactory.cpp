///
/// \author Bartosz Minch <minch@agh.edu.pl>
/// \date 28.04.2019
///

#include "facade/FacadeResourceFactory.h"
#include "facade/FacadeInteractiveVizualization.h"
#include "facade/FacadeCasterRandom.h"
#include "facade/FacadeParserCSV.h"
#include "facade/FacadeGraphGeneratorKDTree.h"
#include "facade/FacadeGraphGeneratorBruteForce.h"
#include "facade/FacadeCasterForceDirected.h"
#include "facade/FacadeCasterAdadelta.h"
#include "facade/FacadeCasterAdam.h"
#include "facade/FacadeCasterNesterov.h"

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

	std::shared_ptr<IGraphGenerator> FacadeResourceFactory::createGraphGenerator(GraphGeneratorType type)
	{
		std::shared_ptr<IGraphGenerator> generator = nullptr;
		
		if (type == GraphGeneratorType::KDTreeBased)
		{
			generator = std::make_shared<facade::FacadeGraphGeneratorKDTree>(m_ext_ivhd.core());
		}
		else if (type == GraphGeneratorType::BruteForce)
		{
			generator = std::make_shared<facade::FacadeGraphGeneratorBruteForce>(m_ext_ivhd.core());
		}

		return generator;
	}

	std::shared_ptr<ICaster> FacadeResourceFactory::createCaster(CasterType type, OptimizerType optimizer)
	{
		std::shared_ptr<ICaster> caster = nullptr;
			
		if (type == CasterType::Random)
		{
			caster = std::make_shared<facade::FacadeCasterRandom>(m_ext_ivhd.core());
		}
		else if (type == CasterType::IVHD && optimizer == OptimizerType::ForceDirected)
		{
			caster = std::make_shared<facade::FacadeCasterForceDirected>(m_ext_ivhd.core());
		}
		else if (type == CasterType::IVHD && optimizer == OptimizerType::Adadelta)
		{
			caster = std::make_shared < facade::FacadeCasterAdadelta> (m_ext_ivhd.core());
		}
		else if (type == CasterType::IVHD && optimizer == OptimizerType::Adam)
		{
			caster = std::make_shared < facade::FacadeCasterAdam>(m_ext_ivhd.core());
		}
		else if (type == CasterType::IVHD && optimizer == OptimizerType::Nesterov)
		{
			caster = std::make_shared < facade::FacadeCasterNesterov>(m_ext_ivhd.core());
		}
		return caster;
	}
}
