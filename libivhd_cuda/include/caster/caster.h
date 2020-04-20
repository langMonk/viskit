#pragma once

#include <functional>
#include <vector>
#include <vector_types.h>
#include <ivhd/ICaster.h>
#include <device_launch_parameters.h>
#include "distance.h"
#include "distance_container.h"

class Caster : public IDistanceContainer, public ivhd::ICaster
{
public:
	Caster(int n, std::function<void(float)> onErrorCallback, std::function<void(std::vector<float2>&)> onPositionsCallback)
		: positions(n)
	{
		onError = onErrorCallback;
		onPositions = onPositionsCallback;
	};
	
	virtual void prepare(std::vector<int>& labels) {};
	virtual void prepareFromIvhdResources(ivhd::IParticleSystem& ps, ivhd::IGraph& graph) {};
	virtual void finish() {};

	std::vector<float2> positions;
	std::function<void(float)> onError;
	std::function<void(std::vector<float2>&)> onPositions;
};