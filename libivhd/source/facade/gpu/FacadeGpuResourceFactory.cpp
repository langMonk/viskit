///
/// \author Bartosz Minch <minch@agh.edu.pl>
/// \date 28.04.2020
///

#include "facade/gpu/FacadeGpuResourceFactory.h"
#include "facade/FacadeInteractiveVisualization.h"
#include "facade/gpu/FacadeGpuCasterMomentum.h"

namespace ivhd::facade::gpu
{
	FacadeGpuResourceFactory::FacadeGpuResourceFactory(FacadeInteractiveVisualization& ivhd)
		: m_ext_ivhd(ivhd)
	{
	}

	std::shared_ptr<IGraphGenerator> FacadeGpuResourceFactory::createGraphGenerator(const GraphGeneratorType type)
	{
		std::shared_ptr<IGraphGenerator> generator = nullptr;
		
		// if (type == GraphGeneratorType::Faiss)
		// {
		// 	generator = std::make_shared<FacadeGraphGeneratorFaiss>(m_ext_ivhd.core());
		// }
		return generator;
	}

	std::shared_ptr<IGpuCaster> FacadeGpuResourceFactory::createCaster(const CasterType type, const OptimizerType optimizer)
	{
		std::shared_ptr<IGpuCaster> caster = nullptr;
		
		auto onError = [&](float err) -> void {};

		auto onPos = [&](vector<float2>& positions) -> void {};

		if (type == CasterType::IVHD && optimizer == OptimizerType::Momentum)
		{
			caster = std::make_shared<FacadeGpuCasterMomentum>(m_ext_ivhd.core(), onError, onPos);
		}

		return caster;
	}
}