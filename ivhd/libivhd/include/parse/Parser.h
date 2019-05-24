///
/// \author Bartosz Minch <minch@agh.edu.pl>
/// \date 15.05.2019
///

#pragma once

#include <string>
#include "core/ParticleSystem.h"

namespace ivhd::parse
{
	class Parser
	{
		// public construction and destruction methods
	public:
		Parser(core::ParticleSystem& system);

		Parser(const Parser&) = delete;
		Parser& operator=(const Parser&) = delete;

		// public methods
	public:
		virtual void initialize();

		virtual void loadFile(std::string filePath);

		virtual void finalize();

	protected:
		core::ParticleSystem& m_ext_system;
	};
}