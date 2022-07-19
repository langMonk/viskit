#pragma once

#include <viskit/embed/cast/Caster.h>
#include <viskit/particles/ParticleSystem.h>

using Engine = std::mt19937;
using Dist = std::uniform_real_distribution<>;

namespace viskit::embed::cast {
class TSNEParams {
public:
    TSNEParams(
        int n,
        int inputDims,
        int outputDims,
        double perplexity,
        double theta,
        int maxIter,
        int neighbor_count,
        bool use_graph,
        int rand_seed,
        bool skip_random_init,
        int stop_lying_iter,
        int mom_switch_iter);

    int N;
    int input_dims;
    int output_dims;
    double perplexity;
    double theta;
    int max_iter;
    int neighbor_count;
    bool use_nn_graph;
    int rand_seed;
    bool skip_random_init;
    int stop_lying_iter;
    int mom_switch_iter;

    [[nodiscard]] bool is_exact() const;
};
class TSNEState {
public:
    TSNEState(clock_t start,
        double momentum,
        double finalMomentum,
        double eta,
        std::vector<double> dY,
        std::vector<double> uY,
        std::vector<double> gains,
        std::vector<double> P,
        std::vector<unsigned int> row_P,
        std::vector<unsigned int> col_P,
        std::vector<double> val_P,
        std::vector<double> Y,
        int iter);

    clock_t start;
    double momentum;
    double final_momentum;
    double eta;
    std::vector<double> dY;
    std::vector<double> uY;
    std::vector<double> gains;
    std::vector<double> P;
    std::vector<unsigned int> row_P;
    std::vector<unsigned int> col_P;
    std::vector<double> val_P;
    std::vector<double> Y;
    int iter;
};

class CasterTSNE final : public Caster {
public:
    explicit CasterTSNE(const core::System& system);

public:
    void initialize(particles::ParticleSystem& ps, Graph& graph);

    void calculatePositions(particles::ParticleSystem& ps) override;

    void castParticleSystem(particles::ParticleSystem& ps, Graph& graph) override;

private:
    std::unique_ptr<TSNEState> state = nullptr;
    std::unique_ptr<TSNEParams> params = nullptr;
};

}