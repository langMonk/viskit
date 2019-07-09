///
/// \author Bartosz Minch <minch@agh.edu.pl>
/// \date 18.04.2019
///

#pragma once

#include "IParticleSystem.h"

namespace ivhd
{
	class ICaster
	{
		// public methods 
	public:
		/// <summary>
		/// Handles process of casting between spaces
		/// </summary>
		virtual void cast(std::shared_ptr<ivhd::IParticleSystem>& ps) = 0;
	};
}