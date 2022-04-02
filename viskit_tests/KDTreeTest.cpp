///
/// \author Bartosz Minch <minch@agh.edu.pl>
/// \date 13.07.2019
///

#include <gtest/gtest.h>
#include <mutex>
#include <thread>

#include <viskit/graph/generate/KDTree.h>
#include <viskit/viskit/Structures.h>

#include <viskit_tests/ViskitTest.h>
#include <viskit_tests/TestUtils.h>
#include <viskit/utils/Math.h>

using namespace viskit;
using Logs = std::pair<LogLevel, std::string>;

static std::mutex mutex;
static const int kNumThreads = 8;
bool setDistancesToOne{ true };

bool alreadyNeighbors(size_t index1, size_t index2, Graph& graph)
{
    if (const auto neighbors = graph.getNeighbors(index1))
    {
        for (const auto neighbor : *neighbors)
        {
            if (neighbor.j == index2)
            {
                return true;
            }
        }
    }
    return false;
}

static void kNNQueryThread(const size_t start, const size_t end, const generate::KDTree& kd, size_t k, size_t k_r, particles::ParticleSystem& ps, Graph& graph)
{
    for (size_t i = start; i < end; i++)
    {
        const auto& p = ps.originalCoordinates()[i];
        std::vector<std::pair<float, DataPoint>> pred = kd.kNN(p.first, k);
        {
            std::scoped_lock lock(mutex);

            for (auto& elem : pred)
            {
                if (setDistancesToOne)
                {
                    graph.addNeighbors(viskit::Neighbors(i,elem.second.getId(), 1.0f, NeighborsType::Near));
                }
                else
                {
                    graph.addNeighbors(viskit::Neighbors(i, elem.second.getId(), elem.first, NeighborsType::Near));
                }
            }
        }
    }

    for (size_t i = start; i < end; i++)
    {
        for (auto random = 0; random < k_r; random++)
        {
            while (true)
            {
                const auto j = math::randInt(0, ps.countAwakeParticles());
                if (j != i)
                {
                    if (!alreadyNeighbors(i, j, graph))
                    {
                        auto distance = 1.0f;
                        if (!setDistancesToOne)
                        {
                            distance = ps.vectorDistance(i, j);
                        }

                        graph.addNeighbors(Neighbors{ i, j, distance, NeighborsType::Random });
                        break;
                    }
                }
            }
        }
    }
}


TEST(KDTreeTest, Generation)
{
    std::vector<Logs> logs;
    auto logsCount = 0;
    auto handler = [&](viskit::LogLevel level, const std::string &message)
            {
        logs.emplace_back(level, message);
        logsCount++;
            };

    std::shared_ptr<core::Core> core = std::make_shared<core::Core>(handler);
    std::shared_ptr<particles::ParticleSystem> particleSystem = std::make_shared<particles::ParticleSystem>(core->system());
    std::shared_ptr<parse::ParserCSV> parser = std::make_shared<parse::ParserCSV>(core->system());
    std::shared_ptr<Graph> graph = std::make_shared<Graph>(core->system());

    auto csvFile = resourcesDirectory().string() + "/mnist_7k_pca30.csv";

    parser->loadFile(csvFile, "", *particleSystem);
    graph->initialize(particleSystem->countParticles());

    // Part responsible for creating a tree
    auto data = particleSystem->originalCoordinates();

    generate::KDTree kd(data, 30);

    // Evaluate performance on test set
    size_t k = 3; // Number of nearest neighbors
    size_t k_r = 1; // Number of nearest neighbors
    size_t queriesPerThread = particleSystem->countParticles() / kNumThreads;
    std::vector<std::thread> threads;

    for (auto i = 0; i < kNumThreads; i++)
    {
        size_t start = i * queriesPerThread;
        size_t end = (i == kNumThreads - 1) ? particleSystem->countParticles() : start + queriesPerThread;
        threads.emplace_back(kNNQueryThread, start, end, std::ref(kd), k, k_r, std::ref(*particleSystem), std::ref(*graph));
    }

    for (auto& t : threads)
    {
        t.join();
    }

    graph->sort();

    dump(*graph, "./", "test_kd");
}
