///
/// \author Bartosz Minch <minch@agh.edu.pl>
/// \date 18.04.2019
///

#pragma once

#include <memory>
#include <map>
#include <iostream>

#include "Caster.h"
#include "particles/ParticleSystem.h"

namespace ivhd::embed::cast
{ 
	class CasterRandom : public Caster
	{
		// public construction and destruction methods
	public:
		CasterRandom(core::System& system);

		// public methods
	public:
		void cast(particles::ParticleSystem& ps);

		int maxEdge() { return m_maxEdge; };

	private:
		int m_maxEdge;
	};
}