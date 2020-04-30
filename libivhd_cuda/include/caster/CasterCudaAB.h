#pragma once

#include <utility>

#include "caster/CasterCuda.h"

namespace ivhd {
    namespace cuda {
        namespace caster {
            class CasterCudaAB : public CasterCuda {
            public:
                explicit CasterCudaAB() : CasterCuda() {

                }

                void setFinalizing(bool val) { finalizing = val; }

                ivhd::OptimizerType optimizerType() override { return ivhd::OptimizerType::Momentum; }

            protected:
                void simul_step_cuda() override;

                bool finalizing = false;
            };
        }
    }
}
