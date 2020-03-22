///
/// \author Bartosz Minch <minch@agh.edu.pl>
/// \date 18.04.2019
///

#pragma once

#include "ICaster.h"

namespace ivhd
{
	/// <summary>
	/// The public caster DPD interface.
	/// </summary>
	class ICasterDpd : public virtual ICaster
	{
		// protected construction and destruction methods
	protected:
		virtual ~ICasterDpd() = default;
		
	};
}