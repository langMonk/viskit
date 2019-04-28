///
/// \author Bartosz Minch <minch@agh.edu.pl>
/// \date 18.04.2019
///

#pragma once

#include "Structures.h"

namespace ivhd
{
	class IParticleSystem
	{
	public:
		/// <summary>
		/// Creates distance matrix.
		/// </summary>
		/// <returns> 1 if matrix was generated properly </returns>
		virtual bool loadFromFile() = 0;

		/// <summary>
		/// Resets all parameters involved in matrix generation
		/// </summary>
		virtual void resetParams() = 0;

		/// <summary>
		/// Clears the distance matrix.
		/// </summary>
		virtual void clear() = 0;

		/// <summary>
		/// Returns the size of the matrix.
		/// </summary>
		/// <returns> Size of the matrix </returns>
		virtual size_t size() = 0;

		/// <summary>
		/// Sorts the matrix.
		/// </summary>
		virtual void sort() = 0;

		/// <summary>
		/// Saves matrix to the cache.
		/// </summary>
		/// <returns> 1 if success </return>
		virtual bool saveToCache() = 0;

		/// <summary>
		/// Check if RkNN is used.
		/// </summary>
		/// <returns> 1 if RkNN algorithm is being used </return>
		virtual bool reversedNeighborsEnabled() = 0;

		/// <summary>
		/// Add object to distance array.
		/// </summary>
		/// <param="element">Element that should be added to matrix.</param>
		virtual void add(DistElem& element) = 0;

		/// <summary>
		/// Get element from the distance array.
		/// </summary>
		/// <param="index">Index where we can find element.</param>
		/// <returns> Distance element from specified index. </returns>
		virtual DistElem& getElement(long index) = 0;
	};
}