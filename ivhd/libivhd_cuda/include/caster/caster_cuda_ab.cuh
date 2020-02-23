#pragma once

#include "caster/caster_cuda.cuh"

class CasterCudaAB : public CasterCuda
{
public:
	CasterCudaAB(int n, function<void(float)> onErr, function<void(vector<float2>&)> onPos)
		: CasterCuda(n, onErr, onPos) {}

	void calculateForces(ivhd::IParticleSystem& ps, ivhd::IGraph& graph) override;

	void calculatePositions(ivhd::IParticleSystem& ps) override;

protected:
	void simul_step_cuda() override;
};