///
/// \author Bartosz Minch <minch@agh.edu.pl>
/// \date 28.04.2020
///

#include "facade/gpu/FacadeGpuResourceFactory.h"
#include "facade/FacadeInteractiveVisualization.h"
#include "facade/gpu/FacadeGpuCasterMomentum.h"
#include "facade/gpu/FacadeGpuGraphGeneratorFaiss.h"

namespace ivhd::facade::gpu
{
	FacadeGpuResourceFactory::FacadeGpuResourceFactory(FacadeInteractiveVisualization& ivhd)
		: m_ext_ivhd(ivhd)
	{
	}

	std::shared_ptr<IGraphGenerator> FacadeGpuResourceFactory::createGraphGenerator(const GraphGeneratorType type)
	{
		std::shared_ptr<IGraphGenerator> generator = nullptr;
		
		if (type == GraphGeneratorType::Faiss)
		{
			generator = std::make_shared<FacadeGpuGraphGeneratorFaiss>(m_ext_ivhd.core());
		}
		return generator;
	}

	std::shared_ptr<IGpuCaster> FacadeGpuResourceFactory::createCaster(const CasterType type, const OptimizerType optimizer)
	{
		std::shared_ptr<IGpuCaster> caster = nullptr;

		if (type == CasterType::IVHD && optimizer == OptimizerType::Momentum)
		{
			caster = std::make_shared<FacadeGpuCasterMomentum>(m_ext_ivhd.core());
		}

		return caster;
	}
}