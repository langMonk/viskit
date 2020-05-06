#pragma once

#include <cmath>
#include <functional>
#include <utility>
#include <vector>
#include <glm/glm/glm.hpp>
#include <ICaster.h>
#include <Math.h>

#include "InternalStructures.h"

namespace ivhd { namespace cuda { namespace caster {
    class CasterCuda : public ivhd::ICaster {
    public:
        explicit CasterCuda() = default;;

    public:
        void calculatePositions(ivhd::IParticleSystem &ps) override {};

        void calculateForces(ivhd::IParticleSystem &ps, ivhd::IGraph &graph) override {};

        void initialize(ivhd::IParticleSystem &ps, ivhd::IGraph &graph) override;

        void step(ivhd::IParticleSystem &ps, ivhd::IGraph &graph) override;

        void finalize() override;

        ivhd::CasterType type() override { return ivhd::CasterType::IVHD; }

        ivhd::OptimizerType optimizerType() override { return ivhd::OptimizerType::None; }

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
        float2 *d_positions{};
        ivhd::cuda::DistElem *d_distances{};
        ivhd::cuda::Sample *d_samples{};
        float *d_errors{};

        std::vector<ivhd::cuda::DistElem> distances{};

        std::vector<float2> positions;
        std::vector<glm::vec2> ivhdPositions;
        std::function<void(float)> onError;
        std::function<void(std::vector<glm::vec2> &)> onPositions;

    };
} } }