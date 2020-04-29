#pragma once

#include "caster/CasterCuda.h"

namespace ivhd_cuda
{
    class CasterCudaAB : public CasterCuda 
    {
    public:
        CasterCudaAB(int n, std::function<void(float)> onErr, std::function<void(std::vector<vec2>&)> onPos)
        : CasterCuda(n, onErr, onPos) {}

        void setFinalizing(bool val) { finalizing = val; }

    protected:
        virtual void simul_step_cuda() override;
        bool finalizing = false;
    };
}