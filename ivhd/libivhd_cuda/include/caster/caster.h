#pragma once

#include <functional>
#include <vector>
#include <vector_types.h>
#include <ivhd/ICaster.h>
#include <device_launch_parameters.h>
#include "distance.h"
#include "distance_container.h"

using namespace std;

class Caster : public IDistanceContainer, public ivhd::ICaster
{
public:
	Caster(int n, function<void(float)> onErrorCallback, function<void(vector<float2>&)> onPositionsCallback)
		: positions(n)
	{
		onError = onErrorCallback;
		onPositions = onPositionsCallback;
	};

	virtual void simul_step() = 0;
	virtual void prepare(vector<int>& labels) {};
	virtual void finish() {};

	vector<float2> positions;
	function<void(float)> onError;
	function<void(vector<float2>&)> onPositions;
};