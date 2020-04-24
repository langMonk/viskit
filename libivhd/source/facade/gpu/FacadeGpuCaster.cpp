#include <utility>
#include <memory>
#include <caster_cuda_ab.h>
#include <caster_cuda_adadelta.h>
#include <caster_cuda_adam.h>
#include <caster_cuda_nesterov.h>

#include "facade/gpu/FacadeGpuCaster.h"

namespace ivhd::facade::gpu
{
	FacadeGpuCaster::FacadeGpuCaster(std::shared_ptr<core::Core> core)
		: m_ext_core(std::move(core))
	{
	}

	std::shared_ptr<CasterCuda> FacadeGpuCaster::createCaster(int n, ErrorHandler onError, 
												PositionHandler onPos, OptimizerType type)
	{
		std::shared_ptr<CasterCuda> cudaCaster;

		if (type == OptimizerType::Momentum) 
		{
			cudaCaster = std::make_shared<CasterCudaAB>(n, onError, onPos);
		} 
		else if (type == OptimizerType::Nesterov) 
		{
			cudaCaster = std::make_shared<CasterCudaNesterov>(n, onError, onPos);
		} 
		else if (type == OptimizerType::Adadelta) 
		{
			cudaCaster = std::make_shared<CasterCudaAdadelta>(n, onError, onPos);
		} 
		else if (type == OptimizerType::Adam) 
		{
			cudaCaster = std::make_shared<CasterCudaAdam>(n, onError, onPos);
		}

		return cudaCaster;
	}

	void FacadeGpuCaster::calculatePositions(IParticleSystem& ps) 
	{
		m_ext_core->logger().logWarning("[Gpu Caster] calculatePositions() metod not available for GPU Casting. Use step() method.");
	}

	void FacadeGpuCaster::calculateForces(IParticleSystem& ps, IGraph& graph)
	{
		m_ext_core->logger().logWarning("[Gpu Caster] calculateForces() metod not available for GPU Casting. Use step() method.");
	}

	void FacadeGpuCaster::step(IParticleSystem& ps, IGraph& graph)
	{
		if(m_initialized)
		{
			m_internalCaster->simul_step();
		}
		else
		{
			m_ext_core->logger().logError("[Gpu Caster] Step method called without prior initialization." 
			"Call initialize() method before using this caster.");
		}
		
	}

    void FacadeGpuCaster::initialize(IParticleSystem& ps, IGraph& graph)
	{
		m_ext_core->logger().logInfo("[Gpu Caster] Initializing GPU resources...");

		// set up error and positions callbacks 
		ErrorHandler onError = [&](float err) -> void {};		

		PositionHandler onPos = [&](vector<float2>& positions) -> void {
			auto internalPositions = ps.positions();
			for (unsigned i = 0; i < positions.size(); i++) {
				internalPositions[i].x = positions[i].x;
				internalPositions[i].y = positions[i].y;
			}
		};

		m_internalCaster = createCaster(ps.countParticles(), onError, onPos, optimizerType());

		// set up initial positions inside GPU caster
		auto positions = ps.positions();
		for (auto i = 0; i < ps.countParticles(); i++)
		{
			m_internalCaster->positions[i].x = positions[i].x;
			m_internalCaster->positions[i].y = positions[i].y;
		}
		
		// set up distances inside GPU caster
		for (auto index = 0; index < graph.size(); index++)
		{
			auto neighbors = graph.getNeighbors(index);
			
			for (auto neighbor : neighbors)
			{
				if(neighbor.type == NeighborsType::Random)
				{
					m_internalCaster->addDistance(DistElem(neighbor.i, neighbor.j, DistElemType::etRandom, neighbor.r));
				}
				else if(neighbor.type == NeighborsType::Near)
				{
					m_internalCaster->addDistance(DistElem(neighbor.i, neighbor.j, DistElemType::etNear, neighbor.r));
				}
			}	
		}

		m_initialized = true;

		m_ext_core->logger().logInfo("[Gpu Caster] Finished.");
	}
}
