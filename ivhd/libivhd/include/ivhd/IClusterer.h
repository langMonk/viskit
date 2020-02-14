#pragma once

///
/// \author Bartosz Minch <minch@agh.edu.pl>
/// \date 08.05.2019
///

#pragma once

#include "ITransformer.h"

namespace ivhd
{
	class IClusterer : public virtual ITransformer
	{
		// public methods 
	public:
		/// <summary>
		/// Handles process of clustering data.
		/// </summary>
		virtual void cluster() = 0;

		/// <summary>
		/// Called, when clusterer is being initialized.
		/// </summary>
		virtual void initialize() = 0;

		/// <summary>
		/// Called, when clusterer is being finalized.
		/// </summary>
		virtual void finalize() = 0;

	};
}