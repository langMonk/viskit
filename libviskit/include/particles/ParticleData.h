///
/// \author Bartosz Minch <minch@agh.edu.pl>
/// \date 18.05.2019
///

#pragma once

#include <vector>
#include "math/glm_adapter.h"

namespace viskit
{
	namespace particles
	{
		class ParticleData
		{
			// public construction and destruction methods
		public:
			ParticleData()= default;
			~ParticleData() = default;

			ParticleData(const ParticleData&) = delete;
			ParticleData& operator=(const ParticleData&) = delete;

			void generate(size_t maxSize);
			void kill(size_t id);
			void wake(size_t id);
			void swapData(size_t a, size_t b);
			bool empty();
			void clear();

			// public members
		public:
			std::vector<glm::vec4> m_pos;
			std::vector<glm::vec4> m_acc;
			std::vector<glm::vec4> m_force;
			std::vector<glm::vec4> m_vel;
			std::vector<glm::vec4> m_col;
			std::vector<bool> m_alive;

			size_t m_count{ 0 };
			size_t m_countAlive{ 0 };
		};
	}
}
