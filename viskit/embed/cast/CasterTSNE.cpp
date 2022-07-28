#include "viskit/embed/cast/tsne/tsne.h"
#include <viskit/embed/cast/CasterTSNE.h>

#include <utility>

namespace viskit::embed::cast {
CasterTSNE::CasterTSNE(const core::System& system)
    : Caster(system)
{
}

std::unique_ptr<TSNEParams> prepare_params(particles::ParticleSystem& ps, Graph& graph);
void write_data(particles::ParticleSystem& ps, const double* data, int N, int no_dims);
std::vector<double> prepare_data(particles::ParticleSystem& ps, const TSNEParams& tsne_params);

void CasterTSNE::castParticleSystem(particles::ParticleSystem& ps, Graph& graph)
{
    calculatePositions(ps);
}

void CasterTSNE::initialize(particles::ParticleSystem& ps, Graph& graph)
{
    params = prepare_params(ps, graph);
    auto data = prepare_data(ps, *params);

    state = tsne::initialize(*params, data, graph, m_ext_system);
}

void CasterTSNE::calculatePositions(particles::ParticleSystem& ps)
{
    if (state == nullptr) {
        return;
    }

    tsne::loop(*params, *state, m_ext_system);

    if (state->iter >= params->max_iter) {
        tsne::finalize(*state);

        write_data(ps, state->Y.data(), params->N, params->output_dims);
        state.reset();
    }
}

std::unique_ptr<TSNEParams> prepare_params(particles::ParticleSystem& ps, Graph& graph)
{
    int N = ps.datasetInfo().count;
    int inputDims = ps.datasetInfo().dimensionality - 1;
    int outputDims = 2;
    double perplexity = 50;
    double theta = 0.5;
    int max_iter = 500;
    int neighbor_count = (int)graph.neighborsCounter.nearestNeighbors;
    bool use_graph = true;
    int rand_seed = 1;
    bool skip_random_init = false;
    int stop_lying_iter = 250;
    int mom_switch_iter = 250;

    return std::make_unique<TSNEParams>(N, inputDims, outputDims, perplexity, theta, max_iter, neighbor_count, use_graph, rand_seed, skip_random_init, stop_lying_iter, mom_switch_iter);
}

std::vector<double> prepare_data(particles::ParticleSystem& ps, const TSNEParams& tsne_params)
{
    int N = tsne_params.N;
    int inputDims = tsne_params.input_dims;
    std::vector<double> data(inputDims * N);

    auto& positions = ps.calculationData()->m_pos;
    for (int i = 0; i < N; i++) {
        auto rowVector = ps.originalCoordinates()[i].first;
        for (int j = 0; j < inputDims; j++) {
            data[i * inputDims + j] = (double)rowVector[j];
        }
    }

    return data;
}

void write_data(particles::ParticleSystem& ps, const double* data, int N, int no_dims)
{
    auto& positions = ps.calculationData()->m_pos;
    for (int i = 0; i < N; i++) {
        positions[i].x = (float)data[no_dims * i];
        positions[i].y = (float)data[no_dims * i + 1];
    }
}

TSNEParams::TSNEParams(
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
    int mom_switch_iter)
    : N(n)
    , input_dims(inputDims)
    , output_dims(outputDims)
    , perplexity(perplexity)
    , theta(theta)
    , max_iter(maxIter)
    , neighbor_count(neighbor_count)
    , use_nn_graph(use_graph)
    , rand_seed(rand_seed)
    , skip_random_init(skip_random_init)
    , stop_lying_iter(stop_lying_iter)
    , mom_switch_iter(mom_switch_iter)
{
}

bool TSNEParams::is_exact() const
{
    return (theta == .0);
}

TSNEState::TSNEState(
    clock_t start,
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
    int iter)
    : start(start)
    , momentum(momentum)
    , final_momentum(finalMomentum)
    , eta(eta)
    , dY(std::move(dY))
    , uY(std::move(uY))
    , gains(std::move(gains))
    , P(std::move(P))
    , row_P(std::move(row_P))
    , col_P(std::move(col_P))
    , val_P(std::move(val_P))
    , Y(std::move(Y))
    , iter(iter)
{
}
}