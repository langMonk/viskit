#pragma once

#include <memory>
#include <functional>
#include <ivhd/Math.h>
#include <ivhd/Structures.h>
#include "ICasterCuda.h"

namespace ivhd_cuda
{
    class IGpuFactory
    {
    public:
        static std::unique_ptr<ICasterCuda> createCaster(int n, std::function<void(float)> onErr, 
                                                std::function<void(std::vector<ivhd::vec2>&)> onPos,
                                                ivhd::OptimizerType optimizer);

    };
}