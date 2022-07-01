//
// Created by Jakub Perzylo on 23/04/2022.
//

#include <vector>
#include "CasterUMAP.h"

namespace viskit::embed::cast::umap {
    CasterUMAP::CasterUMAP(const viskit::core::System &system) : Caster(system) { }

    std::vector<float> particleSystemToEmbedding(particles::ParticleSystem& ps) {
        auto& pos = ps.calculationData()->m_pos;
        auto embedding = std::vector<float>(2 * pos.size());

        for (auto i = 0; i < pos.size(); i++) {
            embedding[2 * i] = pos[i].x;
            embedding[(2 * i) + 1] = pos[i].y;
        }

        return embedding;
    }

    void CasterUMAP::initialize(particles::ParticleSystem &ps, Graph &graph) {
        n_vertices = ps.calculationData()->m_pos.size();

        // observations * target dimensions
        embedding = std::vector<float>(n_vertices * 2);

        auto& dataset = ps.originalCoordinates();

        auto rows = dataset.size();

        // set any UMAP related parameters
        umap
            .set_num_neighbors(static_cast<int>(num_neighbours))
            .set_num_epochs(static_cast<int>(total_iterations))
            .set_batch(true);

        NeighborList<float> data;
        data.resize(rows);

        for (int i = 0; i < rows; i++){
            auto neighbours = graph.getNeighbors(i).value();
            data[i].reserve(neighbours.size());
            for (auto neighbour : neighbours){
                data[i].push_back(std::pair(neighbour.j, neighbour.r));
            }
        }

        status = umap.initialize(data, 2, embedding.data());

        auto& pos = ps.calculationData()->m_pos;
        for (int i = 0; i < n_vertices; i++) {
            pos[i].x = embedding[2 * i];
            pos[i].y = embedding[(2 * i) + 1];
        }
    }
     void CasterUMAP::castParticleSystem(particles::ParticleSystem& ps, Graph& graph) {
        calculatePositions(ps);
     }

     void CasterUMAP::calculatePositions(particles::ParticleSystem& ps) {
        current_iteration += 1;
        // for every vistkit iteration run 20 iterations to reduce the cost of rewriting the embedding data
        // to the particle system
        umap.run(status.value(), 2, embedding.data(), current_iteration * 20);
        auto& pos = ps.calculationData()->m_pos;
        for (int i = 0; i < n_vertices; i++) {
            pos[i].x = embedding[2 * i];
            pos[i].y = embedding[(2 * i) + 1];
        }
    }
}
