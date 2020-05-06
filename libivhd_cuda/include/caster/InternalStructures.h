#pragma once

#include <cuda_runtime.h>
#include <Structures.h>

namespace ivhd { namespace cuda {
    struct Sample {
        float2 pos;
        float2 v;
        float2 *components;
        short num_components;
    };

    class DistElem {
    public:
        long i, j;
        float r;
        float2 *comp1{};
        float2 *comp2{};
        ivhd::NeighborsType type;

        DistElem(long pi, long pj) : i(pi), j(pj), r(0), type(ivhd::NeighborsType::Near) {};

        DistElem(long pi, long pj, ivhd::NeighborsType type, float r)
                : i(pi), j(pj), r(r), type(type) {};
    };
} }