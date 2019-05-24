///
/// \author Bartosz Minch <minch@agh.edu.pl>
/// \date 18.05.2019
///

#pragma once

#include <vector>
#include <memory>
#include "particles/generate/ParticleGenerator.h"

namespace ivhd::particles::emit
{ 
	class ParticleEmitter
	{
		// public construction and destruction methods
	public:
		ParticleEmitter() { }
		virtual ~ParticleEmitter() { }

		// public methods
	public:
		virtual void emit(double dt, ParticleData* p);

		void addGenerator(std::shared_ptr<generate::ParticleGenerator> gen);

		// public members
	public:
		float m_emitRate{ 0.0 };

	protected:
		std::vector<std::shared_ptr<generate::ParticleGenerator>> m_generators;

	};
}