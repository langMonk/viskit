#pragma once

#include <iostream>
#include <memory>
#include <vector>
#include <ivhd/Structures.h>
#include "caster/caster_cuda_ab.cuh"

inline std::shared_ptr<Caster> getCaster(int n, std::function<void(float)> onError, std::function<void(std::vector<float2>&)> onPos, ivhd::CasterType type)
{
	if (type == ivhd::CasterType::IVHD) 
	{
		return std::make_shared<CasterCudaAB>(n, onError, onPos);
	}
	std::cerr << "Invalid algorithm_name. Expected one of: 'ab', 'cuda_ab', ";
	std::cerr << "'nesterov', 'cuda_nesterov', 'cuda_adadelta', 'cuda_adam'\n";
	exit(-1);
}

