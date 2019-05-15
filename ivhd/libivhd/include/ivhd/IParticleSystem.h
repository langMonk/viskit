///
/// \author Bartosz Minch <minch@agh.edu.pl>
/// \date 18.04.2019
///

#pragma once

#include <vector>
#include "Structures.h"

namespace ivhd
{
	class ICaster;
	class IReducer;
	class IClusterer;

	class IParticleSystem
	{

	public:
		/// <summary>
		/// Returns original coordinates.
		/// </summary>
		/// <returns> Container with data original coordinates.</returns>
		virtual std::vector<std::vector<float>> originalCoordinates() = 0;

		/// <summary>
		/// Returns current dataPoints obtained via cast/reduce/cluster operations
		/// </summary>
		/// <returns> Container with data points.</returns>
		virtual std::vector<DataPoint> dataPoints() = 0;

		/// <summary>
		/// Cast data between two spaces (from N -> M dimensions, where M << N). 
		/// </summary>
		/// <params name="caster"> Caster, that will be used for casting between spaces. </params>
		virtual void castData(std::shared_ptr<ICaster> caster) = 0;

		/// <summary>
		/// Reduce data dimensionality. 
		/// </summary>
		/// <params name="reducer"> Reducer, that will be used for dimensionality reduction. </params>
		virtual void reduceData(IReducer& reducer) = 0;

		/// <summary>
		/// Cluster data.
		/// </summary>
		/// <params name="clusterer"> Clusterer, that will be used for data clustering. </params>
		virtual void clusterData(IClusterer& clusterer) = 0;
	};
}