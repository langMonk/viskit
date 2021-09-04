///
/// \author Bartosz Minch <minch@agh.edu.pl>
/// \date 08.05.2019
///

#pragma once

#include <viskit/viskit/ITransformer.h>

namespace viskit
{
	class IReducer : public virtual ITransformer
	{
		// public methods 
	public:
		/// <summary>
		/// Handles process of reducing data.
		/// </summary>
		virtual void reduce() = 0;

		/// <summary>
		/// Called, when reducer is being initialized.
		/// </summary>
		virtual void initialize() = 0;

		/// <summary>
		/// Called, when reducer is being finalized.
		/// </summary>
		virtual void finalize() = 0;

	};
}