#pragma once

#include <cmath>
#include <functional>
#include <vector>

#include <ivhd/ICaster.h>
#include <ivhd/Math.h>

#include "InternalStructures.h"

using namespace ivhd;

namespace ivhd_cuda
{
    class CasterCuda : public ivhd::ICaster
    {
    public:
        CasterCuda(int n, std::function<void(float)> onErrorCallback,
                std::function<void(std::vector<vec2>&)> onPositionsCallback)
            : positions(n)
            , ivhdPositions(n)
            {
                onError = onErrorCallback;
                onPositions = onPositionsCallback;
            };

    public:
        void initialize(IParticleSystem& ps, IGraph& graph) override;
        void step(IParticleSystem& ps, IGraph& graph) override;
        void finish() override;

        virtual void simul_step_cuda() = 0;

        bool allocateInitializeDeviceMemory();
        bool copyResultsToHost();

    protected:
        void initializeHelperVectors();
        virtual float getError();
        void copyPositions();

        int itToPosReady = -1;
        unsigned it = 0;
        
        // internal CUDA variables
        float2* d_positions;
        ivhd_cuda::DistElem* d_distances;
        ivhd_cuda::Sample* d_samples;
        float* d_errors;

        std::vector<ivhd_cuda::DistElem> distances;

        std::vector<float2> positions;
        std::vector<vec2> ivhdPositions;
        std::function<void(float)> onError;
        std::function<void(std::vector<ivhd::vec2>&)> onPositions;
    };
}