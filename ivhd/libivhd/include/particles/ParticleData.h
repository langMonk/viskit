///
/// \author Bartosz Minch <minch@agh.edu.pl>
/// \date 18.05.2019
///

#pragma once

#include "math/glm_adapter.h"

namespace ivhd::particles
{ 
	class ParticleData
	{
		// public construction and destruction methods
	public:
		ParticleData(){}
		explicit ParticleData(size_t maxCount) { generate(maxCount); }
		~ParticleData(){}

		ParticleData(const ParticleData&) = delete;
		ParticleData& operator=(const ParticleData&) = delete;

		void generate(size_t maxSize);
		void kill(size_t id);
		void wake(size_t id);
		void swapData(size_t a, size_t b);

		// public members
	public:
		std::unique_ptr<glm::vec4[]> m_pos;
		std::unique_ptr<glm::vec4[]> m_col;
		std::unique_ptr<glm::vec4[]> m_startCol;
		std::unique_ptr<glm::vec4[]> m_endCol;
		std::unique_ptr<glm::vec4[]> m_vel;
		std::unique_ptr<glm::vec4[]> m_acc;
		std::unique_ptr<glm::vec4[]> m_time;
		std::unique_ptr<bool[]>  m_alive;

		size_t m_count{ 0 };
		size_t m_countAlive{ 0 };
	};
}
