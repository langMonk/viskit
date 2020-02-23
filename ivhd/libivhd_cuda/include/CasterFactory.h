#pragma once

#include <memory>
#include <vector>
#include <ivhd\Structures.h>
#include "caster/caster_cuda_ab.cuh"

std::shared_ptr<Caster> getCaster(int n, std::function<void(float)> onError, std::function<void(std::vector<float2>&)> onPos, ivhd::CasterType type);

