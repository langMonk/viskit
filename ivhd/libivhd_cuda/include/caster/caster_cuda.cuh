#pragma once

#include <vector>
#include "caster/caster.h"

struct Sample
{
	float2 pos;
	float2 v;
	float2* components;
	short num_components;
};

class CasterCuda : public Caster
{
public:
	CasterCuda(int n, std::function<void(float)> onErr, std::function<void(std::vector<float2>&)> onPos)
		: Caster(n, onErr, onPos) {}

	float2* d_positions;
	DistElem* d_distances;
	Sample* d_samples;
	float* d_errors;

	void loadDistances(ivhd::IGraph& graph);
	void loadPositions(ivhd::IParticleSystem& ps);

	void finish() override;
	void step(ivhd::IParticleSystem& ps, ivhd::IGraph& graph) override;
	void prepareFromIvhdResources(ivhd::IParticleSystem& ps, ivhd::IGraph& graph) override;

	bool allocateInitializeDeviceMemory();
	bool copyResultsToHost();

	ivhd::CasterType type() override { return ivhd::CasterType::CUDA; }

protected:
	void initializeHelperVectors();
	virtual void simul_step_cuda(ivhd::IParticleSystem& ps, ivhd::IGraph& graph) = 0;
	virtual float getError();
	void copyPositions();
	int itToPosReady = -1;
	unsigned it = 0;
};