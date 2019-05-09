///
/// \author Bartosz Minch <minch@agh.edu.pl>
/// \date 18.04.2019
///

#pragma once

#include <map>
#include <iostream>

#include "core/ParticleSystem.h"
#include "ivhd/SettingType.h"
#include "Caster.h"

namespace ivhd::embed::cast
{
	class Caster
	{
		// public construction and destruction methods
	public:
		Caster(core::ParticleSystem& system);
		
		virtual ~Caster();

		// public methods
	public:

	private:
		std::map<std::string, std::unique_ptr<SettingType>> m_parameters;

		core::ParticleSystem& m_ext_system;
	};
}