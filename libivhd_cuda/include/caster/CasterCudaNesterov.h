#pragma once

#include "caster/CasterCuda.h"

namespace ivhd_cuda
{
    class CasterCudaNesterov : public CasterCuda 
    {
    public:
        CasterCudaNesterov(int n, std::function<void(float)> onErr, std::function<void(std::vector<vec2>&)> onPos)
            : CasterCuda(n, onErr, onPos) {}

    protected:
        virtual void simul_step_cuda() override;
    };
}