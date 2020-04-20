#pragma once

#include "caster/caster_cuda.cuh"

class CasterCudaAB : public CasterCuda
{
public:
	CasterCudaAB(int n, std::function<void(float)> onErr, std::function<void(std::vector<float2>&)> onPos)
		: CasterCuda(n, onErr, onPos) {}

	void calculateForces(ivhd::IParticleSystem& ps, ivhd::IGraph& graph) override;

	void calculatePositions(ivhd::IParticleSystem& ps) override;

protected:
	void simul_step_cuda(ivhd::IParticleSystem& ps, ivhd::IGraph& graph) override;
};