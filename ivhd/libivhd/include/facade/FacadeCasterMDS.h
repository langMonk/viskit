///
/// \author Bartosz Minch <minch@agh.edu.pl>
/// \date 10.02.2020
///

#pragma once

#include "facade/FacadeCaster.h"
#include "ivhd/IParticleSystem.h"
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

		explicit FacadeCasterMDS(std::shared_ptr<core::Core> core);
		~FacadeCasterMDS() = default;

		FacadeCasterMDS(const FacadeCasterMDS&) = delete;
		FacadeCasterMDS(FacadeCasterMDS&&) = delete;

		FacadeCasterMDS& operator=(const FacadeCasterMDS&) = delete;
		FacadeCasterMDS& operator=(FacadeCasterMDS&&) = delete;

		// public methods
	public:
		void castParticleSystem(std::shared_ptr<ivhd::IParticleSystem>& ps) override;

		void castParticle(std::shared_ptr<ivhd::IParticleSystem>& ps, size_t index) override;

		// private members
	private:
		std::shared_ptr<ivhd::embed::cast::CasterMDS> m_internalCaster;
	};
}