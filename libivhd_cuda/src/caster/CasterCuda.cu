#include <cuda.h>
#include <algorithm>
#include <cassert>
#include <cstring>
#include <iostream>
#include <unordered_map>
#include <thrust/execution_policy.h>
#include <thrust/device_ptr.h>
#include <thrust/reduce.h>
#include <device_launch_parameters.h>

#include "caster/Constants.h"
#include "caster/CasterCuda.h"

#include <IParticleSystem.h>
#include <IGraph.h>

using namespace std;
using namespace ivhd::cuda;

// initialize pos in Samples
// initialize num_components
__global__ void initializeSamples(int n, Sample *samples, float2 *positions,
    const short *sampleFreq)
{
    unsigned i = blockIdx.x * blockDim.x + threadIdx.x;
    if (i < n) 
    {
        Sample sample{};
        sample.pos = positions[i];
        sample.v = {0, 0};
        sample.num_components = sampleFreq[i];
        // FIXME - malloc can return NULL
        sample.components =
            (float2 *)malloc(sample.num_components * sizeof(float2));
        samples[i] = sample;
    }
}

__global__ void initializeDistances(int nDst, DistElem *distances,
    short2 *dstIndexes, Sample *samples) 
{
    unsigned i = blockIdx.x * blockDim.x + threadIdx.x;
    if (i < nDst) 
    {
        DistElem dst = distances[i];
        dst.comp1 = &samples[dst.i].components[dstIndexes[i].x];
        dst.comp2 = &samples[dst.j].components[dstIndexes[i].y];
        distances[i] = dst;
    }
}

__global__ void copyDevicePos(int N, Sample *samples, float2 *positions) 
{
    unsigned i = blockIdx.x * blockDim.x + threadIdx.x;
    if (i < N) 
    {
        positions[i] = samples[i].pos;
    }
}

__global__ void copyPosRelease(int N, Sample *samples, float2 *positions) 
{
    unsigned i = blockIdx.x * blockDim.x + threadIdx.x;
    if (i < N) 
    {
        positions[i] = samples[i].pos;
        free(samples[i].components);
    }
}

namespace ivhd { namespace cuda { namespace caster {
    void CasterCuda::initializeHelperVectors() {
        /*
        * calculate number of distances for each sample and index of each distance
        * for a given sample
        */
        auto *sampleFreq = new short[positions.size()];
        for (unsigned i = 0; i < positions.size(); i++) {
            sampleFreq[i] = 0;
        }

        auto *dstIndexes = new short2[distances.size()];

        for (unsigned i = 0; i < distances.size(); i++) {
            dstIndexes[i] = {sampleFreq[distances[i].i]++,
                             sampleFreq[distances[i].j]++};
        }

        // initialize samples
        short *d_sample_freq;
        cuCall(cudaMalloc(&d_sample_freq, positions.size() * sizeof(short)));
        cuCall(cudaMemcpy(d_sample_freq, sampleFreq, sizeof(short) * positions.size(),
                          cudaMemcpyHostToDevice));

        delete[] sampleFreq;

        initializeSamples <<< positions.size() / 256 + 1, 256 >>> (
                positions.size(), d_samples, d_positions, d_sample_freq);
        cuCall(cudaFree(d_sample_freq));

        // initialize comps in Distances in device memory
        short2 *d_dst_indexes;
        cuCall(cudaMalloc(&d_dst_indexes, distances.size() * sizeof(short2)));
        cuCall(cudaMemcpy(d_dst_indexes, dstIndexes,
                          sizeof(short2) * distances.size(), cudaMemcpyHostToDevice));

        initializeDistances <<< distances.size() / 256 + 1, 256 >>> (
                distances.size(), d_distances, d_dst_indexes, d_samples);
        cuCall(cudaFree(d_dst_indexes));
        delete[] dstIndexes;
    }

    bool CasterCuda::allocateInitializeDeviceMemory() {
        cuCall(cudaMalloc(&d_positions, positions.size() * sizeof(float2)));
        cuCall(cudaMalloc(&d_samples, positions.size() * sizeof(Sample)));
        cuCall(cudaMalloc(&d_distances, distances.size() * sizeof(DistElem)));
        cuCall(cudaMalloc(&d_errors, distances.size() * sizeof(float)));

        cuCall(cudaMemcpy(d_positions, &positions[0],
                          sizeof(float2) * positions.size(), cudaMemcpyHostToDevice));
        cuCall(cudaMemset(d_samples, 0, positions.size() * sizeof(Sample)));
        cuCall(cudaMemset(d_errors, 0, distances.size() * sizeof(float)));
        cuCall(cudaMemcpy(d_distances, &distances[0],
                          sizeof(DistElem) * distances.size(),
                          cudaMemcpyHostToDevice));

        return true;
    }

    void CasterCuda::initialize(ivhd::IParticleSystem &ps, ivhd::IGraph &graph) {
        auto internalPositions = ps.positions();
        auto n = ps.countParticles();

        positions.resize(n);
        internalPositions.resize(n);

        onError = [&](float err) -> void {
        };

        onPositions = [&](vector<glm::vec2> &pos) -> void {
            for (unsigned i = 0; i < pos.size(); i++) {
                internalPositions[i].x = pos[i].x;
                internalPositions[i].y = pos[i].y;
            }
        };

        // initialize positions
        for (auto i = 0; i < internalPositions.size(); i++) {
            positions[i].x = internalPositions[i].x;
            positions[i].y = internalPositions[i].y;
        }

        // initialize distances
        for (auto index = 0; index < graph.size(); index++) {
            auto neighbors = graph.getNeighbors(index);

            for (auto neighbor : neighbors) {
                distances.emplace_back(neighbor.i, neighbor.j, neighbor.type, neighbor.r);
            }
        }

        allocateInitializeDeviceMemory();
    }

    void CasterCuda::finalize() {
        copyResultsToHost();
    }

    void CasterCuda::copyPositions() {
        copyDevicePos <<< positions.size() / 256 + 1, 256 >>> (positions.size(),
                d_samples, d_positions);
        cuCall(cudaMemcpy(&positions[0], d_positions,
                          sizeof(float2) * positions.size(), cudaMemcpyDeviceToHost));

        for (auto i = 0; i < positions.size(); i++) {
            ivhdPositions[i].x = positions[i].x;
            ivhdPositions[i].y = positions[i].y;
        }
    }

    bool CasterCuda::copyResultsToHost() {
        copyPosRelease <<< positions.size() / 256 + 1, 256 >>> (positions.size(),
                d_samples, d_positions);
        cuCall(cudaMemcpy(&positions[0], d_positions,
                          sizeof(float2) * positions.size(), cudaMemcpyDeviceToHost));
        cuCall(cudaFree(d_positions));
        cuCall(cudaFree(d_distances));
        cuCall(cudaFree(d_samples));

        return true;
    }

    __global__ void calculateErrors(int dstNum, DistElem *distances, Sample *samples, float *errors) {
        for (unsigned i = blockIdx.x * blockDim.x + threadIdx.x; i < dstNum;
             i += blockDim.x * gridDim.x) {
            DistElem dist = distances[i];
            float d = dist.r;
            float2 iPos = samples[dist.i].pos;
            float2 jPos = samples[dist.j].pos;
            float2 ij = {iPos.x - jPos.x, jPos.y - jPos.y};
            errors[i] = fabs(d - sqrtf(ij.x * ij.x + ij.y * ij.y));
        }
    }

    float CasterCuda::getError() {
        calculateErrors <<< 256, 256 >>> (distances.size(), d_distances,
                d_samples, d_errors);

        thrust::device_ptr<float> err_ptr = thrust::device_pointer_cast(d_errors);
        return thrust::reduce(err_ptr, err_ptr + distances.size(), 0.0, thrust::plus<float>());
    }

    void CasterCuda::step(ivhd::IParticleSystem &ps, ivhd::IGraph &graph) {
        if (!it++) {
            initializeHelperVectors();
        }

        simul_step_cuda();

        if (it % 100 == 0) {
            onError(getError());
        }

        if ((itToPosReady--) == 0) {

            onPositions(ivhdPositions);
        }

        if (it % 2000 == 0) {
            copyPositions();
            itToPosReady = 5;
            cudaDeviceSynchronize();
        }
    }
} } }