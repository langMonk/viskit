///
/// \author Bartosz Minch <minch@agh.edu.pl>
/// \date 18.04.2019
///

#pragma once

#include "ITransformer.h"

namespace ivhd
{
	class ICaster : public virtual ITransformer
	{
		// public methods 
	public:
		/// <summary>
		/// Handles process of casting between spaces
		/// </summary>
		virtual void cast() = 0;

		/// <summary>
		/// Called, when caster is being initialized.
		/// </summary>
		virtual void initialize() = 0;

		/// <summary>
		/// Called, when caster is being finalized.
		/// </summary>
		virtual void finalize() = 0;

	};
}