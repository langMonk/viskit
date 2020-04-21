///
/// \author Bartosz Minch <minch@agh.edu.pl>
/// \date 28.04.2019
///

#include "facade/FacadeResourceFactory.h"
#include "facade/FacadeInteractiveVisualization.h"
#include "facade/FacadeCasterRandom.h"
#include "facade/FacadeParserCSV.h"
#include "facade/FacadeGraphGeneratorKDTree.h"
#include "facade/FacadeGraphGeneratorBruteForce.h"
#include "facade/FacadeGraphGeneratorFaiss.h"
#include "facade/FacadeCasterMomentum.h"
#include "facade/FacadeCasterForceDirected.h"
#include "facade/FacadeCasterAdadelta.h"
#include "facade/FacadeCasterAdam.h"
#include "facade/FacadeCasterNesterov.h"

namespace ivhd::facade
{
	FacadeResourceFactory::FacadeResourceFactory(FacadeInteractiveVisualization& ivhd)
		: m_ext_ivhd(ivhd)
	{
	}

	std::shared_ptr<IParser> FacadeResourceFactory::createParser(const ParserType type)
	{
		if (type == ParserType::Csv)
		{
			return std::make_shared<FacadeParserCSV>(m_ext_ivhd.core());
		}
		return nullptr;
	}

	std::shared_ptr<IGraphGenerator> FacadeResourceFactory::createGraphGenerator(const GraphGeneratorType type)
	{
		std::shared_ptr<IGraphGenerator> generator = nullptr;
		
		if (type == GraphGeneratorType::KDTreeBased)
		{
			generator = std::make_shared<FacadeGraphGeneratorKDTree>(m_ext_ivhd.core());
		}
		else if (type == GraphGeneratorType::BruteForce)
		{
			generator = std::make_shared<FacadeGraphGeneratorBruteForce>(m_ext_ivhd.core());
		}
		else if (type == GraphGeneratorType::Faiss)
		{
			generator = std::make_shared<FacadeGraphGeneratorFaiss>(m_ext_ivhd.core());
		}
		return generator;
	}

	std::shared_ptr<ICaster> FacadeResourceFactory::createCaster(const CasterType type, const OptimizerType optimizer)
	{
		std::shared_ptr<ICaster> caster = nullptr;
			
		if (type == CasterType::Random)
		{
			caster = std::make_shared<FacadeCasterRandom>(m_ext_ivhd.core());
		}
		else if (type == CasterType::IVHD && optimizer == OptimizerType::Momentum)
		{
			caster = std::make_shared<FacadeCasterMomentum>(m_ext_ivhd.core());
		}
		else if (type == CasterType::IVHD && optimizer == OptimizerType::ForceDirected)
		{
			caster = std::make_shared<FacadeCasterForceDirected>(m_ext_ivhd.core());
		}
		else if (type == CasterType::IVHD && optimizer == OptimizerType::Adadelta)
		{
			caster = std::make_shared<FacadeCasterAdadelta>(m_ext_ivhd.core());
		}
		else if (type == CasterType::IVHD && optimizer == OptimizerType::Adam)
		{
			caster = std::make_shared<FacadeCasterAdam>(m_ext_ivhd.core());
		}
		else if (type == CasterType::IVHD && optimizer == OptimizerType::Nesterov)
		{
			caster = std::make_shared<FacadeCasterNesterov>(m_ext_ivhd.core());
		}
		return caster;
	}

	std::shared_ptr<IParticleSystem> FacadeResourceFactory::createParticleSystem()
	{
		return std::make_shared<FacadeParticleSystem>(m_ext_ivhd.core());
	}

	std::shared_ptr<IGraph> FacadeResourceFactory::createGraph()
	{
		return std::make_shared<FacadeGraph>(m_ext_ivhd.core());
	}
}
