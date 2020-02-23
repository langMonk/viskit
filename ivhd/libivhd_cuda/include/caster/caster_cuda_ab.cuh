#pragma once

#include "caster/caster_cuda.cuh"

class CasterCudaAB : public CasterCuda
{
public:
	CasterCudaAB(int n, function<void(float)> onErr, function<void(vector<float2>&)> onPos)
		: CasterCuda(n, onErr, onPos) {}

protected:
	void simul_step_cuda() override;
};