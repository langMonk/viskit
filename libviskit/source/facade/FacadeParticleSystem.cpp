///
/// \author Bartosz Minch <minch@agh.edu.pl>
/// \date 04.05.2019
///

#include "facade/FacadeParticleSystem.h"
#include "facade/FacadeGraph.h"
#include <memory>
#include <fstream>

namespace viskit::facade
{ 
	FacadeParticleSystem::FacadeParticleSystem(const std::shared_ptr<core::Core>& core)
		: m_ext_core(core)
		, m_internalParticleSystem(std::make_shared<particles::ParticleSystem>(core->system()))
	{
	}

	std::vector<std::pair<DataPoint, size_t>> FacadeParticleSystem::originalCoordinates()
	{
		return m_internalParticleSystem->originalCoordinates();
	}

	glm::vec4* FacadeParticleSystem::positions()
	{
		return m_internalParticleSystem->calculationData()->m_pos.data();
	};

    glm::vec4* FacadeParticleSystem::forces()
	{
		return m_internalParticleSystem->calculationData()->m_force.data();
	};

    glm::vec4* FacadeParticleSystem::velocities()
	{
		return m_internalParticleSystem->calculationData()->m_vel.data();
	};

    glm::vec4* FacadeParticleSystem::colors()
	{
		return m_internalParticleSystem->calculationData()->m_col.data();
	}

	std::vector<size_t> FacadeParticleSystem::labels()
	{
		return m_internalParticleSystem->labels();
	}

	void FacadeParticleSystem::setPosition(size_t index, float x, float y)
	{
		m_internalParticleSystem->calculationData()->m_pos[index] = glm::vec4{ x, y, 0.0f, 1.0f };
	}

	size_t FacadeParticleSystem::countAlive()
	{
		return m_internalParticleSystem->countAwakeParticles();
	}

	size_t FacadeParticleSystem::countParticles()
	{
		return m_internalParticleSystem->countParticles();
	}

	void FacadeParticleSystem::clear()
	{
	
		m_internalParticleSystem->clear();
	}

	bool FacadeParticleSystem::empty()
	{
		return m_internalParticleSystem->empty();
	}

	bool FacadeParticleSystem::saveToFile(const std::string& fileName)
	{
		std::ofstream file(fileName, std::ios::out);

		if(file.good())
		{
			auto positions = m_internalParticleSystem->calculationData()->m_pos;
			auto labels = m_internalParticleSystem->labels();

			for (auto i = 0; i < positions.size(); i++)
			{
				file << positions[i].x << "," << positions[i].y << "," << labels[i] << std::endl;
			}

			return true;
		}
		else { return false; }
	}

	DatasetInfo FacadeParticleSystem::datasetInfo() {
        return m_internalParticleSystem->datasetInfo();
    }
}
