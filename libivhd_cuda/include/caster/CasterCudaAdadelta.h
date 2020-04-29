#pragma once

#include "caster/CasterCuda.h"

namespace ivhd_cuda
{
    class CasterCudaAdadelta : public CasterCuda 
    {
    public:
        CasterCudaAdadelta(int n, std::function<void(float)> onErr, std::function<void(std::vector<vec2>&)> onPos)
            : CasterCuda(n, onErr, onPos) {}

        virtual void initialize(IParticleSystem& ps, IGraph& graph) override;

    protected:
        virtual void simul_step_cuda() override;

    private:
        float4 *d_average_params;
    };
}