#include <iostream>

#include "CasterFactory.h"

constexpr auto HEAP_LIMIT = 100000000;

std::shared_ptr<Caster> getCaster(int n, std::function<void(float)> onError, std::function<void(vector<float2>&)> onPos, ivhd::CasterType type)
{
	if (type == ivhd::CasterType::IVHD) 
	{
		return std::make_shared<CasterCudaAB>(n, onError, onPos);
	}
	cerr << "Invalid algorithm_name. Expected one of: 'ab', 'cuda_ab', ";
	cerr << "'nesterov', 'cuda_nesterov', 'cuda_adadelta', 'cuda_adam'\n";
	exit(-1);
}
