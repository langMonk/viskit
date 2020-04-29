#pragma once

#include <memory>
#include <functional>

#include "ivhd_cuda/ICasterCuda.h"
#include "ivhd_cuda/ICasterFactory.h"
#include "caster/CasterCudaAdam.h"
#include "caster/CasterCudaAdadelta.h"

#include "ivhd/Structures.h"

namespace ivhd_cuda
{
    class GpuFactory : public IGpuFactory
    {
    public:
        static std::unique_ptr<ICasterCuda> createCaster(ivhd::OptimizerType optimizer, 
                                int n, std::function<void(float)> onErr, 
                                std::function<void(std::vector<vec2>&)> onPos,
                                ivhd::OptimizerType optimizer) override

        {
            if(optimizer == ivhd::OptimizerType::Adam)
            {
                return std::make_unique<CasterCudaAdam>(n, onErr, onPos);
            }
            else if(optimizer == ivhd::OptimizerType::Adadelta)
            {
                return std::make_unique<CasterCudaAdadelta>(n, onErr, onPos);
            }
            else if(optimizer == ivhd::OptimizerType::Nesterov)
            {
                return std::make_unique<CasterCudaNesterov>(n, onErr, onPos);
            }
            else if(optimizer == ivhd::OptimizerType::Momentum)
            {
                return std::make_unique<CasterCudaAB>(n, onErr, onPos);
            }
        }
    };
}