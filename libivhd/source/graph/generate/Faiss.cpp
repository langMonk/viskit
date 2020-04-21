#include "graph/generate/Faiss.h"

#include <cstdio>
#include <cstdlib>
#include <cassert>

#include <faiss/gpu/GpuIndexFlat.h>
#include <faiss/gpu/GpuIndexIVFFlat.h>
#include <faiss/gpu/StandardGpuResources.h>

namespace ivhd::graph::generate
{ 
	Faiss::Faiss(core::System& system)
		: GraphGenerator(system)
	{
	}

	void Faiss::generateNearestNeighbors(particles::ParticleSystem& ps, graph::Graph& graph, size_t k, bool distancesEqualOne)
	{ 		

		graph.initialize(ps.countParticles());

		const auto d = ps.datasetInfo().dimensionality;
		const auto count = ps.datasetInfo().count;

		const auto nb = count;  // size of database

		std::vector<float> xb;

		const auto coordinates = ps.originalCoordinates();

		for(auto i = 0; i < nb; i++) 
		{
			for(auto j = 0; j < d; j++)
			{
				xb.push_back(coordinates[i].first[j]);
			}
		}

		m_ext_system.logger().logInfo("[FAISS kNN Generator] Searching for nearest neighbors...");

		faiss::gpu::StandardGpuResources res;
		
		faiss::gpu::GpuIndexFlatL2 index_flat(&res, d);
		//faiss::gpu::GpuIndexIVFFlat index_ivf(&res, d, static_cast<int>(sqrt(count)), faiss::METRIC_L2);

		assert(!index_ivf.is_trained);
		index_flat.train(nb, xb.data());
		assert(index_ivf.is_trained);
		index_flat.add(nb, xb.data());  // add vectors to the index

		printf("is_trained = %s\n", index_flat.is_trained ? "true" : "false");
		printf("ntotal = %ld\n", index_flat.ntotal);

		k+=1;
		{ 
			long *I = new long[k * count];
			float *D = new float[k * count];

			index_flat.search(nb, xb.data(), k, D, I);

			for (int i = 0; i < count; i++)
			{
				for(int j = 0; j < k; j++)
				{
					const auto index = I[i * k + j];
					if (i != index)
					{
						if (!distancesEqualOne)
						{
							graph.addNeighbors(Neighbors(i, index, D[i * k + j], NeighborsType::Near));
						}
						else
						{
							graph.addNeighbors(Neighbors(i, index, 1.0f, NeighborsType::Near));
						}
					}
				}
			}

			delete[] I;
			delete[] D;
		}
		
		xb.clear();

		m_ext_system.logger().logInfo("[FAISS kNN Generator] Finished.");
	}
}