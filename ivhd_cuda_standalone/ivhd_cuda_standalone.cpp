#include <cuda.h>
#include <chrono>
#include <fstream>
#include <iostream>
#include <vector>
#include <ivhd/InteractiveVisualizationBuilder.h>
#include <ivhd/IParser.h>
#include <ivhd/ICaster.h>
#include <ivhd/IGraph.h>
#include <ivhd/IResourceFactory.h>
#include <ivhd/IParticleSystem.h>
#include <caster/caster_cuda_ab.cuh>

using namespace std;
using namespace std::chrono;

#define HEAP_LIMIT 100000000
string dataset_file;
string knn_file;
string experiment_name;
string algorithm_name;
unsigned iterations;
unsigned seed;
unsigned random_neighbours;

void parseArg(int argc, char* argv[]) {
  if (argc != 8) {
    cerr << "Expected 7 arguments:\n";
    cerr << "./ivhd_cuda dataset_file knn_file iterations random_neighbours experiment_name "
            "algorithm_name seed\n";
    exit(-1);
  }

  dataset_file = argv[1];
  knn_file = argv[2];
  iterations = stoi(argv[3]);
  random_neighbours = stoi(argv[4]);
  experiment_name = argv[5];
  algorithm_name = argv[6];
  seed = stoi(argv[7]);
}

Caster* getCaster(int n, function<void(float)> onError,
                  function<void(vector<float2>&)> onPos) {
  if (algorithm_name == "cuda_ab") {
    return new CasterCudaAB(n, onError, onPos); 
  } else {
    cerr << "Invalid algorithm_name. Expected one of: 'ab', 'cuda_ab', ";
    cerr << "'nesterov', 'cuda_nesterov', 'cuda_adadelta', 'cuda_adam'\n";
    exit(-1);
  }
}

int main(int argc, char* argv[]) 
{
    parseArg(argc, argv);
    srand(seed);

    auto handler = [&](ivhd::LogLevel level, const std::string message)
	{
		switch (level)
		{
		case ivhd::LogLevel::Info: std::cout<<message<<std::endl; break;
		case ivhd::LogLevel::Warning: std::cout<<message<<std::endl; break;
		case ivhd::LogLevel::Error: std::cout<<message<<std::endl; break;
		default: ;
		}
	};


    auto m_ivhd = ivhd::createIVHD(handler);
    auto m_particleSystem = m_ivhd->resourceFactory().createParticleSystem();
	auto m_graph = m_ivhd->resourceFactory().createGraph();

    if (!m_graph->loadFromCache(knn_file))
    {
        cerr << "Invalid knn file was used.";
        return 0;
    }

    cudaDeviceSetLimit(cudaLimitMallocHeapSize, HEAP_LIMIT);

	const auto casterRandom = m_ivhd->resourceFactory().createCaster(ivhd::CasterType::Random);

    if (dataset_file.empty())
	{
		return 0;
	}
	else
	{
		auto parser = m_ivhd->resourceFactory().createParser(ivhd::ParserType::Csv);
		parser->loadFile(dataset_file, *m_particleSystem);
	}

	casterRandom->calculateForces(*m_particleSystem, *m_graph);
	casterRandom->calculatePositions(*m_particleSystem);

    system_clock::time_point now = system_clock::now();
    long start = time_point_cast<milliseconds>(now).time_since_epoch().count();
    long offset = 0;

    ofstream errFile;
    errFile.open(experiment_name + "_error");
    float minError = std::numeric_limits<float>::max();
    auto onError = [&](float err) -> void 
    {
        now = system_clock::now();
        minError = min(minError, err);
        auto time = time_point_cast<milliseconds>(now).time_since_epoch().count() -
                    start - offset;

        errFile << time << " " << err << endl;
    };

    auto onPos = [&](vector<float2>& positions) -> void 
    {
        for (auto i = 0; i < positions.size(); i++) 
		{
			m_particleSystem->setPosition(i, positions[i].x, positions[i].y);
		}
    };

    auto casterCUDA = std::make_shared<CasterCudaAB>(m_particleSystem->countParticles(), onError, onPos);

    casterCUDA->loadDistances(*m_graph);
	casterCUDA->loadPositions(*m_particleSystem);
	casterCUDA->allocateInitializeDeviceMemory();

    cudaDeviceSynchronize();

    now = system_clock::now();
    start = time_point_cast<milliseconds>(now).time_since_epoch().count();

    for(auto i = 0; i<iterations; i++)
    {
        casterCUDA->step(*m_particleSystem, *m_graph);
        i++;
    }
       
    cudaDeviceSynchronize();

    now = system_clock::now();
    auto totalTime =
        time_point_cast<milliseconds>(now).time_since_epoch().count() - start -
        offset;
    cerr << totalTime << endl;
    cerr << "minError: " << minError << endl;

    casterCUDA->finish();

    ofstream results;
    results.open(experiment_name + "_result");
    for (int i = 0; i < m_particleSystem->countParticles(); i++) 
    {
        results << casterCUDA->positions[i].x << " " << casterCUDA->positions[i].y << " "
                << m_particleSystem->labels()[i] << endl;
    }

    results.close();
    errFile.close();

    return 0;
}