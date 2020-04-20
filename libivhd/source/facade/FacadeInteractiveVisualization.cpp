#include "facade/FacadeInteractiveVisualization.h"
#include <vector>

namespace ivhd::facade
{
	FacadeInteractiveVisualization::FacadeInteractiveVisualization(LogHandler logHandler)
		: m_core(std::make_shared<core::Core>(logHandler))
	{

	}

	std::shared_ptr<core::Core> FacadeInteractiveVisualization::core() const
	{
		return m_core;
	}

	void FacadeInteractiveVisualization::subscribeOnCastingStepFinish(CasterEventHandler handler)
	{
		m_onCastingStepFinished = handler;
	}

	void FacadeInteractiveVisualization::startCasting(IParticleSystem& ps, IGraph& graph, ICaster& caster)
	{
		m_castingRunning = true;
		
		m_core->enqueueToThreadPool([&]() {
			while(m_castingRunning)
			{
				caster.step(ps, graph);
				m_onCastingStepFinished();

				if(caster.type() == CasterType::Random){ break; }
			}
		});
	}

	void FacadeInteractiveVisualization::stopCasting()
	{
		m_castingRunning = false;
	}

	void FacadeInteractiveVisualization::pauseCasting()
	{
		m_castingRunning = false;
	}

	std::vector<std::pair<float, float>> FacadeInteractiveVisualization::calculateBoundingBox()
	{
		std::vector<std::pair<float, float>> vec;
		const auto pair = std::pair < float, float >(0.0f, 0.0f);
		vec.push_back(pair);
		return vec;
	}

	IResourceFactory& FacadeInteractiveVisualization::resourceFactory()
	{
		return m_resourceFactory;
	}
}
