///
/// \author Bartosz Minch <minch@agh.edu.pl>
/// \date 18.04.2019
///

#pragma once

#include "ivhd/ICaster.h"
#include "core/ParticleSystem.h"
#include "embed/cast/CasterRandom.h"

namespace ivhd::facade
{
	/// <summary>
	/// Implementation of ICaster interface.
	/// </summary>
	class FacadeCasterMDS : public ICaster
	{
		// public construction and destruction methods
	public:

		explicit FacadeCasterMDS(core::ParticleSystem& system);
		~FacadeCasterMDS() = default;

		FacadeCasterMDS(const FacadeCasterMDS&) = delete;
		FacadeCasterMDS(FacadeCasterMDS&&) = delete;

		FacadeCasterMDS& operator=(const FacadeCasterMDS&) = delete;
		FacadeCasterMDS& operator=(FacadeCasterMDS&&) = delete;

		// public methods
	public:
		void cast() override;

		void resetSettings() override;

		void loadSettings(std::istream& in) override;

		void saveSettings(std::ostream& out) override;

	/*private:
		ivhd::embed::cast::CasterRandom m_internalCaster;*/
	};
}