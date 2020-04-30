#pragma once

#include <utility>

#include "caster/CasterCuda.h"

namespace ivhd {
    namespace cuda {
        namespace caster {
            class CasterCudaNesterov : public CasterCuda {
            public:
                explicit CasterCudaNesterov() : CasterCuda() {

                }

                ivhd::OptimizerType optimizerType() override { return ivhd::OptimizerType::Nesterov; }

            protected:
                void simul_step_cuda() override;
            };
        }
    }
}