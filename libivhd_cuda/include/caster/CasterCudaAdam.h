#pragma once

#include <utility>

#include "caster/CasterCuda.h"

namespace ivhd {
    namespace cuda {
        namespace caster {
            class CasterCudaAdam : public CasterCuda {
            public:
                explicit CasterCudaAdam() : CasterCuda() {

                }

                void initialize(ivhd::IParticleSystem &ps, ivhd::IGraph &graph) override;

                ivhd::OptimizerType optimizerType() override { return ivhd::OptimizerType::Adam; }

            protected:
                void simul_step_cuda() override;

            private:
                float4 *d_average_params{};
            };
        }
    }
}