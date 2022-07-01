///
/// \author tomsia
/// \date 27.05.2021
///

#include <viskit/embed/cast/CasterLargeVis.h>

namespace viskit::embed::cast {
CasterLargeVis::CasterLargeVis(const core::System& system)
        : Caster(system)
{
}

const gsl_rng_type *CasterLargeVis::gsl_T = nullptr;
gsl_rng *CasterLargeVis::gsl_r = nullptr;

CasterLargeVis::~CasterLargeVis()
{
    delete[] vis;
    delete[] head;
    delete[] alias;
    delete[] prob;
}

void CasterLargeVis::castParticleSystem(particles::ParticleSystem& ps, Graph& graph)
{
    calculatePositions(ps);
}

void CasterLargeVis::initialize(particles::ParticleSystem& ps, Graph& graph)
{
    n_vertices = graph.size();
    vis = new float[n_vertices * 2];

    for (int i = 0; i < ps.countParticles(); ++i) {
        auto& pos = ps.calculationData()->m_pos;
        vis[i * out_dim] = pos[i].x;
        vis[i * out_dim + 1] = pos[i].y;
    }

    compute_similarities(ps, graph);

    init_neg_table();
    init_alias_table();

    m_ext_system.logger().logInfo("init done");
}

void CasterLargeVis::compute_similarities(particles::ParticleSystem& ps, Graph& graph)
{
    long long i, x, y, p, q;
    float sum_weight = 0;
    n_edge = 0;

    head = new long long[n_vertices];

    for (i = 0; i < n_vertices; ++i)
        head[i] = -1;

    for (i = 0; i < n_vertices; ++i) {
        if (auto neighbors = graph.getNeighbors(i)) {
            for (const auto neighbor : *neighbors)
                if (neighbor.type == NeighborsType::Near) {
                    edge_from.push_back((int)i);
                    edge_to.push_back((int)neighbor.j);
                    edge_weight.push_back(ps.vectorDistance(i, neighbor.j));

                    next.push_back(head[i]);
                    reverse.push_back(-1);
                    head[i] = n_edge++;
                }
        } else {
            m_ext_system.logger().logWarning("failed to retrieve neighbours");
        }
    }

    threading::ThreadPool threadPool(math::threads<>);
    std::vector<std::future<void>> results(math::threads<>);

    for (i = 0; i < math::threads<>; i++) {
        results[i] = threadPool.enqueue([this, i]() {
            compute_similarity_thread(i);
        });
    }
    for (auto& result : results)
        result.get();

    for (i = 0; i < math::threads<>; i++) {
        results[i] = threadPool.enqueue([this, i]() {
            search_reverse_thread(i);
        });
    }
    for (auto& result : results)
        result.get();

    for (x = 0; x < n_vertices; ++x) {
        for (p = head[x]; p >= 0; p = next[p]) {
            y = edge_to[p];
            q = reverse[p];
            if (q == -1) {
                edge_from.push_back((int)y);
                edge_to.push_back((int)x);
                edge_weight.push_back(0);
                next.push_back(head[y]);
                reverse.push_back(p);
                q = reverse[p] = head[y] = n_edge++;
            }
            if (x > y) {
                sum_weight += edge_weight[p] + edge_weight[q];
                edge_weight[p] = edge_weight[q] = (edge_weight[p] + edge_weight[q]) / 2;
            }
        }
    }
}

void CasterLargeVis::compute_similarity_thread(int id)
{
    long long lo = id * n_vertices / math::threads<>;
    long long hi = (id + 1) * n_vertices / math::threads<>;
    long long x, iter, p;
    float beta, lo_beta, hi_beta, sum_weight, H, tmp;
    for (x = lo; x < hi; ++x) {
        beta = 1;
        lo_beta = hi_beta = -1;
        for (iter = 0; iter < 200; ++iter) {
            H = 0;
            sum_weight = FLT_MIN;
            for (p = head[x]; p >= 0; p = next[p]) {
                sum_weight += tmp = exp(-beta * edge_weight[p]);
                H += beta * (edge_weight[p] * tmp);
            }
            H = (H / sum_weight) + log(sum_weight);
            if (fabs(H - log(PERPLEXITY)) < 1e-5)
                break;
            if (H > log(PERPLEXITY)) {
                lo_beta = beta;
                if (hi_beta < 0)
                    beta *= 2;
                else
                    beta = (beta + hi_beta) / 2;
            } else {
                hi_beta = beta;
                if (lo_beta < 0)
                    beta /= 2;
                else
                    beta = (lo_beta + beta) / 2;
            }
            if (beta > FLT_MAX)
                beta = FLT_MAX;
        }
        for (p = head[x], sum_weight = FLT_MIN; p >= 0; p = next[p]) {
            sum_weight += edge_weight[p] = exp(-beta * edge_weight[p]);
        }
        for (p = head[x]; p >= 0; p = next[p]) {
            edge_weight[p] /= sum_weight;
        }
    }
}

void CasterLargeVis::search_reverse_thread(int id)
{
    long long lo = id * n_vertices / math::threads<>;
    long long hi = (id + 1) * n_vertices / math::threads<>;
    long long x, y, p, q;
    for (x = lo; x < hi; ++x) {
        for (p = head[x]; p >= 0; p = next[p]) {
            y = edge_to[p];
            for (q = head[y]; q >= 0; q = next[q]) {
                if (edge_to[q] == x)
                    break;
            }
            reverse[p] = q;
        }
    }
}

void CasterLargeVis::init_neg_table()
{
    long long x, p, i;
    reverse.clear();
    std::vector<long long>(reverse).swap(reverse);
    float sum_weights = 0, dd, *weights = new float[n_vertices];
    for (i = 0; i < n_vertices; ++i)
        weights[i] = 0;
    for (x = 0; x < n_vertices; ++x) {
        for (p = head[x]; p >= 0; p = next[p]) {
            weights[x] += edge_weight[p];
        }
        sum_weights += weights[x] = pow(weights[x], 0.75);
    }
    next.clear();
    std::vector<long long>(next).swap(next);
    delete[] head;
    head = nullptr;

    dd = weights[0];
    for (i = x = 0; i < NEGSIZE; ++i) {
        neg_table[i] = x;
        if (i / (float)NEGSIZE > dd / sum_weights && x < n_vertices - 1) {
            dd += weights[++x];
        }
    }
    delete[] weights;
}

void CasterLargeVis::init_alias_table()
{
    alias = new long long[n_edge];
    prob = new float[n_edge];

    auto* norm_prob = new float[n_edge];
    auto* large_block = new long long[n_edge];
    auto* small_block = new long long[n_edge];

    float sum = 0;
    long long cur_small_block, cur_large_block;
    long long num_small_block = 0, num_large_block = 0;

    for (long long k = 0; k < n_edge; ++k)
        sum += edge_weight[k];
    for (long long k = 0; k < n_edge; ++k)
        norm_prob[k] = edge_weight[k] * n_edge / sum;

    for (long long k = n_edge - 1; k >= 0; --k) {
        if (norm_prob[k] < 1)
            small_block[num_small_block++] = k;
        else
            large_block[num_large_block++] = k;
    }

    while (num_small_block && num_large_block) {
        cur_small_block = small_block[--num_small_block];
        cur_large_block = large_block[--num_large_block];
        prob[cur_small_block] = norm_prob[cur_small_block];
        alias[cur_small_block] = cur_large_block;
        norm_prob[cur_large_block] = norm_prob[cur_large_block] + norm_prob[cur_small_block] - 1;
        if (norm_prob[cur_large_block] < 1)
            small_block[num_small_block++] = cur_large_block;
        else
            large_block[num_large_block++] = cur_large_block;
    }

    while (num_large_block)
        prob[large_block[--num_large_block]] = 1;
    while (num_small_block)
        prob[small_block[--num_small_block]] = 1;

    delete[] norm_prob;
    delete[] small_block;
    delete[] large_block;
}

long long CasterLargeVis::sample_an_edge(double rand_value1, double rand_value2)
{
    long long k = (long long)((n_edge - 0.1) * rand_value1);
    return rand_value2 <= prob[k] ? k : alias[k];
}

void CasterLargeVis::visualize_thread(particles::ParticleSystem& ps, unsigned int id)
{
    auto& pos = ps.calculationData()->m_pos;

    long long x, y, p, lx, ly, i, j;
    float f, g, gg, cur_alpha = INITIAL_ALPHA;
    std::vector<float> cur(out_dim);
    std::vector<float> err(out_dim);

    std::vector<long long> ys(NEG_TABLE_CACHE_SIZE * N_NEGATIVES);
    std::vector<long long> rs(NEG_TABLE_CACHE_SIZE * N_NEGATIVES);
    int ys_counter = 0;

    for (long long counter = 0; counter < n_samples/math::threads<> + 2; counter++) {
        if (counter % 300000 == 0) {
            edge_count_actual += 300000;
            cur_alpha = INITIAL_ALPHA * (1 - edge_count_actual / (n_samples + 1.0));
            if (cur_alpha < INITIAL_ALPHA * 0.0001)
                cur_alpha = INITIAL_ALPHA * 0.0001;
            std::cout << "Fitting model\tAlpha: " << cur_alpha << " Progress: "
                      << (float) edge_count_actual / (float) (n_samples + 1) * 100 << std::endl;
        }

        if(counter % NEG_TABLE_CACHE_SIZE == 0) {
            ys_counter = 0;

            for (int idx = 0; idx < NEG_TABLE_CACHE_SIZE * N_NEGATIVES; ++idx) {
                double r = gsl_rng_uniform(gsl_r);
                rs[idx] = floor(r * (NEGSIZE - 0.1));
            }
            for (int idx = 0; idx < NEG_TABLE_CACHE_SIZE * N_NEGATIVES; ++idx) {
                ys[idx] = neg_table[rs[idx]];
            }
        }
        p = sample_an_edge(gsl_rng_uniform(gsl_r), gsl_rng_uniform(gsl_r));
        x = edge_from[p];
        y = edge_to[p];
        lx = x * out_dim;
        for (i = 0; i < out_dim; ++i) {
            cur[i] = vis[lx + i];
            err[i] = 0;
        }

        for (i = 0; i < N_NEGATIVES + 1; ++i) {
            if (i > 0) {
                y = ys[ys_counter];
                ys_counter++;

                if (y == edge_to[p])
                    continue;
            }

            ly = y * out_dim;
            for (j = 0, f = 0; j < out_dim; ++j)
                f += A * (cur[j] - vis[ly + j]) * (cur[j] - vis[ly + j]);
            if (i == 0)
                g = -2 / (1 + f);
            else
                g = 2 * GAMMA / (1 + f) / (0.1 + f);
            for (j = 0; j < out_dim; ++j) {
                gg = g * (cur[j] - vis[ly + j]);
                if (gg > grad_clip)
                    gg = grad_clip;
                else if (gg < -grad_clip)
                    gg = -grad_clip;
                err[j] += gg * cur_alpha;

                gg = g * (vis[ly + j] - cur[j]);
                if (gg > grad_clip)
                    gg = grad_clip;
                else if (gg < -grad_clip)
                    gg = -grad_clip;
                vis[ly + j] += gg * cur_alpha;
            }
        }

        for (j = 0; j < out_dim; ++j)
            vis[lx + j] += err[j];

        glm::vec4 &posX = pos[x];
        glm::vec4 &posY = pos[y];

        posX.x = vis[lx];
        posX.y = vis[lx + 1];

        posY.x = vis[ly];
        posY.y = vis[ly + 1];
    }
}

void CasterLargeVis::calculatePositions(particles::ParticleSystem& ps)
{
    gsl_rng_env_setup();
    gsl_T = gsl_rng_rand48;
    gsl_r = gsl_rng_alloc(gsl_T);
    gsl_rng_set(gsl_r, 314159265);

    if (n_vertices < 10000)
        n_samples = 1000;
    else if (n_vertices < 1000000)
        n_samples = (n_vertices - 10000) * 9000 / (1000000 - 10000) + 1000;
    else n_samples = n_vertices / 100;
    n_samples *= 1000000;

    threading::ThreadPool threadPool(math::threads<>);
    std::vector<std::future<void>> results(math::threads<>);
    for (int i = 0; i < math::threads<>; i++)
    {
        results[i] = threadPool.enqueue(
                [this, &ps, i](){visualize_thread(ps, i);}
                );
    }
    for (auto& result: results)
        result.get();
}

}