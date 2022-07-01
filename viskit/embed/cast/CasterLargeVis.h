///
/// \author tomsia
/// \date 27.05.2021
///

#pragma once

#include <viskit/embed/cast/Caster.h>
#include <viskit/particles/ParticleSystem.h>
#include <viskit/threading/ThreadPool.h>
#include <viskit/math/IvhdMath.h>

#include <gsl/gsl_rng.h>
#include <array>

namespace viskit::embed::cast
{
    class CasterLargeVis final : public Caster
    {
        // public construction and destruction methods
    public:
        explicit CasterLargeVis(const core::System& system);
        ~CasterLargeVis();

        /// <summary>
        /// Initialize LargeVis structures.
        /// </summary>
        /// <param name="ps"> Particle system initialized by CasterRandom.</param>
        /// <param name="graph"> Prebuilt kNN graph </param>
        void initialize(particles::ParticleSystem& ps, Graph& graph);

        void castParticleSystem(particles::ParticleSystem& ps, Graph& graph) override;

        void calculatePositions(particles::ParticleSystem& ps) override;

    private:
        static const gsl_rng_type * gsl_T;
        static gsl_rng * gsl_r;

        /// number of neighbours.
        int knn;

        /// number of edges in kNN graph (for every two vertices 'p' and 'q', if edge p->q is present in kNN graph,
        /// and edge q -> p is not, the latter is additionally created).
        long long n_edge;

        /// number of vertices in kNN graph.
        long long n_vertices;

        /// for edge 'i', between vertices 'p' and 'q' (p->q), edge_from[i] == p.
        std::vector<int> edge_from;

        /// for edge 'i', between vertices 'p' and 'q' (p->q), edge_to[i] == q.
        std::vector<int> edge_to;

        /// for each vertex 'p', store it`s outgoing edges in a linked list with first edge 'i'. Thus: head[p] == i.
        long long *head;

        /// for each vertex 'p', store it`s outgoing edges in a linked list. For each edge 'i' in this list, the next
        /// edge 'j' can be retrieved as: next[i] == j.
        std::vector<long long> next;

        /// for each edge 'i' between vertices 'p' and 'q' (p->q) there exist edge 'j' connecting vertices in opposite
        /// direction (q->p). Then, reverse[i] == j and reverse[j] == i. Used for finding missing edges in kNN graph.
        std::vector<long long> reverse;

        /// for each edge 'i' store it`s weight 'w' as edge_weight[i] == w.
        std::vector<float> edge_weight;

        /// size of negative samples table.
        static const int NEGSIZE = 1e8;

        /// stores IDs of negative edges with repetitions. Number of repetitions is
        /// proportional to weight of the edge.
        std::array<int, NEGSIZE> neg_table;

        /// NEG_TABLE_CACHE_SIZE times N_NEGATIVES is the size of table that stores cached values from neg_table
        int NEG_TABLE_CACHE_SIZE = 75000;

        /// for each edge 'i', it`s probability of being sampled (rather than it`s alias edge) 'pr' is prob[i] == pr.
        float* prob;

        /// each edge 'i' is assigned an alias edge 'j', so that prob[i] + prob[j] ~= 1.0. Edges IDs are
        /// sampled uniformly and after ID 'i' is chosen, the second random value 'v' from (0, 1) is selected.
        /// If v < prob[i] then edge 'i' is sampled, otherwise edge alias[i] is sampled.
        long long* alias;

        /// embedding dimensionality
        int out_dim = 2;

        /// array storing embedding. (for smoother transitions, ParticleSystem is updated after sampling positive and
        /// all negatives edges of an iteration). For each vertice 'p', it`s embedding is stored in vis[out_dims * p + 0],
        /// vis[out_dims * p + 1], ... vis[out_dims * p + (out_dims - 1)]
        float*  vis;


        // TUNABLE PARAMETERS:

        // uncomment for running interactive visualization (rather than offline viskit)
        #define INTERACTIVE

        /// number of total edges to be sampled.
        int n_samples;


        /// variable used to share total number of edges processed by all visualization threads.
        int edge_count_actual = 0;

        /// initial learning rate.
        float INITIAL_ALPHA = 1.0;

        /// for each positive sample, sample N_NEGATIVES negative edges.
        int N_NEGATIVES = 5;

#ifdef INTERACTIVE
        /// perplexity as proposed in original t-SNE.
        float PERPLEXITY = 10.0;

        /// weight mby which gradient is multiplied when sampling negative edges.
        float GAMMA = 1.0;

        /// in low dimension embedding, probability of vertices 'p' and 'q' being neighbours is based on theirs
        /// euclidean distance 'd'. Distance is being used as argument for function: prob_neigh ~ 1/(1 + A*x^2).
        float A = 100.0;

        /// gradient clipping
        float grad_clip = 1.0;
#else
        /// perplexity as proposed in original t-SNE.
        float PERPLEXITY = 50.0;

        /// weight mby which gradient is multiplied when sampling negative edges.
        float GAMMA = 7.0;

        /// in low dimension embedding, probability of vertices 'p' and 'q' being neighbours is based on theirs
        /// euclidean distance 'd'. Distance is being used as argument for function: prob_neigh ~ 1/(1 + A*x^2).
        float A = 1.0;

        /// gradient clipping
        float grad_clip = 5.0;
#endif

        /// <summary>
        /// Compute weights of edges in kNN graph based on distances in original space.
        /// </summary>
        /// <param name="ps"> Particle system initialized by CasterRandom.</param>
        /// <param name="graph"> Prebuilt kNN graph </param>
        void compute_similarities(particles::ParticleSystem& ps, Graph& graph);

        /// <summary>
        /// Worker thread of compute_similarities function.
        /// </summary>
        void compute_similarity_thread(int id);

        /// <summary>
        /// Worker thread for filling reverse table.
        /// </summary>
        void search_reverse_thread(int id);

        /// <summary>
        /// Initialize negative sampling table.
        /// </summary>
        void init_neg_table();

        /// <summary>
        /// Initialize alias table.
        /// </summary>
        void init_alias_table();

        /// <summary>
        /// Sample an edge using precomputed probabilities.
        /// </summary>
        /// <param name="rand_value1"> Uniformly distributed random value from (0, 1) indicating edge to be sampled. </param>
        /// <param name="rand_value2"> Uniformly distributed random value from (0, 1) indicating whether to use
        /// current edge or it`s alias based on edge probability. </param>
        /// <returns> ID of chosen edge. </returns>
        long long sample_an_edge(double rand_value1, double rand_value2);

        /// <summary>
        /// Worker thread computing embedding.
        /// </summary>
        void visualize_thread(particles::ParticleSystem& ps, unsigned int id);
    };
}
