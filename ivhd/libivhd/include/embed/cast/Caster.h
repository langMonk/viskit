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

		Caster(const Caster&) = delete;
		Caster& operator=(const Caster&) = delete;

		// public methods
	public:
		core::ParticleSystem& particleSystem() const;

		// protected methods
	protected:
		virtual void initialize();

		virtual void finalize();

	protected:
		std::map<std::string, std::unique_ptr<SettingType>> m_parameters;

		core::ParticleSystem& m_ext_system;
	};
}