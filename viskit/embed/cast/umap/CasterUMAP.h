
#pragma once

#include "Umap.h"
#include <viskit/embed/cast/Caster.h>

namespace viskit::embed::cast::umap {
    class CasterUMAP final : public Caster {

    public:
        explicit CasterUMAP(const core::System& system);

        void initialize(particles::ParticleSystem& ps, Graph& graph);

        void castParticleSystem(particles::ParticleSystem& ps, Graph& graph) override;

        void calculatePositions(particles::ParticleSystem& ps) override;

        ~CasterUMAP() override = default;

        CasterUMAP& set_total_iterations(std::size_t iterations) { total_iterations = iterations; return *this; }

        CasterUMAP& set_num_neighbours(std::size_t neighbours) { num_neighbours = neighbours; return *this; }

    private:
        Umap<float> umap;
        // NOTE: total_iterations represents UMAP's number of iterations.
        // For each viskit iteration UMAP will perform 20 internal iterations
        // to lower the overhead of passing data between viskit and UMAP implementation.
        // So when calling from viskit the number of iterations should equal 500 / 20 = 25.
        std::size_t total_iterations = 500;
        std::size_t num_neighbours = 15;

        // current Umap status allowing stopping and continuing calculations
        std::optional<Umap<float>::Status> status;
        // internal embedding used by the Umap class
        std::vector<float> embedding;
        std::size_t n_vertices = 0;
        int current_iteration = 0;
    };
}
