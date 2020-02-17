///
/// \author Bartosz Minch <minch@agh.edu.pl>
/// \date 10.02.2020
///

#pragma once

#include "facade/FacadeCaster.h"
#include "embed/cast/CasterMDS.h"

namespace ivhd::facade
{
	/// <summary>
	/// Implementation of ICaster interface.
	/// </summary>
	class FacadeCasterMDS : public FacadeCaster
	{
		// public construction and destruction methods
	public:

		explicit FacadeCasterMDS(std::shared_ptr<core::Core> core, particles::ParticleSystem& ps);
		~FacadeCasterMDS() = default;

		FacadeCasterMDS(const FacadeCasterMDS&) = delete;
		FacadeCasterMDS(FacadeCasterMDS&&) = delete;

		FacadeCasterMDS& operator=(const FacadeCasterMDS&) = delete;
		FacadeCasterMDS& operator=(FacadeCasterMDS&&) = delete;

		// public methods
	public:
		void castParticleSystem() override;

		void castParticle(size_t index) override;

		CasterType type() override { return CasterType::MDS; }
		
		// private members
	private:
		std::shared_ptr<embed::cast::CasterMDS> m_internalCaster;
	};
}