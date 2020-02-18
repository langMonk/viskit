#include "facade\FacadeInteractiveVizualization.h"
#include <vector>

namespace ivhd::facade
{
	FacadeInteractiveVizualization::FacadeInteractiveVizualization(LogHandler logHandler)
		: m_core(std::make_shared<core::Core>(logHandler))
	{

	}

	std::shared_ptr<core::Core> FacadeInteractiveVizualization::core() const
	{
		return m_core;
	}

	void FacadeInteractiveVizualization::subscribeOnCastingStepFinish(CasterEventHandler handler)
	{
		m_onCastingStepFinished = handler;
	}

	void FacadeInteractiveVizualization::currentCaster(std::shared_ptr<ivhd::ICaster> caster)
	{
		if(caster != nullptr)
		{
			m_currentCaster = caster;
		}
	}

	void FacadeInteractiveVizualization::startCasting()
	{
		m_castingRunning = true;
		
		m_core->enqueueToThreadPool([&]() {
			while(m_castingRunning)
			{
				m_currentCaster->castParticleSystem();
				m_onCastingStepFinished();
			}
		});
	}

	void FacadeInteractiveVizualization::stopCasting()
	{
		m_castingRunning = false;
	}

	void FacadeInteractiveVizualization::pauseCasting()
	{
		m_castingRunning = false;
	}

	std::vector<std::pair<float, float>> FacadeInteractiveVizualization::calculateBoundingBox()
	{
		std::vector<std::pair<float, float>> vec;
		const auto pair = std::pair < float, float >(0.0f, 0.0f);
		vec.push_back(pair);
		return vec;
	}

	IParticleSystem& FacadeInteractiveVizualization::particleSystem()
	{
		return m_particleSystem;
	}

	particles::ParticleSystem& FacadeInteractiveVizualization::internalParticleSystem()
	{
		return m_internalParticleSystem;
	}
	
	IResourceFactory& FacadeInteractiveVizualization::resourceFactory()
	{
		return m_resourceFactory;
	}
}
