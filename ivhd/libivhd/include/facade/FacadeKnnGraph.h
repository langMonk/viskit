///
/// \author Bartosz Minch <minch@agh.edu.pl>
/// \date 26.04.2019
///

#pragma once

#include <vector>
#include <ivhd/IKnnGraph.h>
#include <core/ParticleSystem.h>

namespace ivhd::facade
{
	class FacadeKnnGraph : public IKnnGraph
	{
	public:
		FacadeKnnGraph(core::ParticleSystem& system);

		// IDistanceMatrix implementation
	public:
		void resetParams() override;
		bool create() override;
		int createFromCache() override;
		void clear() override;
		void sort() override;
		bool saveToCache() override;
		bool reversedNeighborsEnabled() override;
		size_t size() override;
		void add(DistElem& element) override;
		DistElem& getElement(long index) override;

		// private methods
	private:
		void add_min_dist(DistElem* n, int elems, float new_r, long pi, long pj, bool sort);
		void add_max_dist(DistElem* n, int elems, float new_r, long pi, long pj, bool sort);
		void add_to_dist_matrix(DistElem* n, int elems);
		void add_to_dist_matrix_choosen(DistElem* n, int elems, bool* choosen);
		void add_to_tmp_dist_matrix(DistElem* a, int ni, int i, int j, float r, DistElemType t);
		void reset_tmp_dist_matrix(DistElem* n, float initval, int elems);
		

		// private members
	private:
		core::ParticleSystem& m_system;

		std::vector<DistElem> m_data;

		int m_outlierTreshhold;

		bool m_useCosineMetric, m_setDistancesToOne, m_useReverseKNN;
		int m_nearestNeighborsCount, m_randomNeightborsCount, m_furthestNeighborsCount;

		int near_nei_cnt_max, rand_min_dist_nn, near_cut_off;
		float max_distance, average_cache_near_distance;
	};
}